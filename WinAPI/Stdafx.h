#pragma once

// DXGI ���� �׷��� �������̽� ��ũ�� ���� ��� ���
#pragma warning(disable : 4005)

// ������ OS�� ���� Windows������� �ڵ忡 ���Ե� �Լ�, ��� ���� �����ϴ� �� ����� �ȴ�.
#include <SDKDDKver.h>

// PCH -> Stdafx

#define WIN32_LEAN_AND_MEAN   

// Windows ��� (�ھ�)
#include <Windows.h>


// C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
// MBCS <-> WBCS
/*
MBCS
- �ƽ�Ű + ���� 1����Ʈ, �̿� ���� 2����Ʈ

WBCS
- 2����Ʈ, 4����Ʈ ó�� ����
*/
#include <tchar.h>


// C++ ��Ÿ�� ��� ����
#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <unordered_map>

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

#include "CommonMacroFuntion.h"