#pragma once
//#include "polygon2D.h"
//#include "camera.h"
//#include "field.h"
//#include "player.h"
//#include "bullet.h"
//#include "enemy.h"
//#include "explosion.h"
//#include "sky.h"
#include <list>
#include <vector>
#include <typeinfo>

#include "gameObject.h"
enum LayerType
{
	layerType_camera,
	layerType_3DObject,
	layerType_2DObject,
	layerType_2DUI,
	layerType_3DAudio,
	layerType_2DAudio,
	layerCount
};
class Scene
{
protected:
	std::list<GameObject*> m_GameObject[layerCount];
	//GameObject* m_GameObject[4];

public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Init() = 0;

	virtual void Uninit()
	{
		for (int i = 0; i < layerCount; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < layerCount; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Update();
			}

			m_GameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < layerCount; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	template<typename T>
	T* AddGameObject(int layer)
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject[layer].push_back(gameObject);

		return gameObject;
	}

	template <typename T>
	T* GetGameObject(int i)
	{
		for (GameObject* object : m_GameObject[i])
		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}
		return nullptr;
	}

	template <typename T>
	std::vector<T*> GetGameObjects(int i)
	{
		std::vector<T*> objects;
		for (GameObject* object : m_GameObject[i])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	virtual void DeleteGameObject(GameObject* obj)
	{
		obj->SetDestroy();
	}
};