Assignment 4
Rhys Young
March 31st, 2017
0925398

Description:
This program is used to write and read streams. It also has a basic priviledge
system so that if you are not a user in the stream it will not let you post to it
or read from it. It is written in c lite, c, python, php and SQL.

How to use:
1. Untar in the directory you want and run make
2. Go to your web browser and follow the on screen instructions

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

TO RUN DB:
3. while in folder invoke the DB with ./db <command>
   NOTE: use ./db -help for help.
   NOTE: In order to use these commands initially you will want to use the webpage and addauthor, since no tables are created
        until that happens.

Test Plan:
For testing the program I extensively tested the different inputs that could be used in the files
ensuring that nothing would crash it this includes spaces between names and invalid credentials etc. As listed above.

Limitations/Design decisions:
    - If you put " in any text field make sure u escape it!
    - There is no button to go back to view the same post you just saw if you click away to another page, just use next post and previous post
    - Do not use edge or explorer to test as some features may not work due to microsoft speciality
