
from collections import defaultdict
import sys
import subprocess
import argparse

"""
This script widens ARMv7-M instructions in-place to 32-bit if required.
It will accept two 16 bit instructions on the same 4-byte data line, but will
expand 16 bit instructions to 32 bit if that ensures alignment for subsequent
32 bit instructions. This prevents wasted cycles for misaligned fetches.

Flag -v results in a line of output to stderr per widened instruction.
"""


parser = argparse.ArgumentParser(description='Widen ARMv7-M instructions.')
parser.add_argument('filename', metavar='filename', type=str,
                    help='the plain assembly file (modified inplace)')
parser.add_argument('--verbose', '-v', action='count',
                    help='enable output for every widened instruction')

args = parser.parse_args()

funcs = defaultdict(list)

obj = args.filename.replace('.s', '.o')
dump = args.filename.replace('.s', '.dump')

# create an object dump of the assembly file
subprocess.run(["arm-none-eabi-gcc", f"{args.filename}", "-mthumb", "-mcpu=cortex-m4", "-mfloat-abi=hard", "-mfpu=fpv4-sp-d16", "-c", "-o", f"{obj}"], check=True)
subprocess.run(["arm-none-eabi-objdump", "-D", f"{obj}"], stdout=open(dump, 'w'), stderr=subprocess.DEVNULL)

func = None

# parse the functions from the object dump
with open(dump, 'r') as f:
    for line in f:
        if len(line) >= 10 and line[9] == '<':
            func = line[10:-3]
        elif len(line) == 0:
            func = None
        elif func:
            if len(line.split('\t')) >= 3:
                address, code, *ins = line.split('\t')
                if ins[0] == 'bl':
                    # grab the function name
                    ins[1] = ''.join(ins[1].split(' ')[1:])[1:-2]
                ins = ' '.join(ins).split(';')[0].strip()
                funcs[func].append({'address': int(address[:-1], 16),
                                    'ins': ins, 'width': None})

subprocess.run(["rm", f"{obj}"])
subprocess.run(["rm", f"{dump}"])

for func in funcs:
    # get widths of all instructions
    for i, ins in enumerate(funcs[func]):
        try:
            nextins = funcs[func][i+1]
            ins['width'] = nextins['address'] - ins['address']
        except IndexError:
            # we cannot determine the width of the last element, but that does
            # not matter; the last bx is always two bytes wide.
            break

aligned = True
alignedfuncs = defaultdict(list)

def widen(ins):
    if args.verbose:
        print(f"Widening '{ins['ins']}' at {hex(ins['address'])}", file=sys.stderr)
    ins = ins['ins'].split(" ")
    if ins[0][-2:] == '.w':
        raise Exception(f"Cannot widen already wide instruction {ins}")
    ins[0] += '.w'
    return ' '.join(ins)


def can_widen(ins):
    # So far this is the only exception we care about
    if ins[:3] == 'add' and ins[-2:] == 'sp':
        return False
    return True


for func in funcs:
    for i, ins in enumerate(funcs[func]):
        if ins['ins'][:2] == 'bx' or ins['width'] is None:
            alignedfuncs[func].append(ins['ins'])
            break
        else:
            nextins = funcs[func][i+1]  # nextins exists, since we halt at bx
            if ins['width'] == 4 or not can_widen(ins['ins']):  # cannot do anything
                alignedfuncs[func].append(ins['ins'])
            elif nextins['width'] == 2:  # delay the decision
                aligned = not aligned  # flip alignment
                alignedfuncs[func].append(ins['ins'])
            elif nextins['width'] == 4:
                if aligned:  # need to stay aligned
                    alignedfuncs[func].append(widen(ins))
                else:  # we automatically get aligned
                    alignedfuncs[func].append(ins['ins'])
                    aligned = True

func = None
output = []

# take the functions from the object dump and insert them in the asm
with open(args.filename, 'r') as f:
    for i, line in enumerate(f):
        if not func:
            output.append(line.strip())
        if ':' in line:
            func = line.replace(':', '').strip()
        if 'bx lr' in line:
            output += alignedfuncs[func]
            func = None

with open(args.filename, 'w') as f:
    for ins in output:
        f.write(ins + '\n')
