// Client: ClientGame.h
//

#pragma once

#include "GLNetwork.h"
#include "ClientNetwork.h"

#include <winsock2.h>
#include <Windows.h>

class ClientGame
{
public:
	ClientGame(void);
	~ClientGame(void);

	ClientNetwork* network;

	void sendActionPackets(int);

	char network_data[MAX_PACKET_SIZE];

	void update(int);
};

