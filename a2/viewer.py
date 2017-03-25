#!/usr/bin/python3
import os, sys
import curses
from datetime import datetime

def checkArgs(args):
    """
        checks to make sure args are right
    """
    if args == 1:
        print("Please enter in a username with the arguement<br>")
        exit()

def userChoice(groups):
    """
        gets the user choice
    """
    if groups:
        choice = input("")
        while choice not in groups and choice != "all":
            print("Invalid choice: please enter one of the options.<br>")
            choice = input("")
        if choice != "all":
            for group in groups:
                if group != choice:
                    groups.remove(group)
        return groups
    else:
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

def readNewMessage(fileName, username, allMessages, limit):
    """
    sets a new message or all messages to read for a given user
    """
    messageCount = countLines(fileName + "StreamData")
    #check to make sure not all the messsages are read
    messagesRead = getMessagesRead(fileName, username)
    if messagesRead == messageCount or messagesRead == limit:
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
                messagesRead = str(messageCount) + '\n'
        lineStr = lineStr + ' ' + messagesRead
        lines.append(lineStr)
    f.close()

    f = open(os.getcwd() + "/a2/messages/" + fileName + "StreamUsers", 'w')
    for line in lines:
        f.write(line)
    f.close()


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

def storeMessages(fileName, username):
    """
    stores the messages for a given user in a given stream and returns it as al ist
    """
    #find out how many messages have been read by the user
    messagesRead = getMessagesRead(fileName, username)
    #gets indexes so we know where each message stops
    indexes = []
    f = open(os.getcwd() + "/a2/messages/" + fileName + "StreamData")
    for line in f:
        indexes.append(int(line))
    f.close()
    f = open(os.getcwd() + "/a2/messages/" + fileName + "Stream")
    read = []
    unread = []
    byte = i = hitNewLine = 0
    currentElement = ""
    currentMessage = []
    #goes through messages storing them
    for line in f:
        #goes through each character in line
        for char in line:
            byte += 1
            currentElement = currentElement + char
            if char == '\n' and hitNewLine < 2:
                currentMessage.append(currentElement)
                hitNewLine += 1
                currentElement = ""
            if indexes[i] == byte:
                currentMessage.append(currentElement)
                currentMessage.append(fileName);
                if i >= messagesRead:
                    unread.append(currentMessage)
                else:
                    read.append(currentMessage)
                currentElement = ""
                hitNewLine = 0
                currentMessage = []
                i += 1
    f.close()
    return read, unread

def sortList(list, type):
    """
    sorts the list either by name or by time
    """
    #true for name
    if type == True:
        list.sort(key=lambda author : author[0])
    else: #false for time
        list.sort(key=lambda date : datetime.strptime(date[1].split(": ")[1], "%b. %d, %Y %I:%M %p\n"))
    return list

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

def getMessages(choices, username):
    """
    gets the messages calling store messages returns read and unread lists
    """
    firstTime = True
    for choice in choices:
        if firstTime == True:
            results = storeMessages(choice, username)
            read = results[0]
            unread = results[1]
            firstTime = False
        else:
            results = storeMessages(choice, username)
            read = read + results[0]
            unread = unread + results[1]
    return read,unread

def countChars(arr):
    """
    counts the chars in a message returns count
    """
    count = 0
    for message in arr[:-1]:
        for char in message:
            count += 1
    return count

def countNewLines(all, spot):
    """
    counts the new lines in a message from a given spot returns count
    """
    count = 23
    for messages in reversed(all[:spot]):
        for message in reversed(messages[:-1]):
            for splitMessage in reversed(message.splitlines()):
                count -= 1
        count-= 2
    return count

def displayMessages(read, unread, username, spot, sorted, limit):
    """
     displays the messages for the world to see
    """
    count = x = lastspot = 0
    all = read + unread
    all = all[:limit]
    newRead = all[:len(read)]
    newUnread = all[len(read):]
    if sorted == True: #means name sorted
        newUnread = sortList(newUnread, True)
        newRead = sortList(newRead, True)
        all = newRead + newUnread
    startRead = len(read)

    #### PROBLEM IS HERE M8
    if spot == 0 and startRead != len(all):
        spot = startRead

    if spot >= len(all): #went past last message
        print("Reached end of messages<br>")
        print("Hit previous post to view older messages <br>")
    else:
        lastspot = spot
        messages = all[spot]
        print("Stream: " + messages[3] + "<br>")
        for message in messages[:-1]:
            print(message, end = "<br>")
        if (sorted == False): #sets messages to read(only works in time sorted order)
            readNewMessage(messages[3], username, False, limit)
            count = 0

    return spot, count, lastspot

def main(read, unread, choices, username, sorted, spot, limit):
    """
    the main method sets up curses and manages the rest of the program
    """
    #sets stuff up
    lastchar =  lastspot = 0
    read = sortList(read, False)
    unread = sortList(unread, False)
    spot, lastchar, lastspot = displayMessages(read, unread, username, spot, sorted, limit)

if __name__ == "__main__":
    checkArgs(len(sys.argv))
    sys.argv.pop(0)
    sortParam = int(sys.argv.pop())
    if sortParam == 1:
        sorted = True
    else:
        sorted = False
    limit = int(sys.argv.pop())
    spot = int(sys.argv.pop())
    choice = sys.argv.pop()
    username = ' '.join(map(str, sys.argv))
    groups = listGroups(username)
    if choice == "all":
        results = getMessages(groups, username)
    else:
        choices = []
        choices.append(choice)
        results = getMessages(choices, username)
    main(results[0], results[1], choice, username, sorted, spot, limit)
    print("</body>")
    print("</html>")
