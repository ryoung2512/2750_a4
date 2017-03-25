#!/usr/bin/python3
import os, sys

def checkArgs(args):
    """
        checks to make sure args are right
    """
    if args == 1:
        print("Please enter in a username with the arguement<br>")
        exit()

def countLines(fileName):
    """
    counts the lines in a file"
    """
    f = open(os.getcwd() + "/a2/messages/" + fileName + "StreamData")
    count = 0
    for line in f:
        count += 1
    f.close()
    return count

def hasAccess(fileName, username):
    """
    checks to make sure the user has access
    """
    f = open(os.getcwd() + "/a2/messages/" + fileName)
    for line in f:
        lineArr = line.split(" ")
        lineArr.pop() #removes last element in array
        lineStr = ' '.join(map(str, lineArr))
        if lineStr == username:
            f.close()
            return 1
    f.close()
    return 0

def listGroups(username):
    """
    lists the streams available to the user
    """
    groups = os.listdir(os.getcwd() + "/a2/messages/")
    accessibleGroups = []
    for group in groups:
        if group.endswith("StreamUsers"):
            if hasAccess(group, username) == 1:
                accessibleGroups.append(group[:-11])
    if not accessibleGroups:
        print("Sorry unable to find any groups for " + username + ". Please add some using addauthor!<br>")
    return accessibleGroups

if __name__ == "__main__":
    checkArgs(len(sys.argv))
    sys.argv.pop(0)
    choice = sys.argv.pop()
    username = ' '.join(map(str, sys.argv))
    groups = listGroups(username)
    count = 0
    if choice == "all":
        for group in groups:
            count += countLines(group)
    else:
        count += countLines(choice)
    print(count)
