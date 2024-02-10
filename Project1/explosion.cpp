#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "explosion.h"
ID3D11ShaderResourceView* Explosion::m_Texture;
void Explosion::Init()
{
	Obj2DRendererInitNormal();
	Obj2DRendererSetAnime(0, 16, 4, 4);

	m_Position = { 0,0,0 };
	m_Rotation = { 0,0,0 };
	m_Scale = { 1,1,1 };
}

void Explosion::Uninit()
{
	Obj2DRendererRelease();
}

void Explosion::Update()
{
	m_FrameCount += 0.3f;
	//m_Rotation.x += 0.06f;
	//m_Rotation.y += 0.06f;
	m_Rotation.z += 0.06f;

	if (m_FrameCount >= m_MaxFrameCount)
	{
		SetDestroy();
		return;
	}
}

void Explosion::Draw()
{
	Obj2DRendererDrawBillBoard(this, m_Texture);
}

void Explosion::Load()
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

void Explosion::Unload()
{
	m_Texture->Release();
}
