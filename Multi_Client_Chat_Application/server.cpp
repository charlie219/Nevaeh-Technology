# include <iostream>
# include <sys/socket.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
//# include <chrono>
//# include <stdio>
# include <bits/stdc++.h>
# include <netinet/in.h>
# include <sys/time.h>
# include <iomanip>
# include <sstream>
# include <vector>
# define PORT 3112

using namespace std;

// Global variables
struct timespec inter,cur;
int server_socket;
bool chk;
unordered_map<int, vector<int>> group;
unordered_map<int,int> client_group;
// SERVER CODE

void error_msg(){

	cout << "Socket INitilization failed";
	exit(0);
}

int make_group(int client_id){
	

	srand(time(NULL));
	int new_group = rand() % 9999 + 1;
	cout <<"New Group Created: " << new_group << endl;

	group[new_group].push_back(client_id);
	client_group[client_id] = new_group;
	return new_group;

}

bool join_group(int client_id, int group_id){
	if(group.find(group_id) == group.end())
		return false;
	ostringstream ss;
	ss << "\n\r\n\rClient #" << client_id << " Joint the group \n\r\r";
	string join_msg = ss.str();

	// To notify other group members of the joining of a new client
	for(int i = 0 ; i < group[group_id].size(); i++){
		int group_member = group[group_id][i];
		send(group_member, join_msg.c_str(), join_msg.size(), 0);
	}
	group[group_id].push_back(client_id);
	client_group[client_id] = group_id;
	return true;
}

void leave_group(int client_id){

	int group_id = client_group[client_id];
	remove(group[group_id].begin(), group[group_id].end(), client_id);
	client_group.erase(client_id);
	ostringstream ss;
	ss << "\n\r\n\rClient #" << client_id << " left the group\n\r\r";
        string leave_msg = ss.str();
	for(int i = 0 ; i < group[group_id].size(); i++){
                int group_member = group[group_id][i];
                send(group_member, leave_msg.c_str(), leave_msg.size(), 0);
	}
}


