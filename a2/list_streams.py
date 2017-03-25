#!/usr/bin/python3
import os, sys

def checkArgs(args):
    """
        checks to make sure args are right
    """
    if args == 1:
        print("Please enter in a username")
        print("</body>")
        print("</html>")
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
    if accessibleGroups:
        print("<form action=\"viewer.php\" method=\"post\">")
        count = 0
        for g in accessibleGroups:
            if count == 0:
                print(g + ": <input type=\"radio\" checked=\"checked\" name=\"stream\" value=\""+ g +"\"/><br>")
                count = 1
            else:
                print(g + ": <input type=\"radio\" name=\"stream\" value=\""+ g +"\"/><br>")
        print("all: <input type=\"radio\" name=\"stream\" value=\"all\"/><br>")
        print("<input type=\"hidden\" name=\"username\" value=\""+ username +"\"/>")
        print("<input type=\"hidden\" name=\"counter\" value=\"0\"/>")
        print("<input type=\"hidden\" name=\"sorted\" value=\"0\"/>")
        print("<input type=\"hidden\" name=\"name\" value=\"choose\"/>")
        print("<input type=\"submit\" value=\"choose\"/>")
        print("</form>")
    else:
        print("Sorry unable to find any groups for " + username + ". Please add some using addauthor!")
    return accessibleGroups

if __name__ == "__main__":
    checkArgs(len(sys.argv))
    sys.argv.pop(0)
    username = ' '.join(map(str, sys.argv))
    listGroups(username)
    print("</body>")
    print("</html>")
