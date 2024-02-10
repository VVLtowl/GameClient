#pragma once
#include "gameObject.h"

class Physics
{
protected:
	D3DXVECTOR3 velo;
	D3DXVECTOR3 force;
	D3DXVECTOR3 forceInv;
	float m;

	D3DXVECTOR3 acc;
public:
	virtual void PhysicsInitNormal(D3DXVECTOR3 _velo);
	virtual void PhysicsInitNormal(D3DXVECTOR3 _velo,
		D3DXVECTOR3 _force,
		D3DXVECTOR3 _forceInv,
		float m);
	virtual void PhysicsUpdate(GameObject* _obj);
};

