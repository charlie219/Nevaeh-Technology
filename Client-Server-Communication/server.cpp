#include<iostream>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
//#include<chrono>
#include<netinet/in.h>
#include<sys/time.h>
#include<iomanip>
#define PORT 3112

using namespace std;
struct timespec inter,cur;
int new_socket,conn;
bool chk;
// SERVER CODE

//----------------------------------- To check the time delay in communication and disconnect server-------------
void* thread2(void* arg){
	pthread_detach(pthread_self());
	//cout<<"Inside the thread";
	// Calculate the current time and the diffrence between the intervals
	while(chk){
		continue;
	}
	while(1){
		clock_gettime(CLOCK_MONOTONIC,&cur);
        	int tim=cur.tv_sec-inter.tv_sec;
        	//cout<<inter.tv_sec<<" "<<cur.tv_sec<<" "<<tim<<endl;
        	if(tim>10){
			cout<<"\n\n<---- Communication delay threshold reached ---->\n\n";
			cout<<"Disconnecting Client ....\n\n";
                	close(conn);
                	close(new_socket);
                	exit(0);

        	}

	}	
}


int main(){
	struct sockaddr_in addr;			// Socket Adress
	int optional=1;
	chk=true;
	pthread_t thread;
	pthread_create(&thread,NULL,&thread2,NULL);

	cout<<"------------------------------------------------------------------------\n";
	cout<<"\n\nSERVER RUNNING\n"<<endl;
	conn= socket(AF_INET, SOCK_STREAM,0);
	//cout<<conn<<endl;

	// Checking if the Socket is failed -> Exit
	if(conn==0){

		cout<<"socket Failed"<<endl;
		exit(EXIT_FAILURE);
	}

	// Initilising setsockopt for reusibility of code
	if(setsockopt(conn,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&optional,sizeof(optional))){
		cout<<"setsockopt";
		exit(EXIT_FAILURE);
	}
	
	// Initilizing the socket address 
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr= INADDR_ANY;
	addr.sin_port=htons(PORT);

	
	// Attaching the Socket to the PORT
	if(bind(conn,(struct sockaddr*)&addr,sizeof(addr))<0){
		cout<<"Binding Failed";
		exit(EXIT_FAILURE);
	}
	if(listen(conn,3)<0){
		cout<<"listening Failed";
		exit(EXIT_FAILURE);
	}

	int socket_addr_len=sizeof(addr);
	new_socket=accept(conn,(struct sockaddr*)&addr,(socklen_t*)&socket_addr_len);
	if(new_socket<0){
		cout<<"Didn't Accept";
		exit(EXIT_FAILURE);
	}
	

	struct timespec st,end;
	clock_gettime(CLOCK_MONOTONIC,&st);
	cout<<"\nWaiting For Connection.....\n\n";
//--------------------------- USERNAME PASWORD------------------------------
	
	char usr[10],pass[10];
	int xdd=read(new_socket,usr,10);
	xdd=read(new_socket,pass,10);
	//cout<<usr<<endl<<pass;

	if(strcmp(usr,"akash")!=0 || strcmp(pass,"123455")!=0 ){
	
		cout<<"Unknown Client tried to access\n\n";
		char error[]="Wrong Credentials";
		send(new_socket,error,strlen(error),0);
		//main();
		return 1;
	}

//-------------------------------------- COMMUNICATION----------------------------
	clock_gettime(CLOCK_MONOTONIC,&inter);
	char empty[80]="";	
	
	char client_msg1[80];
	char server_msg[80]="OK";
	send(new_socket,server_msg,strlen(server_msg),0);
	
	int val=read(new_socket,client_msg1,80);
	client_msg1[val]=0;
	cout<<"---------------------------------------------------------------------------------";
	chk=false;
	cout<<"\n\nClient Connection Stablised\n\n";
	cout<<client_msg1<<endl<<endl;
	
	//char client_msg[80];
	//cout<<"Send message to server\n\n";
	//cin>>server_msg;
	//send(new_socket,server_msg,strlen(server_msg),0);
	
	//cout<<"Message Sent"<<endl;
	//val=read(new_socket,client_msg,80);
	//cout<<client_msg<<endl<<endl;
	while(true){
		clock_gettime(CLOCK_MONOTONIC,&inter);
		//clock_gettime(CLOCK_MONOTONIC,&st);
		char msg[890];
		//for(int i=0;i<80;i++)
			//msg[i]='\0';
		int xval=read(new_socket,msg,890);
		msg[xval]=0;
		clock_gettime(CLOCK_MONOTONIC,&end);
		double ti=cur.tv_sec-inter.tv_sec;	
		cout<<setw(20)<<msg;
		cout<<setw(20)<<"  -->  Communication delay  "<<ti<<endl;

		if(strcmp(msg,"quit")==0 || ti>10){
			//char brk[]="YES";
			//send(new_socket,brk,strlen(brk),0);
			break;
		}
		//char brk[]="NO";
                //send(new_socket,brk,strlen(brk),0);


	}
	cout<<"\n\n\nDisconnecting Client....\n\n";
	 cout<<"----------------------------------------------------------------------------------\n";
	
	pthread_join(thread,NULL);
	pthread_exit(NULL);
	close(conn);
	close(new_socket);
	return 0;
	exit(0);
}
