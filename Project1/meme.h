#pragma once

#include "gameObject.h"
#include "renderer.h"
class Meme:
	public GameObject,
	public ObjectRenderer
{
private:
	static class Model* m_Model;
	//public ModelCtrl
	//static class ModelCtrl* m_ModelCtrl;

	/*ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;*/

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static void Load();
	static void Unload();
};

