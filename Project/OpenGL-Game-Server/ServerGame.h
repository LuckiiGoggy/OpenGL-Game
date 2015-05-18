#ifndef SERVERGAME_H
#define SERVERGAME_H
// Server: ServerGame.h
//

#include "GLNetwork.h"
#include "ServerNetwork.h"
#include <thread>
#include <vector>

class ServerGame
{

public:

	ServerGame(void);
	~ServerGame(void);

	void update();

	static void threadedClient(int clientId);


	static void sendPackets(GLNetwork::Packet *packet);
	static void sendActionPackets();
	static void RemoveClient(unsigned int clientId);
	static void SendPacketToClient(GLNetwork::Packet *packet, unsigned int clientId);
	static void SendPacketToClient(GLNetwork::PacketType packet_t, GLNetwork::Packet *packet, unsigned int clientId);
	static void SendToAll(GLNetwork::PacketType packet_t, GLNetwork::Packet *packet);
	static void SendToOne(GLNetwork::PacketType packet_t, GLNetwork::Packet *packet, unsigned int clientId);


private:

	// IDs for the clients connecting for table in ServerNetwork 
	static unsigned int client_id;

	/*map of client_ids and Player ObjectID*/
	static std::map<unsigned int, int> clients;

	// The ServerNetwork object 
	static ServerNetwork* network;

	// data buffer
	static char network_data[MAX_PACKET_SIZE];

	//threads
	static std::vector<std::thread *> myThreads;
};

#endif