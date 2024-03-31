#pragma once
#include "NetworkCommon.h"
#include "scene.h"
#include "Updater.h"
#include <vector>

enum class BHID
{
	PLAYER_MOVE,
};

class Manager
{
private:
	static class Scene* m_Scene;

public:
	static short m_ThisClientID;
	static class Client m_Client;
	static std::vector<GameObject*> m_Players;

	static Updater update_recvServer;
	static Updater update_input;
	static Updater update_scene;
	static void StartUpdateRecvServerThread();



public:
	static void Init();
	static void Uninit();
	static void Update();

	//send char
	static void SendToServer(char* msgBuf);
	static void SendToServer(std::string msg);
	static bool RecvFromServer(char* msgBuf);
	static void TryCloseClient();

	//other
	static GameObject* GetThisPlayerObj();
	
	//send command
	//client send command(id) of input to server / client send command(id) and data(class) to server
	//server execute command(id) and update data(class)
	//server send command(id) and data(class) to client
	//client execute command(id) and update data(class)
	static void SendPlayerMoveRight();
	static void SendPlayerMoveLeft();
	static void SendPlayerMoveUp();
	static void SendPlayerMoveDown();
	static void SendPlayerMove(float x,float z);
	static void SendPlayerHit(float rot);
	static void SendClientEnd();

	//gameobject management
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

private:
	static void InitNetworkCommand();

	//other func
private:
	static void AddPlayer(D3DXVECTOR3 pos);
	static void RemovePlayer(int id);
};

