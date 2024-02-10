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

Client Manager::m_Client;
Scene* Manager::m_Scene;//static need call

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
}

void Manager::Draw()
{

	Renderer::Begin();

	m_Scene->Draw();

	Renderer::End();
}

void Manager::SendToServer(char* msgBuf)
{
	//show client ip
	char ipBuffer[LEN_MSG]; // 定义用于存储 IP 地址字符串的缓冲区
	inet_ntop(AF_INET, &(m_Client.m_ServerAddr.sin_addr), ipBuffer, INET_ADDRSTRLEN); // 将二进制 IP 地址转换为字符串形式
	std::cout << "send to server[" << ipBuffer << "]: " << msgBuf << std::endl;
	m_Client.SendTo(&(m_Client.m_UDPSocket), msgBuf, &(m_Client.m_ServerAddr));
}

void Manager::RecvFromServer(char* msgBuf)
{

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
