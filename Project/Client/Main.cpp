// Client: Main.cpp
//

#include "Net.h"
#include "ClientGame.h"
// used for multi-threading
#include <process.h>

#include <stdlib.h>
#include <time.h>

ClientGame * client;

int main()
{
	//RNG
	int i;
	srand(time(NULL));

	// initialize the client 
	client = new ClientGame();

	while (true)
	{
		i = rand() % 10 + 1;

		//do game stuff
		client->update(i);
	}
}