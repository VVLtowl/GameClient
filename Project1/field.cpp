#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "field.h"



ID3D11ShaderResourceView* Field::m_Texture;
void Field::Init()
{
	Obj2DRendererInitSixEdge();
	Obj2DRendererSetAnime(0, 1, 1, 1);

	m_Position = { 0,0,0 };
	m_Rotation = { PI/2.0f,0,0 };
	m_Scale = { FIELD_V_SIZE_X,FIELD_V_SIZE_Y,1 };
}

void Field::Uninit()
{
	Obj2DRendererRelease();
}

void Field::Update()
{
	m_FrameCount += 0.02f;
	if (m_FrameCount >= m_MaxFrameCount)
	{
		m_FrameCount -= m_MaxFrameCount;
	}
	m_Scale = D3DXVECTOR3(1, 1, 1) * (0.5f + 0.5f * m_FrameCount / m_MaxFrameCount);
}

void Field::Draw()
{
	Obj2DRendererDrawSixEdge(this, m_Texture);
}

void Field::Load()
{
	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		"asset\\texture\\sixEdgeFloor.png",
		NULL,
		NULL,
		&m_Texture,
		NULL
	);


	assert(m_Texture);
}

void Field::Unload()
{
	m_Texture->Release();
}


//---------------------------------------------------------------------

#define FIELD_NUM_Y (5)
#define FIELD_NUM_X (5)

ID3D11ShaderResourceView* FieldManager::m_Texture;
void FieldManager::InitFieldsVertical()//give up
{
	bool isBig = true;
	int numX = FIELD_NUM_X;
	int numY = FIELD_NUM_Y + (isBig ? 1 : 0);
	float posY = -1;
	float posX = 0 - FIELD_V_SIZE_X * numX / 2.0f;
	float posZ = 0;
	D3DXVECTOR3 offset = { posX,posY,posZ };
	Scene* scene = Manager::GetScene();
	for (int i = 0; i < numX; i++) 
	{
		posX = 0 - FIELD_V_SIZE_X * numX / 2.0f + FIELD_V_UNIT_X * i;
		posZ = 0 + FIELD_V_SIZE_Y * numY / 2.0f;
		for (int j = 0; j < numY; j++)
		{
			posZ = 0 + FIELD_V_SIZE_Y * numY / 2.0f - FIELD_V_UNIT_Y * j;
			offset = { posX,posY,posZ };
			scene->AddGameObject<Field>(1)->SetPosition(offset);
		}
		isBig = !isBig;
		numY = FIELD_NUM_Y + (isBig ? 1 : 0);
	}
}

void FieldManager::InitFieldsHorizontal()
{
	bool isBig = true;
	int numX = FIELD_NUM_X + (isBig ? 1 : 0);
	int numY = FIELD_NUM_Y;
	float posY = -1;
	float posX = 0;
	float posZ = 0;
	D3DXVECTOR3 offset = { posX,posY,posZ };
	Scene* scene = Manager::GetScene();
	for (int i = 0; i < numY; i++)
	{
		posZ = 0 - FIELD_H_UNIT_Y * numY / 2.0f + FIELD_H_UNIT_Y * (0.5f + i);
		for (int j = 0; j < numX; j++)
		{
			posX= 0 - FIELD_H_UNIT_X * numX / 2.0f + FIELD_H_UNIT_X * (0.5f + j);
			offset = { posX,posY,posZ };
			scene->AddGameObject<Field>(layerType_2DObject)->SetPosition(offset);
		}
		isBig = !isBig;
		numX = FIELD_NUM_X + (isBig ? 1 : 0);
	}
}

void FieldManager::LoadTex()
{
	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		"asset\\texture\\explosion.png",
		NULL,
		NULL,
		&m_Texture,
		NULL
	);


	assert(m_Texture);
}

void FieldManager::UnloadTex()
{
	m_Texture->Release();
}