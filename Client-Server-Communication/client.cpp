#include<iostream>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<sstream>
#include<string.h>
#include<iomanip>
#include<ctime>
#include<sys/time.h>
#include<fstream>

#define PORT 3112
using namespace std;
struct timespec st,end;
int connection;
bool chk2;
//using namespace std::chrono;

//----------------------------------- To check the time delay in communication and disconnect server-------------

void* thread3(void* arg){
        pthread_detach(pthread_self());
	while(chk2)
		continue;

        while(1){
                clock_gettime(CLOCK_MONOTONIC,&end);
                int tim=end.tv_sec-st.tv_sec;
		//cout<<tim;
		// Time delay threshold is 10 sec
		if(tim>11){
                        cout<<"\n\n<---- Communication delay threshold reached ---->\n\n";
                        cout<<"Server Disconnecting\n\n";
                        close(connection);
                        exit(0);

                }

        }
}


// CLIENT CODE
int main(){

	connection=socket(AF_INET, SOCK_STREAM,0);
	struct sockaddr_in server_addr;
	chk2=true;

	pthread_t pid;
        pthread_create(&pid,NULL,&thread3,NULL);
	//cout<<sock<<endl;
	//cout<<"Client Code\n";
	
	if(connection<0){
		cout<<"\n Socket Creation Failed\n";
		exit(EXIT_FAILURE);
	}
	
	server_addr.sin_family= AF_INET;
	server_addr.sin_port=htons(PORT);

	if(inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr)<=0){
		cout<<"\n Invalid address\n";
		exit(EXIT_FAILURE);
	}
	if(connect(connection,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		cout<<"Connection Failed\n";
		exit(EXIT_FAILURE);	
	}
	cout<<"----------------------------------------------------------------------------------";
cout<<"\n\nServer Conection Stablished through PORT: "<<server_addr.sin_port<<endl<<endl;
	
//----------------------------------USERNAME PASSWORD-----------------------------
	
	char usr[10],pass[10];
	cout<<"login as: ";
	cin>>usr;
	cout<<"Password: ";
	cin>>pass;
	ofstream in("LOG.txt");
	send(connection,usr,strlen(usr),0);
	send(connection,pass,strlen(pass),0);
	char chk[20];

	time_t now=time(0);
	char* cal=ctime(&now);
	//clock_gettime(CLOCK_MONOTONIC,&cal);
	in<<"\n\nCompunication Established at- "<<cal<<" \n\n\n";
	
	chk2=false;
	clock_gettime(CLOCK_MONOTONIC,&st);
			
	//for(int i=0;i<20;i++)
	//	chk[i]='\0';

	int xds=read(connection,chk,20);
	chk[xds]=0;
	if(strcmp(chk,"OK")!=0){
	
		cout<<chk<<endl;
		close(connection);
		//main();
		return 1;
	}
	//cout<<chk;
	char server_msg[80];
	char client_msg[80]="Greetings from Client...";
	//usleep(1000);
	send(connection,client_msg,strlen(client_msg),0);
	//cout<<"Message Sent::: "<<endl;
	 in<<setw(8)<<"Client:- "<<left<<setw(20)<<client_msg<<"  ->  "<<cal;

	//int val=read(connection,server_msg,80);
	//cout<<server_msg<<endl<<endl;
	
	cout<<"\n\nSEND MESSAGE TO SERVER::\n\n";
	//cin.getline(client_msg,80);
	//cout<<client_msg<<endl<<endl;
	while(true){
		clock_gettime(CLOCK_MONOTONIC,&st);
		cin.getline(client_msg,80);
		send(connection,client_msg,strlen(client_msg),0);

		in<<setw(8)<<"Client:- "<<left<<setw(20)<<client_msg<<"  ->  "<<cal;
		//char chk2[5];
		//int sds=read(connection,chk2,5);
		//cout<<chk2;
		clock_gettime(CLOCK_MONOTONIC,&end);
		if(strcmp(client_msg,"quit")==0 || end.tv_sec-st.tv_sec>10)
			break;
			
	}
	cout<<"\n\nServer Disconnected......\n\n";
	 cout<<"----------------------------------------------------------------------------------\n";
	
	//send(connection,client_msg,strlen(client_msg),0);
	pthread_join(pid,NULL);
        pthread_exit(NULL);
	close(connection);
	return 1;
	in.close();
}
