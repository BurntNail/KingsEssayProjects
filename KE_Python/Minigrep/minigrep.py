from expandable_bit_vec import ExpandableBitVec
import sys
import re

if __name__ == "__main__":
    argv = sys.argv
    argc = len(argv)

    if argc == 1:
        print("You need to pass in a file as the first argument.")
        sys.exit(-1)
    elif argc == 2:
        print("You need to pass in a pattern to look for as the second argument.")
        sys.exit(-1)

    pattern = re.compile(argv[2])

    toBePrinted = ""
    with open(argv[1], 'r', encoding='utf-8') as file:
        ebv = ExpandableBitVec(256)
        for line in file.readlines():
            for match in pattern.finditer(line):
                for i in range(match.start(), match.end()):
                    ebv[i] = True

            for i, c in enumerate(line):
                if ebv[i]:
                    toBePrinted += f"\033[32m{line[i]}\033[0m"
                else:
                    toBePrinted += f"{line[i]}"
            ebv.clear()

    print(toBePrinted)