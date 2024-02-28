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

Client Manager::m_Client;
Scene* Manager::m_Scene;//static need call
GameObject* Manager::m_Player[2] = { nullptr };

void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();
	/*m_Scene = new Title();
	m_Scene->Init();*/

	//SetScene<Title>();
	SetScene<Game>();
}


void Manager::Uninit()
{

	m_Scene->Uninit();
	delete m_Scene;

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
			if (strcmp(msgBuf, "end")==0)
				//end game
			{

			}
			else if (strcmp(msgBuf, "test addr msg!") == 0)
				//test msg
			{

			}
			else
			{
				int playerID = static_cast<int>(msgBuf[0])-'0';
				char posXMsg[LEN_MSG];
				sprintf(posXMsg, "%s", &msgBuf[1]);
				float posX = std::stof(posXMsg);
				D3DXVECTOR3 pos = m_Player[playerID]->Position();
				pos.x = posX;
				pos.z = -pow(-1, playerID);
				m_Player[playerID]->SetPosition(pos);
			}
		}
	}
}

void Manager::Draw()
{

	Renderer::Begin();

	m_Scene->Draw();

	Renderer::End();
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
	auto msg = new MsgContent();
	msg->BHID = (int)BHID::PLAYER_MOVE;
	msg->DataLen = LEN_MSG_DATA_DEFAULT;
	//msg->Data = (void*);
	//auto msgBuf = EncodeMsgContent();
}


Scene* Manager::GetScene()
{
	return m_Scene;
}

template <typename T>
void Manager::AddGameObject()
{
	T* object= m_Scene->AddGameObject<T>();
}
