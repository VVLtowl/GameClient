
#include "main.h"
#include "input.h"


BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];
POINT Input::curPt;
POINT Input::oldPt;
bool Input::isCursorShow;

void Input::Init()
{

	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );
	isCursorShow = true;
}

void Input::Uninit()
{


}

void Input::Update()
{
	if (false)
	{
		HWND hWnd = ::FindWindow(NULL, "DX11ÉQÅ[ÉÄ");
		RECT rect;
		GetWindowRect(hWnd, &rect);
		ClipMouseMove(rect);
	}


	memcpy( m_OldKeyState, m_KeyState, 256 );

	GetKeyboardState( m_KeyState );

	if (GetKeyTrigger('B'))
	{
		if (isCursorShow)
		{
			isCursorShow = false;
			HideCursor();
		}
		else
		{
			isCursorShow = true;
			ShowCursor();
		}

	}

}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}


//mouse------------------------
POINT Input::GetMousePos()
{
	POINT pt;
	GetCursorPos(&pt);

	return pt;
}

POINT Input::GetMouseScreenPos()
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	if (isCursorShow)return pt;

	GetCursorPos(&pt);
	HWND hWnd = ::FindWindow(NULL, "DX11ÉQÅ[ÉÄ");
	RECT rect;
	GetWindowRect(hWnd, &rect);
	pt.x -= rect.left;
	pt.y -= rect.top;
	pt.x = SCREEN_WIDTH / 2.0f - pt.x;
	pt.y = SCREEN_HEIGHT / 2.0f - pt.y;
	return pt;
}

bool Input::ClipMouseMove(RECT rect)
{
	return ClipCursor(&rect);
}

POINT Input::GetMouseMove()
{

	POINT pt;
	pt.x = 0;
	pt.y = 0;
	if (isCursorShow)return pt;


	GetCursorPos(&curPt);
	pt.x = curPt.x - oldPt.x;
	pt.y = curPt.y - oldPt.y;
	oldPt = curPt;
	HWND hWnd = ::FindWindow(NULL, "DX11ÉQÅ[ÉÄ");
	RECT rect;
	GetWindowRect(hWnd, &rect);

	if(true)
	{
		oldPt.x = (rect.left + rect.right) / 2.0f;
		oldPt.y = (rect.top + rect.bottom) / 2.0f;
		SetCursorPos(oldPt.x, oldPt.y);
	}
	if (false)
	{
		if (oldPt.x < rect.left)
		{
			oldPt.x = rect.left;
			SetCursorPos(oldPt.x, oldPt.y);
		}
		if (oldPt.x > rect.right)
		{
			oldPt.x = rect.right;
			SetCursorPos(oldPt.x, oldPt.y);
		}
		if (oldPt.y < rect.top)
		{
			oldPt.y = rect.top;
			SetCursorPos(oldPt.x, oldPt.y);
		}
		if (oldPt.y > rect.bottom)
		{
			oldPt.y = rect.bottom;
			SetCursorPos(oldPt.x, oldPt.y);
		}
	}

	return pt;
}

float Input::GetMouseMoveX()
{
	if (isCursorShow)return 0;

	GetCursorPos(&curPt);
	float moveX = curPt.x - oldPt.x;
	oldPt = curPt;
	HWND hWnd = ::FindWindow(NULL, "DX11ÉQÅ[ÉÄ");
	RECT rect;
	GetWindowRect(hWnd, &rect);

	oldPt.x = (rect.left + rect.right) / 2.0f;
	SetCursorPos(oldPt.x, oldPt.y);
	return moveX;
}

void Input::HideCursor() { 
	CONSOLE_CURSOR_INFO cursor; 
	cursor.bVisible = 0; 
	cursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
void Input::ShowCursor() {
	CONSOLE_CURSOR_INFO cursor; 
	cursor.bVisible = 1;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
