#pragma once
#include <functional>

class WLJoyconInput
{
public:
	static void Init();
	static void Update();
	static void SetEventOrientate(std::function<void(float, float, float)> func)
	{
		m_EventOrientate = func;
	}
	static void SetEventThrow(std::function<void(float,float, bool)> func)
	{
		m_EventThrow = func;
	}
	static void CoolDownThrow()
	{
		m_ThrowCoolDown--;
	}
	static bool IsThrow()
	{
		return m_ThrowCoolDown == 60;
	}
	static bool IsCoolDownThrow()
	{
		return m_ThrowCoolDown > 0;
	}

public:
	static std::function<void(float, float, float)> m_EventOrientate;
	static std::function<void(float,float ,bool)> m_EventThrow;

	static class JoyCon m_Left;
	static float m_StickX;
	static float m_StickY;
	static float m_Yaw;
	static float m_Roll;
	static float m_Pitch;
	static float m_CenterYaw;

	static float m_ThrowPitch;
	static float m_GreatestAcc;
	static int m_ThrowCoolDown;

	static float q[4];
	static float exInt, eyInt, ezInt;
};

