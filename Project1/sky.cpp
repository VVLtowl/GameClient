#include "main.h"
#include "renderer.h"
#include "model.h"
#include "gameObject.h"

#include "manager.h"
#include "scene.h"
#include "sky.h"

Model* Sky::m_Model;

void Sky::Init()
{
	ObjRendererInitNormal();
}

void Sky::Uninit()
{
}

void Sky::Update()
{
}

void Sky::Draw()
{
	ObjRendererDrawModel(this,m_Model);
}

void Sky::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\sky.obj");
}

void Sky::Unload()
{
	m_Model->Unload();
	delete m_Model;
}