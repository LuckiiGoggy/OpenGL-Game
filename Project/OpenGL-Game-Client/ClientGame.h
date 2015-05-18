// Client: ClientGame.h
//

#pragma once

#include "GLNetwork.h"
#include "ClientNetwork.h"

#include <winsock2.h>
#include <Windows.h>
#include "GameScene.h"
#include <thread>

class ClientGame
{
public:
	
	
	
	static void Init(void);

	static ClientNetwork* network;

	static void sendActionPackets(int);
	

	static char network_data[MAX_PACKET_SIZE];

	static void update(int);
	static void SendPacket(GLNetwork::PacketType packet_t, GLNetwork::Packet *packet);


	static void Game(GameScene *newGame);
	static GameScene *Game(void);
	static void Update(float timedelta);

protected:
	static GameScene *game;
	static std::thread *myThread;
};

