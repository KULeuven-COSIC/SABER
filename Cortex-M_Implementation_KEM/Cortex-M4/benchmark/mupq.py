import abc
from collections import defaultdict
import contextlib
import re
import os
import logging
import subprocess
import hashlib
import time
import statistics
from datetime import datetime


logging.basicConfig(level=logging.DEBUG)


class Implementation(object):
    """Contains some properties of a scheme implementation"""

    #: regex to parse the paths into schemes
    _path_regex = re.compile(
        r'(?P<project>\S+/)?'
        r'(?P<type>crypto_sign|crypto_kem)/'
        r'(?P<scheme>\S+)/'
        r'(?P<implementation>\S+)/?$')

    #: regex to find source files
    _source_regex = re.compile(r'.*\.(c|s|S)$')

    def __init__(self, project, primitive, scheme, implementation, path, namespace):
        """Sets up this scheme"""
        self.log = logging.getLogger(__class__.__name__)
        self.project = project
        self.primitive = primitive
        self.scheme = scheme
        self.implementation = implementation
        self.path = path
        if namespace == '':
            self.namespace = None
        else:
            self.namespace = f"{namespace}_{scheme.replace('-','').upper()}_{implementation.upper()}_"

    @classmethod
    def from_path(cls, project, path, namespace):
        """
        Construct a scheme implemenation from a path

        Specify the project that owns it
        """
        matches = cls._path_regex.match(path)
        if not matches:
            raise Exception(f"Unexpected path format: '{path}'")
        return cls(project,
                   matches.group("type"),
                   matches.group("scheme"),
                   matches.group("implementation"),
                   path, namespace)

    def get_binary_path(self, type_):
        return f'bin/{self.path.replace("/", "_")}_{type_}.bin'

    def build_binary(self, type_):
        self.log.info(f"Building {self} - {type_}")
        if self.namespace != None:
            subprocess.check_call(
              ['make',
              f"IMPLEMENTATION_PATH={self.path}",
              f"MUPQ_NAMESPACE={self.namespace}",
              self.get_binary_path(type_)])
        else:
            subprocess.check_call(
                ['make',
                f"IMPLEMENTATION_PATH={self.path}",
                self.get_binary_path(type_)])

    def get_object_path(self, source):
        return f'obj/{self.path.replace("/", "_")}_{source}'

    def build_objects(self, type_):
        self.log.info(f"Building {self} - {type_}")
        for source_file in os.listdir(self.path):
            if Implementation._source_regex.match(source_file) == None:
                continue
            object_file = self.get_object_path(source_file[:-1] + 'o')
            if self.namespace != None:
                subprocess.check_call(
                  ['make',
                  f"IMPLEMENTATION_PATH={self.path}",
                  f"MUPQ_NAMESPACE={self.namespace}",
                  object_file])
            else:
                subprocess.check_call(
                    ['make',
                    f"IMPLEMENTATION_PATH={self.path}",
                    object_file])

    def __str__(self):
        return f"{self.scheme} - {self.implementation}"


class PlatformSettings(object):
    """Contains the settings for a certain platform"""
    scheme_folders = [
        ('pqclean', 'mupq/pqclean/crypto_kem', 'PQCLEAN'),
        ('pqclean', 'mupq/pqclean/crypto_sign', 'PQCLEAN'),
    ]
    skip_list = []
    name = None

    def __init__(self):
        self.log = logging.getLogger(__class__.__name__)

    def __str__(self):
        return self.name

    def get_implementations(self, all=False):
        """Get the schemes"""
        try:
            for (parent, scheme_folder,namespace) in self.scheme_folders:
                for scheme in os.listdir(scheme_folder):
                    scheme_path = os.path.join(scheme_folder, scheme)
                    if not os.path.isdir(scheme_path):
                        continue
                    for implementation_path in os.listdir(scheme_path):
                        path = os.path.join(scheme_path,
                                            implementation_path)
                        if not os.path.isdir(path):
                            continue
                        impl = Implementation.from_path(parent, path, namespace)
                        if not all and self.should_skip(impl):
                            continue
                        yield impl
        except FileNotFoundError as e:
            raise Exception(
                "There is no bin/ folder. Please first make binaries."
            ) from e

    def should_skip(self, impl):
        """Should this Implementation be skipped?"""
        for item in self.skip_list:
            match = len(item) > 0
            for attribute, value in item.items():
                if getattr(impl, attribute) != value:
                    match = False
            if match:
                return True
        return False


