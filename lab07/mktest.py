#!/usr/bin/python
import sys, os
from random import randint, choice

figure = ['s', 'r', 't']


def keygen(fig):
    return ' '.join([fig]+[str(randint(1, 2 ** 32)) for i in range(figure.index(fig) + 1)])


def pathgen():
    return ''.join([(lambda:choice(['l', 'r']))() for j in range(randint(1, 100))])


def main():

    if not 'tests' in os.listdir():
        os.mkdir('tests')

    if len(sys.argv) != 2:
        print("Usage: {0} <size of test>".format(
            sys.argv[0]))
        sys.exit(1)

    actions = [*["+"]*10, "-", "g", "s"]
    with open("tests/"+sys.argv[1]+'t', 'w') as output_file:
        for _ in range(int(sys.argv[1])):
            action = choice(actions)
            if action == "+":
                output_file.write("+ {0}\n".format(keygen(choice(figure))))

            elif action == "g":
                output_file.write("g {0}\n".format(pathgen()))

            elif action == "-":
                output_file.write("- {0}\n".format(pathgen()))

            elif action == "s":
                output_file.write("s\n")

        output_file.close()


if __name__ == "__main__":
    sys.exit(main())
