#include<string>
#include<cstring>
#include<unistd.h>
#include <bitset>
#include<iostream>
#include<pcap.h>
#include<fstream>
#include <sstream>
#include <cstdlib>

#pragma pack(1) 
using namespace std;

struct comm_struct{
        int sequence;
        char phone_no[14];
        double salary;
	char *name;
};

int main(int argc, char *argv[])
{
	string file = "first.pcap";
    	ofstream in("output.txt");
    	char errbuff[PCAP_ERRBUF_SIZE];
 
    	pcap_t * pcap = pcap_open_offline(file.c_str(), errbuff);
    	struct pcap_pkthdr *header;
 
    	const u_char *data;
	struct comm_struct *temp;     	

    	int packetCount = 0;
	
	while (int returnValue = pcap_next_ex(pcap, &header, &data) >= 0)
    	{
		int pak_len = header->len;

		comm_struct pak;
                
       		cout << "Packet # " << ++packetCount << endl;
 		in << "Packet # " << packetCount << endl;

        	//cout<<"Packet size: "<< header->len<<" bytes\n";
 		//in<<"Packet size: "<< header->len<<" bytes\n";
		//cout<<"hey";

        	if (header->len != header->caplen){
        		cout << "Warning! Capture size different than packet size:" << header->len << " bytes\n\n";
	    		in << "Warning! Capture size different than packet size:" << header->len << " bytes\n\n";
 		}

        	int hdr_len = 42;
                int st ;
//------------------------------------------ Sequence ----------------------------

		st = 42;
		//memcpy(&pak.sequence , data+st ,sizeof(int));

//-------------------------------------------Phone Number-------------------------
		
                st+=4;
                //memcpy(pak.phone_no , data + st , 11);

//------------------------------------------- Salary -----------------------------
		
		st+=13;		
		//memcpy(&pak.salary , data + st , sizeof(double));
                
//----------------------------------------- NAME --------------------------------

		st =42;
		memcpy(&pak , data + st , sizeof(int)+ sizeof(char)*11);
                memcpy(&pak.salary , data + st +sizeof(int) + sizeof(char)*13 , sizeof(double));

//		memcpy(&pak , data + 42 , sizeof(int) + sizeof(char) * 11 );
//		memcpy(&pak.salary , data+ st , sizeof(double));
		st+=sizeof(int) + sizeof(char)*13 + sizeof(double) ;
		//returnValue = pcap_next_ex(pcap, &header, &data);
		int str_len;
		memcpy(&str_len , data+st , sizeof(int));
		pak.name = new char[str_len + 1];
		memcpy(pak.name , data+st+ 4 , str_len);
		//cout<<"Nmae "<<str_len<<endl;	

//------------------------------------------ OUTPUT ------------------------------
		
		cout << "-----------------------------------------------------------------\n";
                in << "-----------------------------------------------------------------\n";

		cout << endl << "Sequence:- " << pak.sequence << endl;
                in << endl << "Sequence:- " << pak.sequence << endl;
		
		cout << "Name:- " << pak.name << endl;
                in << "Name:- " << pak.name << endl;

		cout << "Phone Number:- " << pak.phone_no;
                in << "Phone Number:- " << pak.phone_no;

		cout << endl << "Salary: Rs " << pak.salary;
                in << endl << "Salary: Rs " << pak.salary;
			
                cout << "\n\n";
                in << "\n\n";
                cout << "-----------------------------------------------------------------\n";
                in << "-----------------------------------------------------------------\n";
                sleep(1);
    }
}
