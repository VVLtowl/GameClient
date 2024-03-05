#pragma once

#include "scene.h"
class Game:
	public Scene
{
public:
	void AddPlayer(D3DXVECTOR3 pos);

public:
	void Init();
	void Uninit();
	void Update();
};

