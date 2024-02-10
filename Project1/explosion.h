#pragma once
#include "gameObject.h"
#include "renderer.h"
class Explosion:
	public GameObject,
	public Object2DRenderer
{
private :
	static ID3D11ShaderResourceView* m_Texture;// = NULL;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static void Load();
	static void Unload();
};

