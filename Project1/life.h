#pragma once
class LifeTime
{
protected:
	float timeCount;
	float lifeTime;

public:
	void LifeTimeInit(float _lifeTime)
	{
		timeCount = 0;
		lifeTime = _lifeTime;
	}
	void LifeTimeUpdate()
	{
		timeCount += 1.0f / 60.0f;
	}
	bool IsLifeTimeOut()
	{
		if (timeCount >= lifeTime)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	float LifeTimeRatio()
	{
		if (lifeTime == 0)return 1.0f;
		return timeCount / lifeTime;
	}
};

class LifeDist
{
protected:
	D3DXVECTOR3 lastPos;
	float distCount;
	float maxDist;

public:
	void LifeDistInit(GameObject* _obj, float _maxDist)
	{
		distCount = 0;
		lastPos = _obj->Position();
		maxDist = _maxDist;
	}
	void LifeDistUpdate(GameObject* _obj)
	{
		D3DXVECTOR3 v = _obj->Position() - lastPos;
		distCount += D3DXVec3Length(&v);
		lastPos = _obj->Position();
	}
	bool IsLifeDistOver()
	{
		if (distCount >= maxDist)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	float LifeDistRatio()
	{
		if (maxDist == 0)return 1.0f;
		return distCount / maxDist;
	}
};

