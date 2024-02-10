#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "gameObject.h"

#include "scene.h"
#include "enemy.h"
#include "field.h"
#include "bullet.h"
#include "explosion.h"

Model* Bullet::m_Model;
//ModelCtrl* Bullet::m_ModelCtrl;

void Bullet::Init()
{
	ObjRendererInitNormal();
	LifeTimeInit(2.0f);
	//LifeDistInit(this, 5.0f);
}

void Bullet::Uninit()
{
	ObjRendererRelease();
}

void Bullet::Update()
{
	Scene* scene = Manager::GetScene();

	PhysicsUpdate(this);
	LifeTimeUpdate();
	//LifeDistUpdate(this);

	D3DXVECTOR3 scale = D3DXVECTOR3(1, 1, 1) * (1.0f - LifeTimeRatio());
	//SetScale(scale);

	if (IsLifeTimeOut())
	{
		scene->AddGameObject<Explosion>(layerType_2DObject)->SetPosition(m_Position);
		this->SetDestroy();
	}


	//check enemy
	std::vector<Enemy*> enemyList = scene->GetGameObjects<Enemy>(1);

	for (Enemy* enemy : enemyList)
	{
		D3DXVECTOR3 enemyPosition = enemy->Position();

		D3DXVECTOR3 direction = m_Position - enemyPosition;
		float length = D3DXVec3Length(&direction);

		//sphere
#if 0
		if (length < 2.0f)
		{
			Explosion* explo = scene->AddGameObject<Explosion>(layerType_2DObject);
			explo->SetPosition(enemy->Position());
			explo->SetScale(D3DXVECTOR3(3, 3, 3));
			enemy->SetDestroy();
			this->SetDestroy();
			return;
		}
#endif

		//obb
#if 1
		D3DXVECTOR3 obbx, obbz;
		float obbLenx, obbLenz;

		obbx = enemy->GetObbX();
		obbLenx = D3DXVec3Length(&obbx);
		obbx /= obbLenx;

		obbz = enemy->GetObbZ();
		obbLenz = D3DXVec3Length(&obbz);
		obbz /= obbLenz;
		
		float lenx, lenz;
		lenx = D3DXVec3Dot(&obbx, &direction);
		lenz = D3DXVec3Dot(&obbz, &direction);

		if (fabs(lenx)<obbLenx&&
			fabs(lenz)<obbLenz)
		{
			Explosion* explo = scene->AddGameObject<Explosion>(layerType_2DObject);
			explo->SetPosition(Position());
			explo->SetScale(D3DXVECTOR3(1, 1, 1));
			//enemy->SetDestroy();
			this->SetDestroy();
			return;
		}

#endif

	}

	std::vector<Field*> fieldList = scene->GetGameObjects<Field>(1);

	for (Field* field : fieldList)
	{
		D3DXVECTOR3 fieldPosition = field->Position();

		D3DXVECTOR3 direction = m_Position - fieldPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 9.0f)
		{
			D3DXVECTOR3 force = -(9.0f - length) / 9.0f * direction / 60.0f;

			//fieldPosition += -(9.0f - length) / 9.0f * direction / 60.0f;

			//field->SetPosition(fieldPosition);
		}
	}
}

void Bullet::Draw()
{
	ObjRendererDrawModel(this, m_Model);
}

void Bullet::StartPhysics(D3DXVECTOR3 velo)
{
	PhysicsInitNormal(velo);
}

void Bullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\torus.obj");
	//m_Model->Load("asset\\model\\torus.obj"); //"asset/texture/UI.jpg",
}

void Bullet::Unload()
{
	m_Model->Unload();
	delete m_Model;
}


