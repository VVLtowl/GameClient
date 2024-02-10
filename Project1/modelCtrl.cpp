#include "main.h"
#include "renderer.h"
#include "model.h"
#include "modelCtrl.h"
//Model* ModelCtrl::m_Model;

void ModelCtrl::Load(const char* _name)
{
	m_Model = new Model();
	m_Model->Load(_name); //"asset/texture/UI.jpg",
}

void ModelCtrl::Unload()
{
	m_Model->Unload();
	delete m_Model;
}
