# Nevaeh-Technology

###    This repository contains the Training projects, Assignment and Projects made during internship at [Nevaeh Technology](http://nevaehtech.com/).



## [Client Server Interaction using Socket in C++](https://github.com/charlie219/Nevaeh-Technology/tree/main/Client-Server-Communication)
<p>
   This is a Socket program which enables on way communication (Client -> Server) and store the communication in a LOG.txt. The Server is secured with a username and password which ensures the server security. The Server connection disconnects iff either the Client send "quit" to the Server or the comunication delay is more than 10 sec. The interaction is stacked in a text file named LOG.txt which is created during the execution of the program.
</p>
<p>
   If the client is inactive till a pariticular threshold value(say 10 sec), the server and client will automatically get disconnected. I have used threading concept in C++ to keep a track of the time that passes and checks if the client is inactive till a threshold value. If the threshold is reached, the socket is closed and both the server as well as client terminates.
</p> 

   ### RUNNING:
     
   - First Terminal
          
          cd Nevaeh-Technology/Client-Server-Communication
          make
          ./server.exe
          
   - Second Terninal
     
          cd Nevaeh-Technology/Client-Server-Communication
          ./client.exe
          
   - Server Login from Client:
   
                login as: akash     
                Password: 123455
