#pragma once
class TimeManager
{
private:
	static TimeManager* m_Instance;

public:
	static TimeManager* Instance() {
		if (m_Instance == nullptr)
			m_Instance = new TimeManager();
		return m_Instance;
	}

private:
	float timeScale;
	float timePerFrame;
	int fps;

	float targetTimeScale;
	float lerpRatio;
public:
	TimeManager()
	{
		timeScale =
			targetTimeScale = 1.0f;
		fps = 60;
		timePerFrame = 1.0f / (float)fps;

		lerpRatio = 0;
	}

	void SetFPS(int _fps)
	{
		fps = _fps;
		timePerFrame = 1.0f / (float)fps;
	}

	void SetTimeScale(float scale,float lerp)
	{
		targetTimeScale = scale;
		lerpRatio = lerp;
	}

	void UpdateTime()
	{
		//update time scale
		timeScale += (targetTimeScale - timeScale) * lerpRatio;
	}
	
	int FPS()
	{
		return fps;
	}
	float DeltaTime()
	{
		return timePerFrame * timeScale;
	}
};

