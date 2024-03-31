#include "JoyCon.h"
#include "connect.h"
#include "exceptions.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <cmath>

using namespace joy_con_bridge;

#include "WLJoyconInput.h"



std::function<void(float, float, float)> WLJoyconInput::m_EventOrientate;
std::function<void(float, float, bool)> WLJoyconInput::m_EventThrow;
JoyCon WLJoyconInput::m_Left = connect::getLeftJoyCon();
float WLJoyconInput::m_StickX=0;
float WLJoyconInput::m_StickY=0;
float WLJoyconInput::m_CenterYaw;
float WLJoyconInput::m_Yaw;
float WLJoyconInput::m_Pitch;
float WLJoyconInput::m_Roll;
float WLJoyconInput::q[4] = { 0,0,0,1 };
float WLJoyconInput::exInt=0;
float WLJoyconInput::eyInt=0; 
float WLJoyconInput::ezInt=0;
float	WLJoyconInput::m_ThrowPitch;
float	WLJoyconInput::m_GreatestAcc;
int		WLJoyconInput::m_ThrowCoolDown;

void WLJoyconInput::Init()
{
	m_CenterYaw = m_Yaw = 0;
}

void WLJoyconInput::Update()
{
	//update
	m_Left.poll();
	ButtonsState buttons = m_Left.getButtonsState();
	AnalogStick stick = m_Left.getLeftStick();
	ThreeAxesSensor acc = m_Left.getAccelerometer();
	ThreeAxesSensor gyro = m_Left.getGyroscope();

	//update yaw
	//m_Yaw = m_Yaw * 3.1415 / 180;
	//m_Yaw += gyro.z;
	//m_Pitch += gyro.y;
	m_Yaw += +gyro.x;

	//update ypr
	if(0)
	{
		float ax = acc.x;
		float ay = acc.y; 
		float az = acc.z;

		float norm = std::sqrt(ax * ax + ay * ay + az * az);
		ax = ax / norm;
		ay = ay / norm;
		az = az / norm;

		float vx = 2 * (q[1] * q[3] - q[0] * q[2]);
	    float vy = 2 * (q[0] * q[1] + q[2] * q[3]);
		float vz = q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3];

		float ex = ay * vz - az * vy;
		float ey = az * vx - ax * vz;
		float ez = ax * vy - ay * vx;

		float ki = 0.5;
		float kp = 1 - ki;

		exInt = exInt + ex * ki;
		eyInt = eyInt + ey * ki;
		ezInt = ezInt + ez * ki;
		
		float gx = gyro.x;
		float gy = gyro.y;
		float gz = gyro.z;

		gx = gx + kp * ex + exInt;
		gy = gy + kp * ey + eyInt;
		gz = gz + kp * ez + ezInt;

		float q0temp = q[0];
		float q1temp = q[1];
		float q2temp = q[2];
		float q3temp = q[3];

		float halfT = 0.0083;
		q[0] = q0temp + (-q1temp * gx - q2temp * gy - q3temp * gz) * halfT;
		q[1] = q1temp + (q0temp * gx + q2temp * gz - q3temp * gy) * halfT;
		q[2] = q2temp + (q0temp * gy - q1temp * gz + q3temp * gx) * halfT;
		q[3] = q3temp + (q0temp * gz + q1temp * gy - q2temp * gx) * halfT;

		norm = sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
		q[0] = q[0] / norm;
		q[1] = q[1] / norm;
		q[2] = q[2] / norm;
		q[3] = q[3] / norm;

		m_Yaw = m_Yaw + gz * halfT * 2 * 57.3;
		m_Pitch = asin(-2 * q[1] * q[3] + 2 * q[0] * q[2]) * 57.3;
		m_Roll = atan2(2 * q[2] * q[3] + 2 * q[0] * q[1], -2 * q[1] * q[1] - 2 * q[2] * q[2] + 1) * 57.3;
	}

	//check orientate
	{
		float gameX=0;
		float gameY=0;
		float gameZ=0;
		float needAcc = 3;
		float needStick = 0.1f;
		float needYaw = 0.0f;

		m_StickX = 0;
		m_StickY = 0;

		//use acc to check orientation
		if(false)
		{

			//check game Z axis
			if (acc.y < -needAcc)
				//forward
			{
				gameZ = 1;
			}
			else if (acc.y > needAcc)
				//back
			{
				gameZ = -1;
			}
			else
				//stop
			{
				gameZ = 0;
			}


			//check game X axis
			if (m_Yaw > m_CenterYaw + needYaw)
				//left
			{
				gameX = -1;
			}
			else if (m_Yaw < m_CenterYaw - needYaw)
				//right
			{
				gameX = 1;
			}
			else
				//stop
			{
				gameX = 0;
			}
		}
		
		//use stick to check orientation
		if(1)
		{
			if (stick.x < -needStick)
			{
				m_StickX = -1;
				gameX = -1;
			}
			else if (stick.x > needStick)
			{
				m_StickX = 1;
				gameX = 1;
			}

			if (stick.y < -needStick)
			{
				m_StickY = -1;
				gameZ = -1;
			}
			else if (stick.y > needStick)
			{
				m_StickY = 1;
				gameZ = 1;
			}
		}

		//reset the center yaw
		if (buttons.up)
		{
			m_CenterYaw = m_Yaw =m_Pitch =m_Roll=0;
		}

		if (m_EventOrientate != nullptr)
		{
			m_EventOrientate(gameX, gameY, gameZ);
		}
	}

	//check throw
	{
		//cool down
		if (m_ThrowCoolDown>0)
		{
			//m_ThrowCoolDown--;
			if (m_ThrowCoolDown == 0)
			{
				m_ThrowPitch = 0;
			}
			return;
		}


		if (m_GreatestAcc < acc.x)
		{
			m_ThrowPitch = gyro.y;
			m_GreatestAcc = acc.x;
		}

		//check throw
		float throwPower = 0;
		float needAcc = 12;
		if (acc.x < -needAcc)
		{
			//max 78
			throwPower = (std::abs(acc.x) - needAcc) / (78 - needAcc);

			//set cool down
			m_ThrowCoolDown = 60;

			bool trigger= buttons.zl;

			//reset greatest acc and throw pitch
			m_ThrowPitch = gyro.y;//(gyro.y > 0) ? 1 : -1;

			if (m_EventThrow != nullptr)
			{
				m_EventThrow(throwPower, m_ThrowPitch, trigger);
			}
		}
	}
}
