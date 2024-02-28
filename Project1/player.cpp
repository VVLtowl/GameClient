#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "model.h"
#include "audio.h"

#include "scene.h"
#include "camera.h"
#include "player.h"
#include "bullet.h"

void Player::Init()
{		
	Scene* scene = Manager::GetScene();
	shootSE=scene->AddGameObject<Audio>(layerType_3DAudio);
	shootSE->Load("asset\\audio\\wan.wav");
}

void Player::Uninit()
{
}

void Player::Update()
{
	//network input move
	{
		if (Input::GetKeyTrigger('A'))
		{
			Manager::SendToServer("left");
		}
		if (Input::GetKeyTrigger('D'))
		{
			Manager::SendToServer("right");
		}
		if (Input::GetKeyPress('W'))
		{
		}
		if (Input::GetKeyPress('S'))
		{
		}
	}
	
	
	//camera follow player
	if(false)
	{
		Scene* scene = Manager::GetScene();
		Camera* camera = scene->GetGameObject<Camera>(layerType_camera);

		//third person view
		{
			//set camera 
			D3DXVECTOR3 target = m_Position + Right() * 0;
			float posY = -3.0f * (float)Input::GetMouseScreenPos().y / SCREEN_HEIGHT * 2.0f;
			D3DXVECTOR3 pos = m_Position - Forward() * 4.0f + Right() * 0 + D3DXVECTOR3(0, posY , 0);

			camera->SetTargetAndPosition(target, pos);
		}
	}
}

void Player::Draw()
{
}
