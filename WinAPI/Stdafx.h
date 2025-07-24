#pragma once

// DXGI ���� �׷��� �������̽� ��ũ�� ���� ��� ���
#pragma warning(disable : 4005)

// ������ OS�� ���� Windows������� �ڵ忡 ���Ե� �Լ�, ��� ���� �����ϴ� �� ����� �ȴ�.
#include <SDKDDKver.h>

// PCH -> Stdafx

#define WIN32_LEAN_AND_MEAN

// �̹��� ���̺귯��
#pragma comment(lib, "msimg32.lib")

// Windows ��� (�ھ�)
#include <Windows.h>


// C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <time.h>
// MBCS <-> WBCS
/*
MBCS (��Ƽ����Ʈ)
- �ƽ�Ű + ���� 1����Ʈ, �̿� ���� 2����Ʈ

WBCS (�ƽ�Ű)
- 2����Ʈ, 4����Ʈ ó�� ����
*/
#include <tchar.h>


// C++ ��Ÿ�� ��� ����
#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <unordered_map>
#include <random>
#include <cassert>
// ��Ʈ ����� ���� ��Ʈ�� �Լ� ���°� ����ȴ�.
#include <bitset>
#include <string>

/*
// D2D / D3D ���
#include <d2d1.h>
#include <d2d1helper.h>
#include <d3dx9.h>
#include <D3Dx11.h>
#include <D3Dx11shader.h>
#include <dinput.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3d9x.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

ID2D1Factory*			_ID2DFactory = nullptr;
ID2D1HwndRenderTarget*	_ID2DRenderTarget = nullptr;
*/

// ���� ���� ��� ����
#include "CommonMacroFuntion.h"
#include "RnadomFuntion.h"
#include "KeyManager.h"
#include "ImageManager.h"

#define RND RandomFuntion::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()

// # ��ũ�� (������â �ʱ�ȭ) #

#define WINNAME			(LPTSTR)(TEXT("Windows API"))
#define WINSTART_X		400
#define WINSTART_Y		10
#define WINSIZE_X		800
#define WINSIZE_Y		1000
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}

// static
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;