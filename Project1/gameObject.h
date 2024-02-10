#pragma once
class GameObject
{
protected:
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;

	bool m_Destroy;

public:
	GameObject() 
	{
		m_Position = D3DXVECTOR3(0, 0, 0);
		m_Rotation = D3DXVECTOR3(0, 0, 0);
		m_Scale = D3DXVECTOR3(1, 1, 1);
	}
	virtual ~GameObject() {}


	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;



	void SetPosition(D3DXVECTOR3 position)
	{
		m_Position = position;
	}
	D3DXVECTOR3 Position()
	{
		return m_Position;
	}
	void SetRotation(D3DXVECTOR3 rot)
	{
		m_Rotation = rot;
	}
	D3DXVECTOR3 Rotation()
	{
		return m_Rotation;
	}
	void SetScale(D3DXVECTOR3 scl)
	{
		m_Scale = scl;
	}
	D3DXVECTOR3 Scale()
	{
		return m_Scale;
	}

	D3DXVECTOR3 Forward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(
			&rot,
			m_Rotation.y,
			m_Rotation.x,
			m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;


		D3DXVec3Normalize(&forward, &forward);


		return forward;
	}
	D3DXVECTOR3 Up()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(
			&rot,
			m_Rotation.y,
			m_Rotation.x,
			m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._21;
		forward.y = rot._22;
		forward.z = rot._23;


		D3DXVec3Normalize(&forward, &forward);

		return forward;
	}
	D3DXVECTOR3 Right()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(
			&rot,
			m_Rotation.y,
			m_Rotation.x,
			m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._11;
		forward.y = rot._12;
		forward.z = rot._13;

		D3DXVec3Normalize(&forward, &forward);

		return forward;
	}

	D3DXVECTOR3 GetObbX();
	D3DXVECTOR3 GetObbZ();


	void SetDestroy()
	{
		m_Destroy = true;
	}
	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}
};

