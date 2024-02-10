#include "main.h"

#include "physics.h"

void Physics::PhysicsInitNormal(D3DXVECTOR3 _velo)
{
	velo = _velo;
	force = forceInv = { 0,0,0 };
	m = 1.0f;
}

void Physics::PhysicsInitNormal(D3DXVECTOR3 _velo, D3DXVECTOR3 _force, D3DXVECTOR3 _forceInv, float _m)
{
	velo = _velo;
	force = _force;
	forceInv = _forceInv;
	m = _m;
}

void Physics::PhysicsUpdate(GameObject* _obj)
{
	D3DXVECTOR3 pos = _obj->Position() + velo;
	_obj->SetPosition(pos);

	acc = (force + forceInv) / m;
	velo += acc;
}
