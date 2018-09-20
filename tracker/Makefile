CC = g++
CFLAGS = -Wall -std=c++14 
FLAGS = -lssl -lcrypto -lpthread
DEPS = header.h trackerglobal.h
OBJ = trackerglobal.o seeder_file_handler.o sock.o send_seeder_list.o  tracker.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

tracker: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(FLAGS)

clean:
	rm -f *o
