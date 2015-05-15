// Server: ServerGame.h
//

#pragma once
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

	void receiveFromClients();

	static void threadedClient(int clientId);

	void sendActionPackets();

private:

	// IDs for the clients connecting for table in ServerNetwork 
	static unsigned int client_id;

	// The ServerNetwork object 
	static ServerNetwork* network;

	// data buffer
	char network_data[MAX_PACKET_SIZE];

	//threads
	std::vector<std::thread *> myThreads;
};