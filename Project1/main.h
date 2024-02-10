#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


#include <windowsx.h>
#include <winsock2.h>
#include <windows.h>
#include <assert.h>



#pragma warning(push)
#pragma warning(disable:4005)

#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>

#pragma warning(pop)



#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment(lib, "ws2_32.lib")


#define SCREEN_WIDTH	(960)
#define SCREEN_HEIGHT	(540)

#define GAMEOBJ_NUM (4)
#define PI (3.1415926f)

HWND GetWindow();
