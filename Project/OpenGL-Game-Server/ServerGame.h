#ifndef SERVERGAME_H
#define SERVERGAME_H
// Server: ServerGame.h
//

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

#endif