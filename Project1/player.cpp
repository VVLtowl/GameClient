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


#include "Joycon/WLJoyconInput.h"

void Player::Init()
{		
	Scene* scene = Manager::GetScene();
	shootSE=scene->AddGameObject<Audio>(layerType_3DAudio);
	shootSE->Load("asset\\audio\\wan.wav");

	WLJoyconInput::SetEventThrow(
		[&](float pow, float yaw, bool trigger)
		{
			//GameObject* obj = Manager::GetThisPlayerObj();
			//obj->SetRotation(
			//	D3DXVECTOR3(
			//		WLJoyconInput::m_Pitch, 
			//		yaw * 45,
			//		WLJoyconInput::m_Roll));

			//Scene* scene = Manager::GetScene();
			//Bullet* bullet = scene->AddGameObject<Bullet>(layerType_3DObject);
			//bullet->SetPosition(obj->Position() + obj->Forward() * 2);
			//D3DXVECTOR3 scl = { 0.3,0.3,0.3 };
			//bullet->SetScale(scl);
			//bullet->StartPhysics(obj->Forward() * 0.1f);

			if (trigger)
			{
				Scene* scene = Manager::GetScene();
			Bullet* bullet = scene->AddGameObject<Bullet>(layerType_3DObject);
			GameObject* obj = Manager::GetThisPlayerObj();
			bullet->SetPosition(obj->Position() + obj->Forward() * 2);
			D3DXVECTOR3 scl = { 0.3,0.3,0.3 };
			bullet->SetScale(scl);
			bullet->StartPhysics(obj->Forward() * 0.1f);
			}
		}
	);
}

void Player::Uninit()
{
}

void Player::Update()
{
	//update joycon
	//WLJoyconInput::Update();

	//network input move
	{
		short x = 0;
		short z = 0;
		if (Input::GetKeyPress('A') || WLJoyconInput::m_StickX == -1)
		{
			//Manager::SendToServer("left");
			//Manager::SendPlayerMoveLeft();
			x = -1;
		}
		if (Input::GetKeyPress('D') || WLJoyconInput::m_StickX == 1)
		{
			//Manager::SendToServer("right");
			//Manager::SendPlayerMoveRight();
			x = 1;
		}
		if (Input::GetKeyPress('W') || WLJoyconInput::m_StickY == 1)
		{
			//Manager::SendPlayerMoveUp();
			z = 1;
		}
		if (Input::GetKeyPress('S') || WLJoyconInput::m_StickY == -1)
		{
			//Manager::SendPlayerMoveDown();
			z = -1;
		}

		if (x != 0 || z != 0)
		{
			Manager::SendPlayerMove(x,z);
		}
	}
	
	//network input throw
	{
		bool hitBall = false;
		if (WLJoyconInput::IsCoolDownThrow)
		{
			//check is hit ball
			if (WLJoyconInput::IsThrow())
			{
				hitBall = true;
			}

			//cool down 
			WLJoyconInput::CoolDownThrow();
		}

		if (hitBall)
		{
			Manager::SendPlayerHit(WLJoyconInput::m_Yaw);
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
