## [Sending Structure through UDP protocal](https://github.com/charlie219/Nevaeh-Technology/tree/main/Send_Structure_Through_UDP)
<p>
    This is a data dispensing server, which will send N no. of packets having the structure mentioned below to a given IP PORT over UDP protocol. The sending data should be in the provided structure formate. For this program, the input is provided under input.txt file.
</p>
<p>
  Communicating Structure:
      
      struct comm_struct {
            int sequence;
            char * name;
            char phone_no[13];
            double salary;
      };
</p>
<p>
    We have to capture the packets through tcpdump command and save the captured packets in a .pcap file. We have to write another program decode.cpp which will interprete the data of unreadable .pcap file, extract the structure and save it in an text file. There should not be any excess or unwanted data transmission as to reduce the UDP traffic.
</p> 

   ### RUNNING:
     
   - First Terminal
          
          cd Nevaeh-Technology/Client-Server-Communication
          make
          sh tcp.sh
          
   - Second Terninal
     
          cd Nevaeh-Technology/Client-Server-Communication
          ./server.exe
          
          .
          .
          .
          .(After the Packets are sent)
          
          ./decode.exe
          

  ### TCPDUMP Command Used:
    
   Interface: Local (lo)
   
   Capture and Display the Packet in HexaDecimal
        
        tcpdump -XX -i lo       
        
   Capture, Display and  Save it in .pcap file
   
        tcpdump  -XX -w first.pcap -i lo
    
   Read a .pacp File in Hexadecimal
   
        tcpdump -r XX first.pcap
        
   
