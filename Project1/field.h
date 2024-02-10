#pragma once
#include "gameObject.h"
#include "renderer.h"
#include <list>
#include <vector>
#include <typeinfo>

#define FIELD_V_SIZE_X (1.0f)
#define FIELD_V_SIZE_Y (FIELD_V_SIZE_X/4.0f*1.73f*2.0f)
#define FIELD_V_UNIT_X (FIELD_V_SIZE_X/4.0f*3.0f)
#define FIELD_V_UNIT_Y (FIELD_V_SIZE_Y)

#define FIELD_H_SIZE_X (1.0f)
#define FIELD_H_SIZE_Y (FIELD_H_SIZE_X/(2.0f*1.73f)*4.0f)
#define FIELD_H_UNIT_X (FIELD_H_SIZE_X)
#define FIELD_H_UNIT_Y (FIELD_H_SIZE_Y/4.0f*3.0f)

class Field:
	public GameObject,
	public Object2DRenderer
{
private:
	static ID3D11ShaderResourceView* m_Texture;

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static void Load();
	static void Unload();
};

class FieldManager
{
private:
	static std::list<Field*> m_Fields;
	static ID3D11ShaderResourceView* m_Texture;
public:
	static void InitFieldsVertical();//give up
	static void InitFieldsHorizontal();
	static void LoadTex();
	static void UnloadTex();
	static ID3D11ShaderResourceView* FieldTexture()
	{
		return m_Texture;
	}
};