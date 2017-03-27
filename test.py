#!/usr/bin/python3
import subprocess
import os, sys
from collections import Counter

streams = []
out = subprocess.Popen(["./db", "-lPosts", "rhys", "cow", "2"], stdout=subprocess.PIPE)
for l in out.stdout:
    line = l.decode("utf-8")
    if line.startswith("Stream: "):
        stream = line[8:]
        streams.append(stream[:-1])

for key, value in Counter(streams).items():
    try:
        subprocess.check_call(["./db", "-updateR", "rhys", key, str(value)])
    except subprocess.CalledProcessError:
        print("Error: executing your file go check it out")
    except OSError:
        print("Error: executable not found")
print("All posts marked as read")