int main(){
	struct sockaddr_in addr;			// Socket Adress
	int optional = 1;
	chk = true;		
	int new_client[256];		//	To detect new client
	memset(new_client , 0 , 256*sizeof(int));
	char buffer[2048];
	//ostringstream ss;

	cout << "------------------------------------------------------------------------\n";
	//cout << "\n\nSERVER RUNNING\n" << endl;
	server_socket = socket(AF_INET, SOCK_STREAM,0);
	//cout<<conn<<endl;

	// Checking if the Socket is failed -> Exit
	if(server_socket == 0){

		error_msg();
	}

	// Initilising setsockopt for reusibility of code
	if(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optional, sizeof(optional))){
		cout<<"setsockopt";
		error_msg();
	}
	
	// Initilizing the socket address 
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);

	
	// Attaching the Socket to the PORT
	if(bind(server_socket, (struct sockaddr*)&addr, sizeof(addr))<0){
		cout << "Binding Failed";
		error_msg();
	}
	if(listen(server_socket, 3)<0){
		cout << "listening Failed";
		error_msg();
	}


	cout << "\n\nSERVER IS RUNNNING::\n\r";	
	int socket_addr_len = sizeof(addr);	
	// Make fd_set and set server_socket in it
	
	
	int fd_max = server_socket;	
       	fd_set server;
        FD_ZERO(&server);
        FD_SET(server_socket, &server);

	while(true){

		// Every time the select function runs, it destroyes the previous fd_set
		fd_set copy = server;
		//FD_ZERO(&copy);
		//FD_SET(server_socket, &copy);
		int max_sock = select(fd_max + 1, &copy, nullptr, nullptr, nullptr);
		for(int sock = 0 ; sock <= fd_max; sock++){

			if(FD_ISSET(sock, &copy)){
			
				// Accept new connection and add it to the fd_set
			//	char buffer[2048];
				if(sock == server_socket){
					int client = accept(server_socket, (struct sockaddr*)&addr,(socklen_t*)&socket_addr_len);
					if(client < 0)
						cout << "Error in connection";
					//int client = accept(server_socket, );
					FD_SET(client, &server);
					if(client > fd_max){
						fd_max = client;
					}

					// Greetings to the new clent
					ostringstream ss;
			//
					cout << "New Client - #" << client << " connected\n";
					ss << "Welcome to the Comandline Chating application \n\rClient #" << client << "\n\rEnter an option \n\r1...Creat Group \n\r2...Join A Group\n\rEnter your Choice :- ";
					string hello = ss.str();
					send(client, hello.c_str(), hello.size(), 0);
					new_client[client] = 1;
					FD_SET(client, &server);
					//buffer[0] = '\0';
					//int MSG_LEN = recv(server_socket, buffer, 2048, 0);
					//cout << buffer ;


				}
				else{
					// recive the message and distrbute the message to similar group ids
					
					memset(buffer, '\0', 2048);
			
					int msg_len = recv(sock, buffer, 2048, 0);
					
			//		buffer[2] = buffer[1];
			//		buffer[1] = ' ';
					string st = buffer;
					if(st.size() == 2)
						continue;

					// Cilent disconnected
					if(msg_len <= 0){
						//string msg = "Disconnecting from server...";
						leave_group(sock);
						cout << "Client #" << sock << " disconnected\n";
						FD_CLR(sock, &server);
						//send(sock, msg.c_str(), msg.size(), 0);
						//close(sock);
					}

					else if(new_client[sock] == 2){

						//cout << "**" << buffer << "**\n";
                                                int group_id = atoi(buffer);
						if(group_id == 0)
							continue;
                                                chk = join_group(sock, group_id);
                                                if(not chk){
                                                        string msg = "\n\nIncorrect Group ID...... Try again \n\n\r\r";
                                                        send(sock, msg.c_str(), msg.size(), 0);
                                                }
                                                else{
                                                        string msg = "\n\n\n WELCOME to the Group \n\n\r\r";
                                                        send(sock, msg.c_str(), msg.size(), 0);
                                                        new_client[sock] = 0;
                                                }
                                        }

					// New client detected , recieve option 
					else if(new_client[sock] == 1){
                                                //cout << "New Client\n";
                                                //new_client[sock] = 0;
						
						int opt = atoi(buffer);
						// Create a new Group
                                                if(opt == 1){
							int new_group = make_group(sock);
							ostringstream new_group_msg;
							new_group_msg << "\n\n\r\rGroup Created.....\n\rGroup ID:- " << new_group << "\n\rShare the group id to invite your friends...\n\r";
							string msg = new_group_msg.str();
							send(sock, msg.c_str(), msg.size(), 0);	
							new_client[sock] = 0;
						}

						// Join an existing group 
						else if(opt == 2){
                                                        string msg = "\n\nEnter the Group ID:- ";
                                                        send(sock, msg.c_str(), msg.size(), 0);
							new_client[sock] = 2;
						}

						// Incorrect option, make the clent new again
						else{
							//cout << "Incorrect Option.... Try again\n";
							//new_client[sock] = 1;
							string msg = "\n\rIncorrect Option ID...... Try again \n\r";
                                      			send(sock, msg.c_str(), msg.size(), 0);
						}
                                        }

					else{
				                //string st = buffer;
						//cout << "**" << buffer[0] << "**" << buffer[1] << endl;
                	                        
						//cout << st << st.size();

						int group_id = client_group[sock];
						if(strcmp(buffer, "leave") == 0){
							
							leave_group(sock);
							cout << "Client #" << sock << " left\r\n";
							FD_CLR(sock , &server);
							close(sock);
						}
						else{
							//cout << group_id << " " << sock << endl;
							for(int i = 0 ; i < group[group_id].size() ; i++){
								int group_member = group[group_id][i];
								//cout << group[group_id].size() << endl;
								if(group_member != sock){
									ostringstream ss;
									ss << "Client #" << sock << " : " << buffer << "\n\r";
									string msg = ss.str();
									send(group_member, msg.c_str(), msg.size(), 0);
								}
							}
						}
					}
				}
			}
		}
	}	

	close(server_socket);
	//close(new_socket);
	return 0;
}

