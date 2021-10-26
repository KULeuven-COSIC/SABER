# Speed Evaluation
## Key Encapsulation Schemes
| scheme | implementation | key generation [cycles] | encapsulation [cycles] | decapsulation [cycles] |
| ------ | -------------- | ----------------------- | ---------------------- | ---------------------- |
| firesaber (1 executions) | clean | AVG: 3,762,557 <br /> MIN: 3,762,557 <br /> MAX: 3,762,557 | AVG: 4,671,932 <br /> MIN: 4,671,932 <br /> MAX: 4,671,932 | AVG: 5,317,828 <br /> MIN: 5,317,828 <br /> MAX: 5,317,828 |
| firesaber (1 executions) | m4-striding | AVG: 1,423,610 <br /> MIN: 1,423,610 <br /> MAX: 1,423,610 | AVG: 1,747,301 <br /> MIN: 1,747,301 <br /> MAX: 1,747,301 | AVG: 1,789,389 <br /> MIN: 1,789,389 <br /> MAX: 1,789,389 |
| firesaber (1 executions) | m4-tc4kara | AVG: 1,381,782 <br /> MIN: 1,381,782 <br /> MAX: 1,381,782 | AVG: 1,695,025 <br /> MIN: 1,695,025 <br /> MAX: 1,695,025 | AVG: 1,726,657 <br /> MIN: 1,726,657 <br /> MAX: 1,726,657 |
| firesaber (1 executions) | m4fspeed | AVG: 992,165 <br /> MIN: 992,165 <br /> MAX: 992,165 | AVG: 1,203,211 <br /> MIN: 1,203,211 <br /> MAX: 1,203,211 | AVG: 1,149,409 <br /> MIN: 1,149,409 <br /> MAX: 1,149,409 |
| firesaber (1 executions) | m4fstack | AVG: 1,317,405 <br /> MIN: 1,317,405 <br /> MAX: 1,317,405 | AVG: 1,613,944 <br /> MIN: 1,613,944 <br /> MAX: 1,613,944 | AVG: 1,594,023 <br /> MIN: 1,594,023 <br /> MAX: 1,594,023 |
| lightsaber (1 executions) | clean | AVG: 1,032,714 <br /> MIN: 1,032,714 <br /> MAX: 1,032,714 | AVG: 1,508,692 <br /> MIN: 1,508,692 <br /> MAX: 1,508,692 | AVG: 1,827,607 <br /> MIN: 1,827,607 <br /> MAX: 1,827,607 |
| lightsaber (1 executions) | m4-striding | AVG: 448,679 <br /> MIN: 448,679 <br /> MAX: 448,679 | AVG: 631,233 <br /> MIN: 631,233 <br /> MAX: 631,233 | AVG: 647,753 <br /> MIN: 647,753 <br /> MAX: 647,753 |
| lightsaber (1 executions) | m4-tc4kara | AVG: 438,226 <br /> MIN: 438,226 <br /> MAX: 438,226 | AVG: 615,553 <br /> MIN: 615,553 <br /> MAX: 615,553 | AVG: 626,843 <br /> MIN: 626,843 <br /> MAX: 626,843 |
| lightsaber (1 executions) | m4fspeed | AVG: 351,962 <br /> MIN: 351,962 <br /> MAX: 351,962 | AVG: 481,517 <br /> MIN: 481,517 <br /> MAX: 481,517 | AVG: 452,547 <br /> MIN: 452,547 <br /> MAX: 452,547 |
| lightsaber (1 executions) | m4fstack | AVG: 421,706 <br /> MIN: 421,706 <br /> MAX: 421,706 | AVG: 590,781 <br /> MIN: 590,781 <br /> MAX: 590,781 | AVG: 579,943 <br /> MIN: 579,943 <br /> MAX: 579,943 |
| saber (1 executions) | clean | AVG: 2,193,658 <br /> MIN: 2,193,658 <br /> MAX: 2,193,658 | AVG: 2,885,249 <br /> MIN: 2,885,249 <br /> MAX: 2,885,249 | AVG: 3,350,026 <br /> MIN: 3,350,026 <br /> MAX: 3,350,026 |
| saber (1 executions) | m4-striding | AVG: 878,300 <br /> MIN: 878,300 <br /> MAX: 878,300 | AVG: 1,137,803 <br /> MIN: 1,137,803 <br /> MAX: 1,137,803 | AVG: 1,161,188 <br /> MIN: 1,161,188 <br /> MAX: 1,161,188 |
| saber (1 executions) | m4-tc4kara | AVG: 854,778 <br /> MIN: 854,778 <br /> MAX: 854,778 | AVG: 1,106,446 <br /> MIN: 1,106,446 <br /> MAX: 1,106,446 | AVG: 1,121,996 <br /> MIN: 1,121,996 <br /> MAX: 1,121,996 |
| saber (1 executions) | m4fspeed | AVG: 644,158 <br /> MIN: 644,158 <br /> MAX: 644,158 | AVG: 820,559 <br /> MIN: 820,559 <br /> MAX: 820,559 | AVG: 773,506 <br /> MIN: 773,506 <br /> MAX: 773,506 |
| saber (1 executions) | m4fstack | AVG: 819,029 <br /> MIN: 819,029 <br /> MAX: 819,029 | AVG: 1,056,636 <br /> MIN: 1,056,636 <br /> MAX: 1,056,636 | AVG: 1,035,848 <br /> MIN: 1,035,848 <br /> MAX: 1,035,848 |
## Signature Schemes
| scheme | implementation | key generation [cycles] | sign [cycles] | verify [cycles] |
| ------ | -------------- | ----------------------- | ------------- | --------------- |
# Memory Evaluation
## Key Encapsulation Schemes
| Scheme | Implementation | Key Generation [bytes] | Encapsulation [bytes] | Decapsulation [bytes] |
| ------ | -------------- | ---------------------- | --------------------- | --------------------- |
| firesaber | clean | 19,364 | 19,460 | 20,940 |
| firesaber | m4-striding | 5,328 | 5,296 | 5,304 |
| firesaber | m4-tc4kara | 7,084 | 7,052 | 7,060 |
| firesaber | m4fspeed | 7,676 | 8,348 | 8,356 |
| firesaber | m4fstack | 4,316 | 3,332 | 3,340 |
| lightsaber | clean | 9,356 | 9,452 | 10,196 |
| lightsaber | m4-striding | 4,296 | 4,272 | 4,280 |
| lightsaber | m4-tc4kara | 6,052 | 6,028 | 6,036 |
| lightsaber | m4fspeed | 5,628 | 6,308 | 6,316 |
| lightsaber | m4fstack | 3,292 | 3,068 | 3,076 |
| saber | clean | 12,948 | 13,044 | 14,220 |
| saber | m4-striding | 4,808 | 4,784 | 4,792 |
| saber | m4-tc4kara | 6,564 | 6,540 | 6,548 |
| saber | m4fspeed | 6,652 | 7,332 | 7,340 |
| saber | m4fstack | 3,804 | 3,196 | 3,204 |
## Signature Schemes
| Scheme | Implementation | Key Generation [bytes] | Sign [bytes] | Verify [bytes] |
| ------ | -------------- | ---------------------- | ------------ | -------------- |
# Hashing Evaluation
## Key Encapsulation Schemes
| Scheme | Implementation | Key Generation [%] | Encapsulation [%] | Decapsulation [%] |
| ------ | -------------- | ------------------ | ----------------- | ----------------- |
| firesaber | clean | 18.9% | 18.7% | 13.8% |
| firesaber | m4-striding | 50.0% | 50.1% | 41.2% |
| firesaber | m4-tc4kara | 51.5% | 51.7% | 42.7% |
| firesaber | m4fspeed | 71.6% | 72.7% | 64.1% |
| firesaber | m4fstack | 54.0% | 54.3% | 46.2% |
| lightsaber | clean | 24.7% | 23.6% | 15.3% |
| lightsaber | m4-striding | 56.8% | 56.5% | 43.3% |
| lightsaber | m4-tc4kara | 58.2% | 57.9% | 44.7% |
| lightsaber | m4fspeed | 72.4% | 74.0% | 61.9% |
| lightsaber | m4fstack | 60.4% | 60.3% | 48.3% |
| saber | clean | 21.4% | 20.8% | 14.8% |
| saber | m4-striding | 53.4% | 53.4% | 42.6% |
| saber | m4-tc4kara | 54.9% | 55.0% | 44.1% |
| saber | m4fspeed | 72.8% | 74.1% | 63.9% |
| saber | m4fstack | 57.3% | 57.6% | 47.8% |
## Signature Schemes
| Scheme | Implementation | Key Generation [%] | Sign [%] | Verify [%] |
| ------ | -------------- | ------------------ | -------- | ---------- |
# Size Evaluation
## Key Encapsulation Schemes
| Scheme | Implementation | .text [bytes] | .data [bytes] | .bss [bytes] | Total [bytes] |
| ------ | -------------- | ------------- | ------------- | ------------ | ------------- |
| firesaber | clean | 9,796 | 0 | 0 | 9,796 |
| firesaber | m4-striding | 30,532 | 0 | 0 | 30,532 |
| firesaber | m4-tc4kara | 43,306 | 0 | 0 | 43,306 |
| firesaber | m4fspeed | 18,768 | 0 | 0 | 18,768 |
| firesaber | m4fstack | 19,564 | 0 | 0 | 19,564 |
| lightsaber | clean | 9,920 | 0 | 0 | 9,920 |
| lightsaber | m4-striding | 30,724 | 0 | 0 | 30,724 |
| lightsaber | m4-tc4kara | 43,498 | 0 | 0 | 43,498 |
| lightsaber | m4fspeed | 18,896 | 0 | 0 | 18,896 |
| lightsaber | m4fstack | 19,716 | 0 | 0 | 19,716 |
| saber | clean | 9,684 | 0 | 0 | 9,684 |
| saber | m4-striding | 30,424 | 0 | 0 | 30,424 |
| saber | m4-tc4kara | 43,198 | 0 | 0 | 43,198 |
| saber | m4fspeed | 18,692 | 0 | 0 | 18,692 |
| saber | m4fstack | 19,468 | 0 | 0 | 19,468 |
## Signature Schemes
| Scheme | Implementation | .text [bytes] | .data [bytes] | .bss [bytes] | Total [bytes] |
| ------ | -------------- | ------------- | ------------- | ------------ | ------------- |
