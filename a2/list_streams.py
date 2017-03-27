#!/usr/bin/python3
import os, sys
import subprocess

def checkArgs(args):
    """
        checks to make sure args are right
    """
    if args == 1:
        print("Please enter in a username")
        print("</body>")
        print("</html>")
        exit()

if __name__ == "__main__":
    checkArgs(len(sys.argv))
    sys.argv.pop(0)
    username = ' '.join(map(str, sys.argv))
    try:
        subprocess.check_call(["./db", "-lStreams", username])
    except OSError:
        print("Error: executable not found")
    print("</body>")
    print("</html>")
