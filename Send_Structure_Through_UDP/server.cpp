#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <bitset>

#pragma pack(1)
using namespace std;

struct comm_struct{
	int sequence;	// 	4
	char phone_no[13];//	13
	double salary;//	8
};

struct comm_struct2{
	char *name;
};

void Exit(const char* msg){
	cout<<msg<<endl;
	exit(0);
}

int main(int argc , char *argv[]){
	
	// Number of Packets
	int n=10;
	// Server and Client Address
	struct sockaddr_in server_addr,client_addr;
	int PORT,conn;
	char* IP;

	if(!argv[2])
		Exit("Port not provided");

	if(!argv[1])
		Exit("IP not provided");

	PORT=atoi(argv[2]);
	IP=argv[1];
	cout << "\nIP:- " << IP << endl ;	
	cout << "PORT:- " << PORT << endl ;
	// Create Socket
	conn=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(conn<0)
		Exit("Socket Creation Failed");
	
	//memset(&server_addr,0,sizeof(server_addr));
	memset(&server_addr, 0, sizeof(server_addr)); 
    	memset(&client_addr, 0, sizeof(client_addr));
	int len=sizeof(server_addr);	

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(IP);
	server_addr.sin_port = htons(PORT);

	if(bind(conn,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
		Exit("Binding Failed");

//--------------------------------------- Input -------------------------------
	
	ifstream file("input.txt");
	string line;
	int var;
	cout<<sizeof(comm_struct)<<endl;

	while(getline(file,line)){
		int count=0;	
		line+=' ';
		comm_struct temp;
		comm_struct2 data;
		int i=-1;
		for(int ii=0 ; ii < 4 ; ii++){
			string word;
			count++;
    			char x ;
    			word.clear();
        		x = line[++i];

        		while ( x != ' ' )
        		{
            			word = word + x;
            			x = line[++i];
        		}
			
			if(count==1)
				temp.sequence=atoi(word.data());

			if(count==2){
				//cout<<word;
				var=word.length();
				char *nam;
                                nam= (char *)calloc(n+1,sizeof(char));
				strcpy(nam,word.c_str());
		
				data.name = nam;
				//cout << endl << data.name << nam;		
			}
			if(count==3){
				strncpy(temp.phone_no,word.c_str(), sizeof(temp.phone_no));
				temp.phone_no[13]='\0';
			}		
			if(count==4)
				temp.salary=atof(word.data());
//			cout<<temp.sequence<<endl;
			word.clear();
		}
		
		char * send_data;
		int len2=strlen(data.name);
		send_data = new char[sizeof(int) + len2+1]();
		memcpy(send_data , &len2 , sizeof(int));
		memcpy(send_data + sizeof(int) , data.name, len2+1);
		
		//cout<<data.name<<" -> "<<send_data+sizeof(int);		
		
		//cout<< "PTR: " <<temp.name<<endl;
		 if (sendto(conn,&temp, sizeof(temp),0,(struct sockaddr*)&server_addr,len)<0){
			cout<<"Packet of Sequence Number:- "<<temp.sequence<<" not sent";
		}

                else{
			if(sendto(conn , send_data , sizeof(int)+strlen(data.name),0,(struct sockaddr*)&server_addr,len)> 0)
                                cout<<"Packet of Sequence Number:- "<<temp.sequence<<" sent";
                        else
                                cout << "Error Occred...\n\n";

//                        cout<<"\nPacket of Sequence Number:- "<<temp.sequence<<" sent";
		}
                cout<<endl;
                sleep(1);

	}
	//string nam="Akash";
	//comm_struct temp={123,"Akash",{'+','9','1','7','8','0','8','7','9','8','3','2','0'},1235.5};
	//cout<<sizeof(temp)<<"**"<<sizeof(comm_struct);	
/*
	for(int i =0;i<n;i++){
		temp.sequence=i+1;
	
		if(sendto(conn,&temp, sizeof(temp),0,(struct sockaddr*)&server_addr,len)<0)
			cout<<"Packet number "<<i+1<<" not sent";

        	else
                	cout<<"Packet number "<<i+1<<" sent";
		cout<<endl;
		sleep(1);
	}
*/
	close(conn);
	return 1;
}
