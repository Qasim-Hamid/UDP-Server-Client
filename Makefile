CXX = g++ -std=c++11

DSTS = client intermediate_host

all: $(DSTS)

clean:
	rm $(DSTS)

client: client.cpp 
intermediate_host: intermediate_host.cpp 
