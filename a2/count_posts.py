#!/usr/bin/python3
import os, sys
import subprocess

def checkArgs(args):
    """
        checks to make sure args are right
    """
    if args == 1:
        print("Please enter in a username with the arguement<br>")
        exit()

if __name__ == "__main__":
    checkArgs(len(sys.argv))
    sys.argv.pop(0)
    choice = sys.argv.pop()
    username = ' '.join(map(str, sys.argv))
    try:
        subprocess.check_call(["./db", "-pCount", username, choice])
    except subprocess.CalledProcessError:
        print("Error: executing your file go check it out")
    except OSError:
        print("Error: executable not found")
