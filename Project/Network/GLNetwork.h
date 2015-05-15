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
	enum PacketType {

		INIT_CONNECTION = 0,

		ACTION_EVENT = 1,

		PLAYER_PACKET = 2,

		PLAYER_INFO_PACKET = 3,

		OBJECT_INFO = 4,
		
		KILL_OBJECT = 5,

		WALL_OBJECT = 6,

		PLAYER_OBJECT = 7,

		PROJECTILE_OBJECT = 8

	};

	struct Packet {
		Packet();
		Packet(PacketType packetType, size_t packetSize);

		// Packet types
		unsigned int packet_type;
		size_t packet_size;

		// Convert structure into packet
		virtual void serialize(char * data) {
			memcpy(data, this, sizeof(packet_size));
		}

		// Convert received packets into structure
		virtual void deserialize(char * data) {
			memcpy(this, data, sizeof(packet_size));
		}
	};

	struct PlayerPacket : Packet {
		PlayerPacket() : Packet(PLAYER_PACKET, sizeof(PlayerPacket)){};

		/*Player Input*/
		bool forward;
		bool backward;
		bool left;
		bool right;

		/*Net Rotation*/
		float netRot00;
		float netRot01;
		float netRot02;
		float netRot10;
		float netRot11;
		float netRot12;
		float netRot20;
		float netRot21;
		float netRot22;

		/*Player is shooting*/
		bool isShooting;
		
	};

	struct PlayerInfo : Packet {
		PlayerInfo() : Packet(PLAYER_INFO_PACKET,sizeof(PlayerInfo)){};

		int health;
		int score;
		int ammo;
	};

	struct ObjectPacket : Packet{
		ObjectPacket() : Packet(OBJECT_INFO,sizeof(ObjectPacket)){};
		ObjectPacket(PacketType type, size_t size) : Packet(type, size){};

		/*Object Id*/
		int objectId;

		/*Net Rotation*/
		float netRot00;
		float netRot01;
		float netRot02;
		float netRot10;
		float netRot11;
		float netRot12;
		float netRot20;
		float netRot21;
		float netRot22;

		/*Object Position*/
		float posX;
		float posY;
		float posZ;
	};

	struct WallObjectPacket : ObjectPacket{
		WallObjectPacket() : ObjectPacket(WALL_OBJECT, sizeof(WallObjectPacket)){};
	};

	struct PlayerObjectPacket : ObjectPacket{
		PlayerObjectPacket() : ObjectPacket(PLAYER_OBJECT, sizeof(PlayerObjectPacket)){};
	};

	struct ProjectileObjectPacket : ObjectPacket{
		ProjectileObjectPacket() : ObjectPacket(PROJECTILE_OBJECT, sizeof(ProjectileObjectPacket)){};
	};

	struct KillObject : Packet{
		KillObject() : Packet(KILL_OBJECT, sizeof(KillObject)){};

		int objectId;
	};


}

