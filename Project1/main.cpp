
#include "main.h"
#include "manager.h"
#include "timeManager.h"
#include <iostream>

#include "input.h"
#include "NetworkGameData.h"
#include <thread>
#include <mutex>

const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "DX11ÉQÅ[ÉÄ";


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


HWND g_Window;

bool threadOver = false;
void RecvServerLoop()
{
	while (!threadOver)
	{
		Manager::update_recvServer.Update();
	}
}

HWND GetWindow()
{
	return g_Window;
}

int main(int argc, char* argv[])
{
#pragma region ========== FIXED ==========

	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
	HINSTANCE hPreInstance = NULL;
	TCHAR szCmdLine[1024];
	szCmdLine[0] = 0;
	LPTSTR lpCmdLine = szCmdLine;
	for (int i = 1; i < argc; i++)
	{
		if (i > 1)
		{
			strcpy(lpCmdLine, (" "));
			lpCmdLine = lpCmdLine + strlen((" "));
		}
		strcpy(lpCmdLine, argv[i]);
		lpCmdLine = lpCmdLine + strlen(argv[i]);
	}
	lpCmdLine = szCmdLine;
	int nCmdShow = SW_SHOWNORMAL;

#pragma endregion

	//join in server 
	std::cout << "input server ip:" << std::endl;
	std::cin>> Manager::m_Client.m_ServerIP;
	std::cout << "input server port:" << std::endl;
	std::cin >> Manager::m_Client.m_ServerPort;
	Manager::m_Client.StartUDP();


	//sprintf(msgBuf, "hello server!");
	//Manager::SendToServer(msgBuf);

	MsgContent msg;
	msg.BHID = (int)BHID_C2S::User_TryJoin;

	char msgBuf[LEN_MSG];
	EncodeMsgContent(msg, msgBuf);
	Manager::SendToServer(msgBuf);

	int ret = WinMain(hInstance, hPreInstance, lpCmdLine, nCmdShow);
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	RegisterClassEx(&wcex);

	g_Window = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		hInstance,
		NULL);





	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);

	Manager::Init();





	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;



	MSG msg;
	Manager::StartUpdateRecvServerThread();
	std::thread recvServer(RecvServerLoop);
	while(1)
	{
		//new update
		Manager::Update();

        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
		}
	}

	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);


	threadOver = true;

	Manager::Uninit();

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