class Platform(contextlib.AbstractContextManager):
    """Generic platform interface"""

    def __init__(self):
        self.log = logging.getLogger("platform interface")

    def __enter__(self):
        return super().__enter__()

    def __exit__(self, *args, **kwargs):
        return super().__exit__(*args, **kwargs)

    def device(self):
        raise NotImplementedError("Override this")

    @abc.abstractmethod
    def flash(self, binary_path):
        self.log.info("Flashing %s to device", binary_path)
        self.state = 'waiting'
        self.equals_seen = 0

    def run(self, binary_path):
        """Runs the flashed target and collects the result"""
        self.flash(binary_path)
        while not self._wait_for_start():
          self.flash(binary_path)
        self.log.info("Output started")
        return self._read_output()

    def _wait_for_start(self):
        """Waits until we read five equals signs"""
        while self.state == 'waiting':
            x = self.device().read()
            if x == b'':
                self.log.warning(
                    "timed out while waiting for the markers, reflashing")
                return False
            elif x == b'=':
                self.equals_seen += 1
                continue
            elif self.equals_seen > 5:
                self.state = 'beginning'
                self.log.debug("Found output marker")
            elif self.equals_seen > 1:
                self.log.warning(
                    "Got garbage after finding first equals sign, restarting"
                )
                return False
        # Read remaining = signs
        while self.state == 'beginning':
            x = self.device().read()
            # Consume remaining =
            if x != b'=':
                self.output = [x]
                self.state = 'reading'
                break
        return True

    def _read_output(self):
        while self.state == 'reading':
            x = self.device().read()
            if x == b'#':
                self.state = 'done'
                break
            elif x != b'':
                self.output.append(x)
        output = b''.join(self.output).decode('utf-8', 'ignore')
        # sometimes there's a line full of markers; strip out to avoid errors
        lines = (x for x in output.split('\n') if not all(c == '=' for c in x))
        return "{}\n".format('\n'.join(lines))


class BoardTestCase(abc.ABC):
    """
    Generic test class to run tests on all schemes.

    Generally you want to override run_test to parse the output of the tests
    running on the board.
    """
    test_type = 'undefined'

    def __init__(self, settings, interface):
        self.platform_settings = settings
        self.interface = interface
        self.log = logging.getLogger(__class__.__name__)

    def get_implementations(self, all=False):
        return self.platform_settings.get_implementations(all)

    @abc.abstractmethod
    def run_test(self, implementation):
        implementation.build_binary(f'{self.test_type}')
        binary = implementation.get_binary_path(f'{self.test_type}')
        return self.interface.run(binary)

    def test_all(self, args=[]):
        exclude = "--exclude" in args
        for implementation in self.get_implementations():
            if exclude and implementation.scheme in args:
                continue
            if not exclude and len(args) > 0 and implementation.scheme not in args:
                continue
            self.run_test(implementation)


class SimpleTest(BoardTestCase):
    test_type = 'test'

    def run_test(self, *args, **kwargs):
        output = super().run_test(*args, **kwargs).strip()
        if output.count("ERROR") or output.count("OK") != 30:
            self.log.error("Failed!")
        else:
            self.log.info("Success")


