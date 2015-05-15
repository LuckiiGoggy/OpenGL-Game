#include "GLNetwork.h"



namespace GLNetwork{

	// Convert structure into packet
	void Packet::serialize(char * data) {
		memcpy(data, this, sizeof(Packet));
	}

	// Convert received packets into structure
	void Packet::deserialize(char * data) {
		memcpy(this, data, sizeof(Packet));
	}
}


