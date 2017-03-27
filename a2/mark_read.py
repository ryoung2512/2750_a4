#!/usr/bin/python3
import subprocess
import os, sys
from collections import Counter

def checkArgs(args):
    """
        checks to make sure args are right
    """
    if args < 4:
        print("Please enter in the appropriate number of arguments")
        exit()

if __name__ == "__main__":
    checkArgs(len(sys.argv))
    sys.argv.pop(0)
    limit = int(sys.argv.pop())
    allMessages = sys.argv.pop()
    choice = sys.argv.pop()
    username = ' '.join(map(str, sys.argv))
    setAll = False
    if allMessages == "1":
        setAll = True
    streams = []
    out = subprocess.Popen(["./db", "-lPosts", username, choice, str(limit)], stdout=subprocess.PIPE)
    for l in out.stdout:
        line = l.decode("utf-8")
        if line.startswith("Stream: "):
            stream = line[8:]
            streams.append(stream[:-1])

    for key, value in Counter(streams).items():
        try:
            subprocess.check_call(["./db", "-updateR", username, key, str(value)])
        except subprocess.CalledProcessError:
            print("Error: executing your file go check it out")
        except OSError:
            print("Error: executable not found")
    print("All posts marked as read")
    print("</body>")
    print("</html>")
