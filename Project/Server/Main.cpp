// Server: Main.cpp
//

#include "GLNetwork.h"
#include "ServerGame.h"

// used for multi-threading
#include <process.h>
#include <thread>
#include <iostream>

void serverLoop(void *);

ServerGame * server;

int main()
{

	// initialize the server
	server = new ServerGame();

	while (true)
	{
		server->update();
	}

}