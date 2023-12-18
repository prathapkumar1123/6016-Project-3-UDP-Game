#include "NetworkManager.h"
#include <Buffer.h>
#include <Message.h>

#include <memory>


#define SERVER_PORT 8412
#define SERVER_IP "127.0.0.1"

namespace net
{
	// Move this to a structure for each client
	sockaddr_in addr;
	int addrLen;

	NetworkManager::NetworkManager()
	{
	}

	NetworkManager::~NetworkManager()
	{

	}

	void NetworkManager::Initialize()
	{
		// Initialize WinSock
		WSADATA wsaData;
		int result;

		// Set version 2.2 with MAKEWORD(2,2)
		result = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (result != 0) {
			printf("WSAStartup failed with error %d\n", result);
			return;
		}
		printf("WSAStartup successfully!\n");


		// Socket
		m_ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (m_ServerSocket == INVALID_SOCKET) {
			printf("socket failed with error %d\n", WSAGetLastError());
			WSACleanup();
			return;
		}
		printf("socket created successfully!\n");

		unsigned long nonblock = 1;
		result = ioctlsocket(m_ServerSocket, FIONBIO, &nonblock);
		if (result == SOCKET_ERROR) {
			printf("set nonblocking failed with error %d\n", result);
			return;
		}
		printf("set nonblocking successfully!\n");

		m_ServerAddr.sin_family = AF_INET;
		m_ServerAddr.sin_port = htons(SERVER_PORT);
		m_ServerAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
		m_ServerAddrLen = sizeof(m_ServerAddr);

		printf("NetworkManager running...\n");
		printf("Socket ID: %d...\n", m_ServerSocket);

		m_NextSendTime = std::chrono::high_resolution_clock::now();

		m_NetworkedPositions.resize(NUM_PLAYERS);

		m_Initialized = true;
	}

	void NetworkManager::Destroy()
	{
		if (!m_Initialized)
		{
			return;
		}

		closesocket(m_ServerSocket);
		WSACleanup();

		m_Initialized = false;
	}

	void NetworkManager::Update()
	{
		if (!m_Initialized)
		{
			return;
		}

		// Send information/data back to clients
		SendDataToServer();

		// Handle all recv data
		HandleRECV();

		// Process everything
	}

	void NetworkManager::SendPlayerPositionToServer(float x, float z)
	{
		m_PlayerPosition.x = x;
		m_PlayerPosition.z = z;
	}

	void NetworkManager::HandleRECV()
	{

		const int bufSize = 1024;
		Buffer* buffer = new Buffer(bufSize);

		int result = recvfrom(m_ServerSocket, reinterpret_cast<char*>(buffer->m_BufferData.data()), 
			bufSize, 0, (SOCKADDR*)&m_ServerAddr, &m_ServerAddrLen);

		if (result == SOCKET_ERROR) {
			if (WSAGetLastError() == WSAEWOULDBLOCK) {
				return;
			}
			printf("recvfrom failed with error %d\n", WSAGetLastError());
			Destroy();
			return;
		}

		if (result > 0) {
			uint32_t packetSize = buffer->ReadUInt32LE();
			uint32_t messageType = buffer->ReadUInt32LE();
			uint32_t messageLength = buffer->ReadUInt32LE();
			std::string msg = buffer->ReadString(messageLength);
			
			game::GameScene newScene;
			newScene.Clear();
			newScene.ParseFromString(msg);

			scene.Clear();
			scene = newScene;

			std::cout << "Game Scene - " << scene.id() << ", Players Size - " << scene.players().size() << std::endl;
		}

		delete buffer;
	}

	void NetworkManager::SendDataToServer()
	{
		std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		if (m_NextSendTime > currentTime)
		{
			return;
		}

		m_NextSendTime = currentTime + std::chrono::milliseconds(200);

		// Add 20 ms to the next broadcast time from now()
		//m_NextBroadcastTime 



		// MessageQueue, loop through and send all messages
		// You may multiple servers, you are sending data to
		int result = sendto(m_ServerSocket, (const char*)&m_PlayerPosition,
			sizeof(m_PlayerPosition), 0, (SOCKADDR*)&m_ServerAddr, m_ServerAddrLen);
		if (result == SOCKET_ERROR) {
			// TODO: We want to handle this differently.
			printf("send failed with error %d\n", WSAGetLastError());
			Destroy();
			return;
		}
	}
}