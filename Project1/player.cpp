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
	m_Model = new Model();
	m_Model->Load("asset\\model\\torus.obj"); //"asset/texture/UI.jpg",

	m_Position = D3DXVECTOR3(0,0,0);
	m_Rotation = D3DXVECTOR3(0,0,0);
	m_Scale = D3DXVECTOR3(1, 1, 1);

	Renderer::CreateVertexShader(
		&m_VertexShader,
		&m_VertexLayout,
		"unlitTextureVS.cso"
	);

	Renderer::CreatePixelShader(
		&m_PixelShader,
		"unlitTexturePS.cso"
	);

	Scene* scene = Manager::GetScene();
	shootSE=scene->AddGameObject<Audio>(layerType_3DAudio);
	shootSE->Load("asset\\audio\\wan.wav");
}

void Player::Uninit()
{
	m_Model->Unload();
}

void Player::Update()
{
	//defualt
	{
		//if (Input::GetKeyPress('A'))
		//{
		//	m_Position.x += -1.0f / 60.0f;
		//}
		//if (Input::GetKeyPress('D'))
		//{
		//	m_Position.x += 1.0f / 60.0f;
		//}
		//if (Input::GetKeyPress('W'))
		//{
		//	m_Position.z += 1.0f / 60.0f;
		//}
		//if (Input::GetKeyPress('S'))
		//{
		//	m_Position.z += -1.0f / 60.0f;
		//}

		if (Input::GetKeyPress(VK_LEFT))
		{
			m_Rotation.y -= 1.0f / 60.0f;
		}
		if (Input::GetKeyPress(VK_RIGHT))
		{
			m_Rotation.y += 1.0f / 60.0f;
		}

		//m_Rotation.y = (float)Input::GetMousePos().x / SCREEN_WIDTH * 2*PI;
		m_Rotation.y += 1.0f / 60.0f * (float)Input::GetMouseMoveX();
		//m_Rotation.x += 1.0f / 60.0f * (float)Input::GetMouseMove().y;
	}
	
	
	//camera follow player
	{
		Scene* scene = Manager::GetScene();
		Camera* camera = scene->GetGameObject<Camera>(layerType_camera);

		//top view
		{
			//m_Target = playerPos;
			//m_Position = playerPos + D3DXVECTOR3(0, 3, -5);
		}
		//third person view
		{
			if (Input::GetKeyPress('A'))
			{
				m_Position += 3.0f * (-1.0f / 60.0f * Right());
			}
			if (Input::GetKeyPress('D'))
			{
				m_Position += 3.0f * (1.0f / 60.0f * Right());
			}
			if (Input::GetKeyPress('W'))
			{
				m_Position += 3.0f * (1.0f / 60.0f * Forward());
			}
			if (Input::GetKeyPress('S'))
			{
				m_Position += 3.0f * (-1.0f / 60.0f * Forward());
			}
			if (Input::GetKeyPress('Q'))
			{
				m_Position += 3.0f * (1.0f / 60.0f * Up());
			}
			if (Input::GetKeyPress('E'))
			{
				m_Position += 3.0f * (-1.0f / 60.0f * Up());
			}

			D3DXVECTOR3 target = m_Position + Right() *0;
			float posY = -3.0f * (float)Input::GetMouseScreenPos().y / SCREEN_HEIGHT*2.0f;
			D3DXVECTOR3 pos = m_Position - Forward() * 4.0f + Right() * 0 + D3DXVECTOR3(0, posY , 0);

			//camera->SetTargetAndPosition(target, pos);
		}
		//first person view
		{
			//m_Target = playerPos + playerForward + D3DXVECTOR3(0, 1, 0);
			//m_Position = playerPos + D3DXVECTOR3(0, 1, 0);
		}
	}

	if (Input::GetKeyPress(VK_SPACE)||
		Input::GetKeyTrigger(VK_LBUTTON))
	{
		//Manager::AddGameObject<Bullet>();
		//shootSE->Play();


		Scene* scene = Manager::GetScene();
		Bullet* bullet = scene->AddGameObject<Bullet>(layerType_3DObject);
		bullet->SetPosition(m_Position); 
		D3DXVECTOR3 scl = { 0.3,0.3,0.3 };
		bullet->SetScale(scl);
		bullet->StartPhysics(Forward()*0.1f);
	}
}

void Player::Draw()
{
	//culling
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(layerType_camera);
	if (!camera->CheckView(m_Position))
	{
		return;
	}

	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//Renderer::SetWorldViewProjection2D();
	//ワールドマトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();

	//マテリアル設定
	/*MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = { 1,1,1,1 };
	Renderer::SetMaterial(material);*/
}