class StackBenchmark(BoardTestCase):
    test_type = 'stack'

    def write_result(self, implementation, result):
        timestamp = datetime.fromtimestamp(
            time.time()).strftime('%Y%m%d%H%M%S')
        filename = os.path.join(
            'benchmarks/',
            self.test_type, implementation.primitive,
            implementation.scheme, implementation.implementation,
            timestamp)
        os.makedirs(os.path.dirname(filename), exist_ok=True)
        with open(filename, 'w') as f:
            f.write(result)
        self.log.info("Wrote benchmark!")

    def run_test(self, implementation):
        self.log.info("Benchmarking %s", implementation)
        output = super().run_test(implementation)
        assert 'ERROR KEYS' not in output
        self.write_result(implementation, output)


class SpeedBenchmark(StackBenchmark):
    test_type = 'speed'

class HashingBenchmark(StackBenchmark):
    test_type = 'hashing'

class SizeBenchmark(StackBenchmark):
    test_type = 'size'

    def run_test(self, implementation):
        self.log.info("Measuring %s", implementation)
        implementation.build_objects(self.test_type)
        glob = f'obj/{implementation.path.replace("/", "_")}_*.o'
        output = subprocess.check_output(
                'arm-none-eabi-size -t ' + glob,
                shell=True,
                stderr=subprocess.DEVNULL,
                text=True)
        sizes = output.splitlines()[-1].split('\t')
        fsizes = (f'.text bytes:\n{sizes[0].strip()}\n'
                  f'.data bytes:\n{sizes[1].strip()}\n'
                  f'.bss bytes:\n{sizes[2].strip()}\n'
                  f'.total bytes:\n{sizes[3].strip()}\n')
        super().write_result(implementation, fsizes)


class TestVectors(BoardTestCase):
    test_type = 'testvectors'

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.testvectorhash = dict()

    def hash_output(self, output):
        hash = hashlib.sha3_256(output.strip()).hexdigest()
        return hash

    def run_test(self, implementation):
        checksum = self.hash_output(
            super().run_test(implementation).encode('utf-8'))
        assert self.testvectorhash[implementation.scheme] == checksum

    def _prepare_testvectors(self, exclude, args):
        for scheme, implementations in self.schemes.items():
            for impl in implementations:
                if exclude and impl.scheme in args:
                    continue
                if not exclude and len(args)>0 and impl.scheme not in args:
                    continue
                if impl.implementation not in ('ref', 'clean'):
                    continue
                # Build host version
                self.log.info("Running %s on host", impl)
                binpath = impl.get_binary_path(self.test_type)
                hostbin = (binpath
                           .replace('bin/', 'bin-host/')
                           .replace('.bin', ''))
                if impl.namespace != None:
                    subprocess.check_call(['make',
                                       f"IMPLEMENTATION_PATH={impl.path}",
                                       f"MUPQ_NAMESPACE={impl.namespace}",
                                       hostbin])
                else:
                    subprocess.check_call(['make',
                                       f"IMPLEMENTATION_PATH={impl.path}",
                                       hostbin])
                checksum = self.hash_output(
                        subprocess.check_output(
                            [hostbin],
                            stderr=subprocess.DEVNULL,
                        ))
                self.testvectorhash[scheme] = checksum
                break

    def test_all(self, args):
        self.schemes = defaultdict(list)
        for implementation in self.get_implementations(all=True):
            self.schemes[implementation.scheme].append(implementation)

        exclude = "--exclude" in args
        self._prepare_testvectors(exclude, args)

        for implementation in self.get_implementations():
            if exclude and implementation.scheme in args:
                continue
            if not exclude and len(args)>0 and implementation.scheme not in args:
                continue
            self.run_test(implementation)


class BuildAll(BoardTestCase):

    def __init__(self, settings):
        super().__init__(settings, None)

    def run_test(self, implementation):
        for test_type in ('test', 'testvectors', 'speed', 'hashing', 'stack'):
            implementation.build_binary(test_type)

