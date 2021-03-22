#Makefile by Akash Kumar Bhagat
#Variable Declaration
CROSS_TOOL=
CC_CPP=$(CROSS_TOOLS)g++

CFLAGS= -Wall -pthread

#Compiling server.cpp and client.cpp
all:
	g++ server.cpp -o server.exe -pthread
	g++ decode.cpp -o decode.exe -lpcap 

clean:
	rm -f server.exe

