#pragma once

#include "physics.h"
#include "life.h"
class GameObject;
class ObjectRenderer;

class Bullet :
	public GameObject,
	public ObjectRenderer,
	public Physics,
	public LifeTime

{
private:
	static class Model* m_Model;

public :
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	
	void StartPhysics(D3DXVECTOR3 velo);

	static void Load();
	static void Unload();
};

