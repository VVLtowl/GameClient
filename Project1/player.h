#pragma once
#include "gameObject.h"

class Audio;

class Player:public GameObject
{
private:
	Audio* shootSE;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

