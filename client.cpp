#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>
#include "Datagram1.h"
#include <typeinfo>

#define INTERMEDIATE_HOST 23
#define SERVER 69

class Client {
public:
    Client() :  send_receive_host() {}

private:
    DatagramSocket send_receive_host;

public:
    void send(std::vector<uint8_t> packet_data) {

        DatagramPacket sendPacket(packet_data, packet_data.size(), InetAddress::getLocalHost(), INTERMEDIATE_HOST);

        std::cout << "Client: Sending packet:" << std::endl;
        std::cout << "To host: " << sendPacket.getAddressAsString() << std::endl; 
        std::cout << "Destination host port: " << sendPacket.getPort() << std::endl;
        int len = sendPacket.getLength();
        std::cout << "Length: " << len << std::endl;
        std::cout << "Containing: " << std::string(static_cast<const char *>(
                    sendPacket.getData()), sendPacket.getLength()) << std::endl;

        try {
            send_receive_host.send(sendPacket);
        } catch (const std::runtime_error& e) {
            std::cerr << e.what();
            exit(1);
        }

        std::cout << "Client: Packet sent." << std::endl;

    }


    void recievePacket_func() {

        std::vector<uint8_t> in(100);
        DatagramPacket receivePacket(in, in.size());
        std::cout << "Server: Waiting for Packet." << std::endl;

        try {
			// Block until a datagram is received via sendReceiveSocket.
			send_receive_host.receive(receivePacket);
		} catch(const std::runtime_error& e) {
			std::cerr << e.what();
			exit(1);
		}

		std::cout << "Client: Packet received:" << std::endl;
		std::cout << "From host: " << receivePacket.getAddressAsString() << std::endl;
		std::cout << "Host port: " << receivePacket.getPort() << std::endl;
		int len = receivePacket.getLength();
        std::cout << "Length: " << len << std::endl;
		std::cout << "Containing: ";

		// Form a String from the byte array.
        std::cout << std::string( static_cast<const char *>
            (receivePacket.getData()), receivePacket.getLength() ) << std::endl;
		return;
    }
	

    std::vector<uint8_t> create_packet_data() {
        
        std::string filename = "test.txt";
        std::string mode = "octet";
        /* std::vector<utint8_t> filename; */

        std::vector<uint8_t> packet_data;
        packet_data.push_back(0x0);
        packet_data.push_back(0x1);

        for (int i = 0; i < filename.length(); i++)
            packet_data.push_back(filename[i]);

        packet_data.push_back(0x0);

        for (int i = 0; i < mode.length(); i++)
            packet_data.push_back(mode[i]);

        packet_data.push_back(0x0);

        for (char i: packet_data)
            if (i <= 0x10) {
                std::cout << std::hex << static_cast<int>(i);
            }
            else {
            std::cout << i;
            }
        std::cout << std::endl;

        return packet_data;
    }
};

int main() {

    std::vector<uint8_t> packet_data = Client().create_packet_data();
    Client().send(packet_data);
    Client().recievePacket_func();
    return 0;

}
