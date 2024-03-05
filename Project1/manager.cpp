#include "main.h"

#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "timeManager.h"

//#include "polygon2D.h"
//#include "camera.h"
//#include "field.h"
//#include "player.h"
#include "scene.h"
#include "game.h"
#include "title.h"
#include "audio.h"
#include <string>

#include "SerializedTool.h"
#include "NetworkGameData.h"
#include "enemy.h"

short Manager::m_ThisClientID;
Client Manager::m_Client;
Scene* Manager::m_Scene;//static need call
std::vector<GameObject*> Manager::m_Players;

void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();

	//network init
	NetworkManager::InitClient();
	InitNetworkCommand();

	/*m_Scene = new Title();
	m_Scene->Init();*/



	//SetScene<Title>();
	SetScene<Game>();
}

template <typename T>
void Manager::AddGameObject()
{
	T* object = m_Scene->AddGameObject<T>();
}

void Manager::Uninit()
{

	m_Scene->Uninit();
	delete m_Scene;

	Manager::TryCloseClient();

	Audio::UninitMaster();
	Renderer::Uninit();
	Input::Uninit();
}

void Manager::Update()
{
	Input::Update();
	m_Scene->Update();

	//update network, update by server data
	{
		char msgBuf[LEN_MSG];
		if (Manager::RecvFromServer(msgBuf))
		{
			MsgContent msg;
			DecodeMsgContent(msgBuf, msg);
			int bhid = msg.BHID;

			if (bhid >= 0)
			{
				NetworkManager::Commands[bhid](msg);
			}

			/*int playerID = static_cast<int>(msgBuf[0])-'0';
			char posXMsg[LEN_MSG];
			sprintf(posXMsg, "%s", &msgBuf[1]);
			float posX = std::stof(posXMsg);
			D3DXVECTOR3 pos = m_Player[playerID]->Position();
			pos.x = posX;
			pos.z = -pow(-1, playerID);
			m_Player[playerID]->SetPosition(pos);*/
		}
	}
}

void Manager::Draw()
{

	Renderer::Begin();

	m_Scene->Draw();

	Renderer::End();
}

void Manager::TryCloseClient()
{
	SendClientEnd();

	//wait server answer
	while (m_Client.IsActive())
	{
	}
}

void Manager::SendToServer(char* msgBuf)
{
	m_Client.SendTo(&(m_Client.m_UDPSocket), msgBuf, &(m_Client.m_ServerAddr));
}

void Manager::SendToServer(std::string msg)
{
	m_Client.SendTo(&(m_Client.m_UDPSocket), &(*(msg.begin())), &(m_Client.m_ServerAddr));
}

bool Manager::RecvFromServer(char* msgBuf)
{
	SOCKADDR_IN tempAddr;
	return m_Client.RecvFrom(&(m_Client.m_UDPSocket), msgBuf, &(tempAddr))>0;
}

void Manager::SendPlayerMoveRight()
{
	Data_C2S_PlayerMove data;
	data.id = m_ThisClientID;
	data.leftRight = 1;
	data.upDown = 0;

	MsgContent msg;
	msg.BHID = (int)BHID_C2S::Player_InputMove;
	msg.DataLen = sizeof(Data_C2S_PlayerMove);
	msg.Data = (void*)(&data);

	auto msgBuf = EncodeMsgContent(msg, nullptr);
	SendToServer(msgBuf);
}

void Manager::SendPlayerMoveLeft()
{
	Data_C2S_PlayerMove data;
	data.id = m_ThisClientID;
	data.leftRight = -1;
	data.upDown = 0;

	MsgContent msg;
	msg.BHID = (int)BHID_C2S::Player_InputMove;
	msg.DataLen = sizeof(Data_C2S_PlayerMove);
	msg.Data = (void*)(&data);

	auto msgBuf = EncodeMsgContent(msg, nullptr);
	SendToServer(msgBuf);
}



void Manager::SendClientEnd()
{
	Data_UserID data;
	data.id = m_ThisClientID;

	MsgContent msg;
	msg.BHID = (int)BHID_C2S::User_Quit;
	msg.DataLen = sizeof(data);
	msg.Data = (void*)(&data);

	auto msgBuf = EncodeMsgContent(msg, nullptr);
	SendToServer(msgBuf);
}



Scene* Manager::GetScene()
{
	return m_Scene;
}

void Manager::InitNetworkCommand()
{
	NetworkManager::SetCommand(
		BHID_S2C::SetID,
		[&](const MsgContent& msg)
		{
			auto data = (Data_UserID*)(msg.Data);
			m_ThisClientID = data->id;

			// 修改窗口名字
			char name[50];
			sprintf(name, "player %d", m_ThisClientID);
			SetWindowText(GetWindow(), name);
		});
	NetworkManager::SetCommand(
		BHID_S2C::AddExistPlayers,
		[&](const MsgContent& msg)
		{
			auto data = (Data_S2C_ObjectPos2*)msg.Data;
			int existPlayerNum = data->max - 1;//minus shuttle

			//update shuttle pos

			//add player and set pos
			for (int i = 0; i < existPlayerNum; i++)
			{
				if (i + 1 >= data->max)continue;

				auto objPos = data->pos[i + 1];

				D3DXVECTOR3 pos;
				pos.x = objPos.x;
				pos.y = objPos.y;
				pos.z = objPos.z;
				AddPlayer(pos);
			}
		});
	NetworkManager::SetCommand(
		BHID_S2C::AddPlayer,
		[&](const MsgContent& msg)
		{
			auto data = (Data_Pos*)(msg.Data);
			D3DXVECTOR3 pos = D3DXVECTOR3(data->x,data->y,data->z);
			AddPlayer(pos);
		});
	NetworkManager::SetCommand(
		BHID_S2C::RemovePlayer,
		[&](const MsgContent& msg)
		{
			auto data = (Data_UserID*)(msg.Data);
			int removeClientID = data->id;
			RemovePlayer(removeClientID);
		});
	NetworkManager::SetCommand(
		BHID_S2C::SyncObjectPosition,
		[&](const MsgContent& msg)
		{
			auto data = (Data_S2C_ObjectPos2*)msg.Data;

			//update shuttle pos

			//update player pos
			for (int i = 0; i < m_Players.size(); i++)
			{
				if (i + 1 >= data->max)continue;

				auto objPos=data->pos[i+1];

				D3DXVECTOR3 pos;
				pos.x = objPos.x;
				pos.y = objPos.y;
				pos.z = objPos.z;
				m_Players[i]->SetPosition(pos);
			}


			//auto data = (Data_S2C_ObjectPos*)msg.Data;

			//D3DXVECTOR3 pos;

			//pos.x = data->player1X;
			//pos.y = data->player1Y;
			//pos.z = data->player1Z;
			//m_Player[0]->SetPosition(pos);


			//pos.x = data->player2X;
			//pos.y = data->player2Y;
			//pos.z = data->player2Z;
			//m_Player[1]->SetPosition(pos);


		});
	NetworkManager::SetCommand(
		BHID_S2C::ApproveQuit,
		[&](const MsgContent& msg)
		{
			m_Client.ShutDown();
		});
}



void Manager::AddPlayer(D3DXVECTOR3 pos)
{
	//test add player on different poasition
	((Game*)GetScene())->AddPlayer(pos);
}

void Manager::RemovePlayer(int id)
{
	GameObject* deletePlayer= m_Players[id];
	m_Players.erase(m_Players.begin() + id);
	((Game*)GetScene())->DeleteGameObject(deletePlayer);
}