#pragma once
#include "gameObject.h"

class Enemy :
    public GameObject,
	public ObjectRenderer
{
private:
	static Model* m_Model;


public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static void Load();
	static void Unload();
};

