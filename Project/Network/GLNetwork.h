// Client: Header.h
//

#pragma once

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>
#include <string>

#define MAX_PACKET_SIZE 1000000

// Hard-coded serverIP
#define SERVER_IP "142.232.237.137"

// Packet structure, contains necessary values
namespace GLNetwork{


	// Enumeration of packet types
	enum PacketType {

		INIT_CONNECTION = 10,

		ACTION_EVENT = 1,

		PLAYER_PACKET = 2,

		PLAYER_INFO_PACKET = 3,

		OBJECT_INFO = 4,
		
		KILL_OBJECT = 5,

		WALL_OBJECT = 6,

		FLOOR_OBJECT = 7,

		PLAYER_OBJECT = 8,

		PROJECTILE_OBJECT = 9

	};

	struct Packet {
		// Packet types
		//char packet_type;
// 		size_t packet_size;
// 
// 		virtual const unsigned int size(void){ return packet_size; };
// 
// 		// Convert structure into packet
// 		virtual void serialize(char * data) {
// 			data[0] = packet_type;
// 			memcpy(data + 1, &packet_size, sizeof(size_t));
// 		}
// 
// 		// Convert received packets into structure
// 		virtual void deserialize(char * data) {
// 			packet_type = data[0];
// 			memcpy(&packet_size, data + 1, sizeof(size_t));
// 		}

		virtual size_t size(void){ return sizeof(Packet); };
		virtual PacketType PacketType(void){ return ACTION_EVENT; };
	};

	struct PlayerPacket : Packet{
		/*Player Input*/
		bool forward = false;
		bool backward = false;
		bool left = false;
		bool right = false;

		/*Net Rotation*/
		float netRot00 = 1.0f;
		float netRot01 = 0.0f;
		float netRot02 = 0.0f;
		float netRot10 = 0.0f;
		float netRot11 = 1.0f;
		float netRot12 = 0.0f;
		float netRot20 = 0.0f;
		float netRot21 = 0.0f;
		float netRot22 = 1.0f;

		/*Player is shooting*/
		bool isShooting = false;

		virtual size_t size(void){ return sizeof(PlayerPacket); };
		virtual GLNetwork::PacketType PacketType(void){ return PLAYER_PACKET; };
	};

	struct PlayerInfoPacket : Packet{
		int objectId;

		int health;
		int score;
		int ammo;

		virtual size_t size(void){ return sizeof(PlayerInfoPacket); }
		virtual GLNetwork::PacketType PacketType(void){ return PLAYER_INFO_PACKET; };
	};

	struct ObjectPacket : Packet{
		/*Object Id*/
		int objectId;

		/*Net Rotation*/
		float netRot00 = 1.0f;
		float netRot01 = 0.0f;
		float netRot02 = 0.0f;
		float netRot10 = 0.0f;
		float netRot11 = 1.0f;
		float netRot12 = 0.0f;
		float netRot20 = 0.0f;
		float netRot21 = 0.0f;
		float netRot22 = 1.0f;

		/*Object Position*/
		float posX = 0.0f;
		float posY = 0.0f;
		float posZ = 0.0f;

		virtual size_t size(void){ return sizeof(ObjectPacket); };
		virtual GLNetwork::PacketType PacketType(void){ return OBJECT_INFO; };
	};

	struct KillObjectPacket : Packet{
		int objectId;

		virtual size_t size(void){ return sizeof(KillObjectPacket); };
		virtual GLNetwork::PacketType PacketType(void){ return KILL_OBJECT; };
	};




	class PacketBuilder{
	public:
		/*Serializes the data of a packet, and returns the byte length*/
		static unsigned int SerializePacket(PacketType packet_t, Packet *packet, char *&data){
			data = new char[packet->size() + 1];

			data[0] = packet_t;
			memcpy(data + 1, packet, packet->size());

			return packet->size() + 1;
		}

	protected:

	};

	class PacketReader{
	public:
		static int DeSerializePacket(Packet *&packet, char data[], int offset){
			int packetSize = 0;
			char packet_t = data[offset + 0];
			packet = new Packet();
			switch (packet_t)
			{
			case PLAYER_PACKET:
				packet = new PlayerPacket();
				break;
			case PLAYER_INFO_PACKET:
				packet = new PlayerInfoPacket();
				break;
			case OBJECT_INFO:
				packet = new ObjectPacket();
				break;
			case KILL_OBJECT:
				packet = new KillObjectPacket();
				break;
			case WALL_OBJECT:
				packet = new ObjectPacket();
				break;
			case FLOOR_OBJECT:
				packet = new ObjectPacket();
				break;
			case PLAYER_OBJECT:
				packet = new ObjectPacket();
				break;
			case PROJECTILE_OBJECT:
				packet = new ObjectPacket();
				break;
			case INIT_CONNECTION:
			case ACTION_EVENT:
			default:
				break;
			}
			packetSize = packet->size() + 1;
			memcpy(packet, data + offset + 1, packet->size());

			return packetSize;
		}
	protected:
	};
}

