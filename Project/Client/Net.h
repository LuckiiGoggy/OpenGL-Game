// Client: Header.h
//

#pragma once

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>
#include <string>

#define MAX_PACKET_SIZE 1000000

// Enumeration of packet types
enum PacketTypes {

	INIT_CONNECTION = 0,

	ACTION_EVENT = 1,

};

// Packet structure, contains necessary values
struct Packet {

	// Packet types
	unsigned int packet_type;

	// Values to send
	float testValue;

	// Convert structure into packet
	void serialize(char * data) {
		memcpy(data, this, sizeof(Packet));
	}

	// Convert received packets into structure
	void deserialize(char * data) {
		memcpy(this, data, sizeof(Packet));
	}
};