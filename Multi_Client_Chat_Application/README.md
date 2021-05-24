# [Multi Client chat Application (with select() function)](https://github.com/charlie219/Nevaeh-Technology/tree/main/Multi_Client_Chat_Application)

This is a Command Line chatting Applicatiion which enables clients to either create chating groups or join an already existing group. 
The program consist of a server.cpp file which uses select() to handle multiple clients trafic. 

When you run the client, you recieve a menu to either create group or chat. If you select create group, a new group will be created with a random 4 digit ID. The 
Group Id will flash on the screen and the user can share it to their friends to chat with them. 

## RUNNING:

    cd Nevaeh-Technology/Multi_Client_Chat_Application
    make
    ./server
    
Now open several Putty terminals and enter the following IP/PORT
    
           IP       :-  127.0.0.1
          PORT      :-  3112
    Connection Type :-  RAW
 
Rest is user friendly
