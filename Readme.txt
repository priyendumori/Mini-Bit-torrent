                                    Name: Priyendu Mori
                                    Roll no: 2018201103
####################################### Mini Bit Torrent ##################################

Compiling and running:
-> Code is divided in folders: client and tracker
-> Both folders have corresponding Makefile. Use "make" in both folders to compile
-> To run client:
    ./client_2018201103 <CLIENT_IP>:<UPLOAD_PORT> <TRACKER_IP_1>:<TRACKER_PORT_1> <TRACKER_IP_2>:<TRACKER_PORT_2> <log_file>
-> To run tracker:
    ./tracker_2018201103 <my_tracker_ip>:<my_tracker_port> <other_tracker_ip>:<other_tracker_port> <seederlist_file> <log_file>

Points to be noted about the implementation:
-> Only one tracker is implemented
-> Spaces in file name should be escaped by \
-> Relative and absolute paths are supported
-> Downloading occurs only from one peer in chunks of 512KB
-> All the mTorrent files should be present in client/mTorrent folder