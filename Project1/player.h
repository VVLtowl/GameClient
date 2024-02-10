#pragma once
#include "gameObject.h"

class Audio;

class Player:public GameObject
{
private:
	class Model* m_Model;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	Audio* shootSE;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

