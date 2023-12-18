#pragma once

#include <string>

struct PacketHeader
{
	uint32_t packetSize;
	uint32_t messageType;
};

struct Message
{
	PacketHeader header;
	uint32_t messageLength;
	std::string message;
};

enum MESSAGE_TYPE {
	JOIN = 1, DATA = 2, LEAVE = 3
};