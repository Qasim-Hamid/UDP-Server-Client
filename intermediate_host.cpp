#include <chrono>
#include <thread>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include "Datagram1.h"

#define INTERMEDIATE_HOST 23
#define SERVER 69

class IntermeidateHost {
private:
    DatagramSocket ServerSocket;
    DatagramSocket ClientSocket;

public:
    IntermeidateHost() : ClientSocket(INTERMEDIATE_HOST), ServerSocket() {}
     
    void receiveClient() {

        std::vector<uint8_t> clientData(100);
        DatagramPacket clientPacket(clientData, clientData.size());
        std::cout << "Server: Waiting for Packet." << std::endl;

        try {
			std::cout << "Waiting..." << std::endl; // so we know we're waiting
			ClientSocket.receive(clientPacket);
		} catch (const std::runtime_error& e ) {
			std::cout << "IO Exception: likely:"
				  << "Receive Socket Timed Out." << std::endl << e.what() << std::endl;
			exit(1);
		}

		std::cout << "Server: Packet received:" << std::endl;                         
		std::cout << "From host: " << clientPacket.getAddressAsString() << std::endl;
		std::cout << "Host port: " << clientPacket.getPort() << std::endl;
		int len = clientPacket.getLength();
		std::cout << "Length: " << len << std::endl << "Containing: ";
		std::string received = std::string(static_cast<const char *>(clientPacket.getData()), clientPacket.getLength());
        std::cout << received << std::endl;

        DatagramPacket sendPacket(clientData, clientPacket.getLength(),
                clientPacket.getAddress(), clientPacket.getPort());

        std::cout <<  "Server: Sending packet:" << std::endl;
        std::cout << "To host: " << sendPacket.getAddressAsString() << std::endl;
        std::cout << "Destination host port: " << sendPacket.getPort() << std::endl;
        len = sendPacket.getLength();
        std::cout << "Length: " << len << std::endl
                  << "Containing: " << std::endl;
        std::cout << std::string(static_cast<const char *>(sendPacket.getData()), len) << std::endl; //

        try {
                ClientSocket.send(sendPacket);
        } catch ( const std::runtime_error& e ) {
            std::cerr << e.what() << std::endl;
            exit(1);
        }

        std::cout << "Server: packet sent" << std::endl;

        std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
        return;
    }
};

int main() {

    IntermeidateHost().receiveClient(); 

}
