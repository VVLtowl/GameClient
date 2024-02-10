#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "manager.h"
#include "player.h"

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 6.0f, -5.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Camera::Uninit()
{
}

void Camera::Update()
{
#pragma region ========== SAMPLE ==========

	if (false)
	{
		if (Input::GetKeyPress(VK_UP))
		{
			m_Position.y += -10.0f / 60.0f;
		}
		if (Input::GetKeyPress(VK_DOWN))
		{
			m_Position.y += 10.0f / 60.0f;
		}

		Scene* scene = Manager::GetScene();
		Player* player = scene->GetGameObject<Player>(1);
		D3DXVECTOR3 playerPos = player->Position();
		D3DXVECTOR3 playerForward = player->Forward();

		//top view
		{
			//m_Target = playerPos;
			//m_Position = playerPos + D3DXVECTOR3(0, 3, -5);
		}
		//third person view
		{
			//m_Target = playerPos;
			//m_Position = playerPos - playerForward * 4.0f + D3DXVECTOR3(0, 3, 0);
		}
		//first person view
		{
			//m_Target = playerPos + playerForward + D3DXVECTOR3(0, 1, 0);
			//m_Position = playerPos + D3DXVECTOR3(0, 1, 0);
		}
	}
	
#pragma endregion


}

void Camera::Draw()
{
	D3DXVECTOR3 up = D3DXVECTOR3(0, 1, 0);
	D3DXMatrixLookAtLH(
		&m_ViewMatrix,
		&m_Position,
		&m_Target,
		&up
	);
	Renderer::SetViewMatrix(&m_ViewMatrix);

	D3DXMatrixPerspectiveFovLH(
		&m_ProjectionMatrix,
		1.0f,
		(float)SCREEN_WIDTH/SCREEN_HEIGHT,
		1.0f,
		1000.0f
	);
	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);
}

bool Camera::CheckView(D3DXVECTOR3 pos)
{
	D3DXMATRIX vp, invvp;
	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = { -1,1,1 };
	vpos[1] = { 1,1,1 };
	vpos[2] = { -1,-1,1 };
	vpos[3] = { 1,-1,1 };

	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	/*
	left right
	0    1
	
	2    3
	*/
	
	//left face
	{
		D3DXVECTOR3 v, v1, v2, n;

		v = pos - m_Position;
		v1 = wpos[0] - m_Position;
		v2 = wpos[2] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < 0.0f)
		{
			return false;
		}
	}

	//right face
	{
		D3DXVECTOR3 v, v1, v2, n;

		v = pos - m_Position;
		v1 = wpos[3] - m_Position;
		v2 = wpos[1] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < 0.0f)
		{
			return false;
		}
	}

	//up face
	{
		D3DXVECTOR3 v, v1, v2, n;

		v = pos - m_Position;
		v1 = wpos[1] - m_Position;
		v2 = wpos[0] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < 0.0f)
		{
			return false;
		}
	}

	//down face
	{
		D3DXVECTOR3 v, v1, v2, n;

		v = pos - m_Position;
		v1 = wpos[2] - m_Position;
		v2 = wpos[3] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < 0.0f)
		{
			return false;
		}
	}

	return true;
}
