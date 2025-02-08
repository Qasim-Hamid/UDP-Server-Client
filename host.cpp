#include <chrono>
#include <thread>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include "Datagram1.h"

#define INTERMEDIATE_HOST 23
#define SERVER 69

class Host {
private:
    DatagramSocket IntermediateSocket;

public:
    Host() : IntermediateSocket(SERVER) {}

    void receiveIntermediate() {

        std::vector<uint8_t> intermediateData(100);
        DatagramPacket intermediatePacket(intermediateData, intermediateData.size());
        std::cout << "Server: Waiting for Packet." << std::endl;

        try {
            std::cout << "Waiting..." << std::endl; // so we know we're waiting
            IntermediateSocket.receive(intermediatePacket);
        } catch (const std::runtime_error& e ) {
            std::cout << "IO Exception: likely:"
                  << "Receive Socket Timed Out." << std::endl << e.what() << std::endl;
            exit(1);
        }

        printPacket(intermediateData, intermediatePacket, 0);

    }


    void printPacket(std::vector<uint8_t> packet_data, DatagramPacket packet, int code) {

            if (code == 0) {
            std::cout << "Server: Packet received:" << std::endl;
            std::cout << "From host: " << packet.getAddressAsString() << std::endl;
            std::cout << "Host port: " << packet.getPort() << std::endl;
            int len = packet.getLength();
            std::cout << "Length: " << len << std::endl;
            std::cout << "Packet as string: ";
            std::string received = std::string(static_cast<const char *>(packet.getData()), packet.getLength());
            std::cout << received << std::endl;
        }

        else {
            std::cout <<  "Server: Sending packet:" << std::endl;
            std::cout << "To host: " << packet.getAddressAsString() << std::endl;
            std::cout << "Destination host port: " << packet.getPort() << std::endl;
            int len = packet.getLength();
            std::cout << "Length: " << len << std::endl;
            std::cout << "Packet as string: ";
            std::cout << std::string(static_cast<const char *>(packet.getData()), len) << std::endl; //
        }


		bool first = false;
        std::cout << "Packet as bytes: ";
        for (char i: packet_data)
        {
            if (i <= 0x10) {
                std::cout << std::oct << static_cast<int>(i);
                if (i == 0x0) {

                    if (first == false) {
                        first = true;
                    }
                    else {
                        std::cout << std::endl;
                        std::cout << std::endl;
                        return;
                    }

                }
                else {
                    first = false;
                }
            }

            else {
                std::cout << std::oct << i;
                /* std::cout << std::oct << i; */
                /* std::cout << i; */
            }

        }
        std::cout << std::endl;
        std::cout << std::endl;
	}

};

int main() {

    Host host;
    host.receiveIntermediate();

    return 0;

}
