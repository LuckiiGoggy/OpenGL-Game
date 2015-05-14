// Server: Main.cpp
//

#include "Net.h"
#include "ServerGame.h"

// used for multi-threading
#include <process.h>

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

	/*
	// create thread with arbitrary argument for the run function
	_beginthread(serverLoop, 0, (void*)12);
	*/
}

void serverLoop(void * arg)
{
	while (true)
	{
		server->update();
	}
}
