CC = g++
CFLAGS = -Wall -std=c++14 
FLAGS = -lssl -lcrypto
DEPS = header.h
OBJ = mTorrentGenerator.o main.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

torrent: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(FLAGS)

clean:
	rm -f *o