class Converter(object):
    def convert(self):
        self._speed()
        self._stack()
        self._hashing()
        self._size()

    def _speed(self):
        self._header("Speed Evaluation")
        self._subheader("Key Encapsulation Schemes")
        self._tablehead(["scheme", "implementation", "key generation [cycles]",
                         "encapsulation [cycles]", "decapsulation [cycles]"])
        self._processPrimitives("benchmarks/speed/crypto_kem/", "speed")

        self._subheader("Signature Schemes")
        self._tablehead(["scheme", "implementation", "key generation [cycles]",
                         "sign [cycles]", "verify [cycles]"])
        self._processPrimitives("benchmarks/speed/crypto_sign/", "speed")

    def _stack(self):
        self._header("Memory Evaluation")
        self._subheader("Key Encapsulation Schemes")
        self._tablehead(["Scheme", "Implementation", "Key Generation [bytes]",
                         "Encapsulation [bytes]", "Decapsulation [bytes]"])
        self._processPrimitives("benchmarks/stack/crypto_kem/", "stack")

        self._subheader("Signature Schemes")
        self._tablehead(["Scheme", "Implementation", "Key Generation [bytes]",
                         "Sign [bytes]", "Verify [bytes]"])
        self._processPrimitives("benchmarks/stack/crypto_sign/", "stack")

    def _hashing(self):
        """ prints the cycles spent in hashing and the percentage of the total
            runtime """
        self._header("Hashing Evaluation")
        self._subheader("Key Encapsulation Schemes")
        self._tablehead(["Scheme", "Implementation", "Key Generation [%]",
                         "Encapsulation [%]", "Decapsulation [%]"])
        self._processPrimitives("benchmarks/hashing/crypto_kem/", "hashing")

        self._subheader("Signature Schemes")
        self._tablehead(["Scheme", "Implementation", "Key Generation [%]",
                         "Sign [%]", "Verify [%]"])
        self._processPrimitives("benchmarks/hashing/crypto_sign/", "hashing")

    def _size(self):
        """ prints the total number of bytes in the text, data, and bss sections
            of the scheme-specific code (i.e., excluding FIPS202, etc) """
        self._header("Size Evaluation")
        self._subheader("Key Encapsulation Schemes")
        self._tablehead(["Scheme", "Implementation", ".text [bytes]",
                         ".data [bytes]", ".bss [bytes]", "Total [bytes]"])
        self._processPrimitives("benchmarks/size/crypto_kem/", "size")

        self._subheader("Signature Schemes")
        self._tablehead(["Scheme", "Implementation", ".text [bytes]",
                         ".data [bytes]", ".bss [bytes]", "Total [bytes]"])
        self._processPrimitives("benchmarks/size/crypto_sign/", "size")


    def _processPrimitives(self, path, type_):
        if os.path.exists(path) == False:
            return;
        data = dict()
        for scheme in sorted(os.listdir(path)):
            data[scheme] = dict()
            for implementation in sorted(os.listdir(path+"/"+scheme)):
                measurements = []
                for measurement in os.listdir(path+"/"+scheme+"/"+implementation):
                    with open(path+"/"+scheme+"/"+implementation+"/"+measurement, "r") as f:
                        d = self._parseData(f.read(), type_)
                        measurements.append(d)
                self._formatData(scheme, implementation, measurements, type_)
                data[scheme][implementation] = measurements
        return data

    def _stats(self, data):
        return (int(statistics.mean(data)), min(data), max(data))

    def _parseData(self, fileContents, type_):
        parts = fileContents.split("\n")
        if type_ == 'size':
            text  = int(parts[1])
            data  = int(parts[3])
            bss   = int(parts[5])
            total = int(parts[7])
            return [text, data, bss, total]
        elif type_ == 'hashing':
            keygentotal    = int(parts[1])
            keygen         = int(parts[3])/keygentotal
            encsigntotal   = int(parts[5])
            encsign        = int(parts[7])/encsigntotal
            decverifytotal = int(parts[9])
            decverify      = int(parts[11])/decverifytotal
        else:
            keygen    = int(parts[1])
            encsign   = int(parts[3])
            decverify = int(parts[5])
        return [keygen, encsign, decverify]

    def _formatData(self, scheme, implementation, data, type_):
        if type_ == "speed":
            keygen    = self._formatStats([item[0] for item in data])
            encsign   = self._formatStats([item[1] for item in data])
            decverify = self._formatStats([item[2] for item in data])
            self._row([f"{scheme} ({len(data)} executions)", implementation, keygen, encsign, decverify])
        elif type_ == "stack":
            keygen     = self._formatNumber(max([item[0] for item in data]))
            encsign    = self._formatNumber(max([item[1] for item in data]))
            decverify  = self._formatNumber(max([item[2] for item in data]))
            self._row([scheme, implementation, keygen, encsign, decverify])
        elif type_ == "hashing":
            keygen     = self._formatPercentage(statistics.mean([item[0] for item in data]))
            encsign    = self._formatPercentage(statistics.mean([item[1] for item in data]))
            decverify  = self._formatPercentage(statistics.mean([item[2] for item in data]))
            self._row([scheme, implementation, keygen, encsign, decverify])
        elif type_ == "size":
            textsec = self._formatNumber(max([item[0] for item in data]))
            datasec = self._formatNumber(max([item[1] for item in data]))
            bsssec  = self._formatNumber(max([item[2] for item in data]))
            total   = self._formatNumber(max([item[3] for item in data]))
            self._row([scheme, implementation, textsec, datasec, bsssec, total])

