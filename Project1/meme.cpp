
#include "main.h"
#include "renderer.h"
#include "model.h"
#include "gameObject.h"

#include "manager.h"
#include "scene.h"
#include "meme.h"
#include "enemy.h"

Model* Meme::m_Model;
//ModelCtrl* Meme::m_ModelCtrl;

void Meme::Init()
{
	ObjRendererInitNormal();
}

void Meme::Uninit()
{
}

void Meme::Update()
{
	m_Position += {0, 0, 1};
	if (m_Position.z > 100)
	{
		m_Position.z = -100;
		this->SetDestroy();
	}

	Scene* scene = Manager::GetScene();

	//check enemy
	std::vector<Enemy*> enemyList = scene->GetGameObjects<Enemy>(1);
}

void Meme::Draw()
{
	ObjRendererDrawModel(this, m_Model);
}

void Meme::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\torus.obj");
	//m_Model->Load("asset\\model\\torus.obj"); //"asset/texture/UI.jpg",
}

void Meme::Unload()
{
	m_Model->Unload();
	delete m_Model;
}


