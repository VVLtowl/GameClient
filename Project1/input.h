#pragma once


class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];

	static POINT oldPt;
	static POINT curPt;

	static bool isCursorShow;
public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );
	
	static POINT GetMousePos();
	static POINT GetMouseScreenPos();
	static POINT GetMouseMove();
	static float GetMouseMoveX();
	static bool ClipMouseMove(RECT rect);
	static void HideCursor();
	static void ShowCursor();
};
