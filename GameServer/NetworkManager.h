#pragma once

// WinSock2 Windows Sockets
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <Message.h>
#include <Buffer.h>

#include "player_state.pb.h"

// Need to link Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#include <chrono>
#include <vector>

namespace net
{
	struct PlayerPosition
	{
		unsigned int id;
		float x;
		float z;
	};

	struct ClientInfo : public PlayerPosition
	{
		sockaddr_in addr;
		int addrLen;
	};

	class NetworkManager
	{
	public:
		NetworkManager();
		~NetworkManager();

		void Initialize();
		void Destroy();

		void Update();

	private:
		void HandleRECV();
		void BroadcastUpdatesToClients();

		bool m_Initialized = false;
		bool m_Connected = false;
		float m_Wait = 0;

		SOCKET m_ListenSocket;

		// 
		// Time
		std::chrono::high_resolution_clock::time_point m_NextBroadcastTime;

		//
		// ConnectedClients
		std::vector<ClientInfo> m_ConnectedClients;

		game::GameScene gameScene;

		bool newConnectionAdded = false;


        //std::string serializeGameScene(const GameScene& gameScene) {
        //    std::ostringstream oss;

        //    // Serialize the id
        //    oss << gameScene.id << " ";

        //    // Serialize each player
        //    for (const auto& player : gameScene.players) {
        //        oss << player.id << " " << player.isAlive << " " << player.isShot << " "
        //            << player.position.x << " " << player.position.z << " " << player.state << " ";
        //    }

        //    // Serialize each bullet
        //    for (const auto& bullet : gameScene.bullets) {
        //        oss << static_cast<int>(bullet.state) << " " << bullet.position.x << " "
        //            << bullet.position.z << " " << bullet.velocity.x << " " << bullet.velocity.z << " ";
        //    }

        //    return oss.str();
        //}

        //GameScene deserializeGameScene(const std::string& serializedString) {
        //    GameScene gameScene;

        //    std::istringstream iss(serializedString);

        //    // Deserialize the id
        //    iss >> gameScene.id;

        //    // Deserialize each player
        //    while (!iss.eof()) {
        //        Player player;
        //        iss >> player.id >> player.isAlive >> player.isShot
        //            >> player.position.x >> player.position.z >> player.state;
        //        gameScene.players.push_back(player);
        //    }

        //    // Reset the stream and ignore the trailing whitespace
        //    iss.clear();
        //    iss.ignore();

        //    // Deserialize each bullet
        //    while (!iss.eof()) {
        //        Bullet bullet;
        //        int bulletState;
        //        iss >> bulletState >> bullet.position.x >> bullet.position.z
        //            >> bullet.velocity.x >> bullet.velocity.z;
        //        bullet.state = static_cast<BulletState>(bulletState);
        //        gameScene.bullets.push_back(bullet);
        //    }

        //    return gameScene;
        //}


	};

	const float RETRY_TIME_MS = 10000;
}