class MarkdownConverter(Converter):
    def _header(self, headline):
        print(f"# {headline}")

    def _subheader(self, headline):
        print(f"## {headline}")

    def _tablehead(self, columns):
      print("| "+ " | ".join(columns)+" |")
      print("| "+ " | ".join(["-"*(len(c)) for c in columns]) + " |")

    def _row(self, data):
        print("| "+ " | ".join(data)+" |")

    def _formatStats(self, l):
        mean, minimum, maximum = self._stats(l)
        return "AVG: {:,} <br /> MIN: {:,} <br /> MAX: {:,}".format(mean, minimum, maximum)

    def _formatNumber(self, num):
        return f"{num:,}"

    def _formatPercentage(self, perc):
        return f"{perc*100:.1f}%"

class CsvConverter(Converter):
    def _header(self, headline):
        # always pad to 11 columns, so that github can nicely render it
        print(headline+","*10)

    def _subheader(self, headline):
        # always pad to 11 columns, so that github can nicely render it
        print(headline+","*10)

    def _tablehead(self, columns):
        # always pad to 11 columns, so that github can nicely render it
        print(",".join(columns)+(","*(11-len(columns))))

    def _speed(self):
        """ overwrite this here to we can can have three columns for mean, min, max """
        self._header("Speed Evaluation")
        self._subheader("Key Encapsulation Schemes")
        self._tablehead(["Scheme", "Implementation"] +
                        [f"Key Generation [cycles] ({x})" for x in ["mean", "min", "max"]] +
                        [f"Encapsulation [cycles] ({x})" for x in ["mean", "min", "max"]] +
                        [f"Decapsulation [cycles] ({x})" for x in ["mean", "min", "max"]])

        cyclesKem = self._processPrimitives("benchmarks/speed/crypto_kem/", "speed")

        self._subheader("Signature Schemes")
        self._tablehead(["Scheme", "Implementation"]+
                        [f"Key Generation [cycles] ({x})" for x in ["mean", "min", "max"]] +
                        [f"Sign [cycles] ({x})" for x in ["mean", "min", "max"]] +
                        [f"Verify [cycles] ({x})" for x in ["mean", "min", "max"]])
        cyclesSign = self._processPrimitives("benchmarks/speed/crypto_sign/", "speed")
        return (cyclesKem, cyclesSign)

    def _row(self, data):
        # always pad to 11 columns, so that github can nicely render it
        row = ",".join(data)
        print(row+(","*(10-row.count(","))))

    def _formatStats(self, l):
        mean, minimum, maximum = self._stats(l)
        return f"{mean},{minimum},{maximum}"

    def _formatNumber(self, num):
        return str(num)

    def _formatPercentage(self, perc):
        return f"{perc*100:.1f}"
