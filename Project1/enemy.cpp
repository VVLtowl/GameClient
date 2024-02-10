#include "main.h"
#include "renderer.h"
#include "model.h"
#include "enemy.h"

Model* Enemy::m_Model;
void Enemy::Init()
{
	ObjRendererInitNormal();

	m_Position = D3DXVECTOR3(0, 0, 0);
	m_Rotation = D3DXVECTOR3(0, 70, 0);
	m_Scale = D3DXVECTOR3(1, 1, 2);

}

void Enemy::Uninit()
{
	ObjRendererRelease();
}

void Enemy::Update()
{
}

void Enemy::Draw()
{

	ObjRendererDrawModel(this, m_Model);
}

void Enemy::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\cube.obj");
	//m_Model->Load("asset\\model\\torus.obj"); //"asset/texture/UI.jpg",
}

void Enemy::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

