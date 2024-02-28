#pragma once
#include "NetworkCommon.h"
#include "scene.h"

enum class BHID
{
	PLAYER_MOVE,
};

class Manager
{
private:
	static class Scene* m_Scene;

public:
	static short m_PlayerID;
	static class Client m_Client;
	static class GameObject* m_Player[2];

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	//send char
	static void SendToServer(char* msgBuf);
	static void SendToServer(std::string msg);
	static bool RecvFromServer(char* msgBuf);
	
	//send command
	//client send command of input to server
	//server execute command and update data
	//server send command and data to client
	//client update data
	static void SendPlayerMoveRight();
	static void SendPlayerMoveLeft();
	static void PlayerMove();


	template <typename T>
	static void AddGameObject();
	static Scene* GetScene();

	template<typename T>
	static void SetScene()
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		m_Scene = new T();
		m_Scene->Init();
	}
};

