// Client: ClientNetwork.h
//

#pragma once

#include "GLNetwork.h"
#include "NetworkServices.h"

#include <winsock2.h>
#include <Windows.h>
#include <stdio.h> 

// size of our buffer
#define DEFAULT_BUFLEN 512
// port to connect sockets through 
#define DEFAULT_PORT "6881"
// Hard-coded serverIP
#define IP_TO_CONNECT "142.232.237.137"

using namespace std;

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ClientNetwork
{

public:

	// for error checking function calls in Winsock library
	int iResult;

	// socket for client to connect to server
	SOCKET ConnectSocket;

	// ctor/dtor
	ClientNetwork(void);
	~ClientNetwork(void);

	int receivePackets(char *);
};

