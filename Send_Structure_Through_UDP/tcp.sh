echo "tcpdumb Commands running...."

#Capture and Display in HEX
#tcpdump -c 12 -XX -i lo
#tcpdump -r first.pcap


# Capture  and savw
tcpdump -c 12 -XX -w first.pcap -i lo
