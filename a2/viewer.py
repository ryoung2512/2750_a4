#!/usr/bin/python3
import os, sys
import curses
from datetime import datetime
import subprocess

def checkArgs(args):
    """
        checks to make sure args are right
    """
    if args == 1:
        print("Please enter in a username with the arguement<br>")
        exit()

def storeMessages(fileName, username, limit, choice):
    """
    stores the messages for a given user in a given stream and returns it as al ist
    """
    # call messages read to find how many are read
    ret = subprocess.Popen(["./db", "-getRead", username, choice], stdout=subprocess.PIPE)
    messagesRead = 0
    for k in ret.stdout:
        p = k.decode("utf-8")
        try:
           messagesRead += int(p)
        except ValueError:
           return
    read = []
    unread = []
    byte = hitNewLine = 0
    i = 0
    currentElement = ""
    currentMessage = []
    #goes through messages storing them
    while i < limit:
        out = subprocess.Popen(["./db", "-fetchP", username, choice, str(i), "1"], stdout=subprocess.PIPE)
        for l in out.stdout:
            line = l.decode("utf-8")
            for char in line:
                if char == '\n':
                    currentMessage.append(currentElement)
                    currentElement = ""
                else:
                    currentElement = currentElement + char
        # add message
        if i >= messagesRead:
            unread.append(currentMessage)
        else:
            read.append(currentMessage)
        currentElement = ""
        currentMessage = []
        i += 1

    print(read)
    print(unread)
    return read, unread

def sortList(list, type):
    """
    sorts the list either by name or by time
    """
    #true for name
    if type == True:
        list.sort(key=lambda author : author[0])
    else: #false for time
        list.sort(key=lambda date : datetime.strptime(date[1].split(": ")[1], "%b. %d, %Y %I:%M %p"))
    return list

def getMessages(username, limit, choice):
    """
    gets the messages calling store messages returns read and unread lists
    """
    results = storeMessages(choice, username, limit, choice)
    read = results[0]
    unread = results[1]
    return read,unread

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
    if choice == "all":
        results = getMessages(username, limit, choice)
    else:
        choices = []
        choices.append(choice)
        results = getMessages(username, limit, choice)
    main(results[0], results[1], choice, username, sorted, spot, limit)
    print("</body>")
    print("</html>")
