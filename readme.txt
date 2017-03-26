Assignment 4
Rhys Young
March 31st, 2017
0925398

Description:
This program is used to write and read streams. It also has a basic priviledge
system so that if you are not a user in the stream it will not let you post to it
or read from it. It is written in c lite, c, python and php.

How to use:
1. Make sure you are in the main project folder (a3)
2. Run this command in terminal: make
3. Go to your web browser and follow the on screen instructions

Explanation of buttons:
Previous post: goes to the previous post
Sorting: toggles sorting from time to name and back
Mark all read: Marks all messages in the current stream as read
Check for new posts: loads new posts and displays the first one
Select new Stream: lets you choose a new stream
Change Author: lets you change author (goes back to login screen)
Add or remove author: lets you add or remove an author
Post new message: lets you post a new message
Next post: loads the next post in the stream and displays it.

TO RUN PARSER:
4. while in a3 folder invoke parser with ./parser <file>

Added functionality:
.k - add author
.c - add post
.T - text area

Test Plan:
For testing the program I extensively tested the different inputs that could be used in the files
ensuring that nothing would crash it this includes spaces between names and invalid credentials etc. As listed above.

Limitations/Design decisions:
    - If you put " in any text field except for post make sure u escape it!
    - There is no button to go back to view the same post you just saw if you click away to another page, just use next post and previous post
    - Do not use edge or explorer to test as some features may not work due to microsoft speciality
