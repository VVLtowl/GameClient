#pragma once
//#include "model.h"
class ModelCtrl
{
public:
	class Model* m_Model;
	void Load(const char* _name);
	void Unload();
};

