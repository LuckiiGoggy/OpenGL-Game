// Client: Header.h
//

#pragma once

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>
#include <string>

#define MAX_PACKET_SIZE 1000000


// Packet structure, contains necessary values
namespace GLNetwork{


	// Enumeration of packet types
	enum PacketTypes {

		INIT_CONNECTION = 0,

		ACTION_EVENT = 1,

		PLAYER_OBJECT = 2,

		LEVEL_OBJECT = 3,

		PROJECTILE_OBJECT = 4

	};

	struct Packet {

		// Packet types
		unsigned int packet_type;

		// Values to send
		float testValue;

		// Convert structure into packet
		void serialize(char * data);

		// Convert received packets into structure
		void deserialize(char * data);
	};

}

