CXX = g++ -std=c++11
CC 	= $(CXX)

DSTS = client intermediate_host host

all: $(DSTS)

clean:
	rm $(DSTS)

client:   client.o
intermediate_host:  intermediate_host.o 
host: host.o

client.o: client.cpp Datagram1.h
intermediate_host.o: intermediate_host.cpp Datagram1.h
host.o: host.cpp Datagram1.h

