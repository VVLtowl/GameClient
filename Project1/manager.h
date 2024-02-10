#pragma once
#include "Network/NetworkCommon.h"
#include "scene.h"

class Manager
{
private:
	static class Scene* m_Scene;

public:
	static short m_PlayerID;
	static class Client m_Client;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static void SendToServer(char* msgBuf);
	static void RecvFromServer(char* msgBuf);
	
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