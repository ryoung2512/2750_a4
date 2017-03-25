#!/usr/bin/python3
import os, sys

def countLines(fileName):
    """
    counts the lines in a file"
    """
    f = open(os.getcwd() + "/a2/messages/" + fileName)
    count = 0
    for line in f:
        count += 1
    f.close()
    return count

def getMessagesRead(fileName, username):
    """
    returns how many messages a user has read
    """
    read = 0
    f = open(os.getcwd() + "/a2/messages/" + fileName + "StreamUsers")

    for line in f:
        lineArr = line.split(" ")
        messagesRead = lineArr[-1]
        lineArr.pop() #removes last element in array
        lineStr = ' '.join(map(str, lineArr))
        if lineStr == username:
            read = int(messagesRead)
            break
    f.close()
    return read

def checkArgs(args):
    """
        checks to make sure args are right
    """
    if args < 4:
        print("Please enter in the appropriate number of arguments")
        exit()

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

def readNewMessage(fileName, username, allMessages, limit):
    """
    sets a new message or all messages to read for a given user
    """
    messageCount = countLines(fileName + "StreamData")
    #check to make sure not all the messsages are read
    if getMessagesRead(fileName, username) == messageCount:
        return

    f = open(os.getcwd() + "/a2/messages/" + fileName + "StreamUsers")
    lines = []

    for line in f:
        lineArr = line.split(" ")
        messagesRead = lineArr[-1]
        lineArr.pop() #removes last element in array
        lineStr = ' '.join(map(str, lineArr))
        if lineStr == username:
            if allMessages == False:
                messagesRead = str(int(messagesRead) + 1) + '\n'
            else:
                messagesRead = str(limit) + '\n'
        lineStr = lineStr + ' ' + messagesRead
        lines.append(lineStr)
    f.close()

    f = open(os.getcwd() + "/a2/messages/" + fileName + "StreamUsers", 'w')
    for line in lines:
        f.write(line)
    f.close()

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
        print("Sorry unable to find any groups for " + username + ". Please add some using addauthor!")
    return accessibleGroups

if __name__ == "__main__":
    checkArgs(len(sys.argv))
    sys.argv.pop(0)
    limit = int(sys.argv.pop())
    allMessages = sys.argv.pop()
    choice = sys.argv.pop()
    username = ' '.join(map(str, sys.argv))
    setAll = False
    groups = listGroups(username)
    if allMessages == "1":
        setAll = True
    if choice == "all":
        for g in groups:
            readNewMessage(g, username, setAll, limit)
        print("All messages in all streams have been marked as read!")
    else:
        readNewMessage(choice, username, setAll, limit)
        print("All messages in " + choice  + " have been marked as read!")
    print("</body>")
    print("</html>")
