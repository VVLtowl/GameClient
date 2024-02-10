#pragma once
#include "gameObject.h"

class Camera:
	public GameObject
{
private :
	D3DXVECTOR3 m_Target;
	D3DXMATRIX m_ViewMatrix;
	D3DXMATRIX m_ProjectionMatrix;

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	bool CheckView(D3DXVECTOR3 pos);
	void SetTargetAndPosition(D3DXVECTOR3 target, D3DXVECTOR3 pos)
	{
		m_Target = target;
		m_Position = pos;
	}
	D3DXMATRIX ViewMatrix()
	{
		return m_ViewMatrix;
	}
	void SetViewMatrix(D3DMATRIX m)
	{
		m_ViewMatrix = m;
	}
};

