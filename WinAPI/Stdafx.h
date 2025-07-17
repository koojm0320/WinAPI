#pragma once

// DXGI 등등에서 그래픽 인터페이스 매크로 관련 출력 경고
#pragma warning(disable : 4005)

// 지원할 OS에 따라 Windows헤더에서 코드에 포함될 함수, 상수 등을 제어하는 데 사용이 된다.
#include <SDKDDKver.h>

// PCH -> Stdafx

#define WIN32_LEAN_AND_MEAN   

// Windows 헤더 (코어)
#include <Windows.h>


// C 런타임 헤더 파일
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
// MBCS <-> WBCS
/*
MBCS
- 아스키 + 영어 1바이트, 이외 문자 2바이트

WBCS
- 2바이트, 4바이트 처리 가능
*/
#include <tchar.h>


// C++ 런타임 헤더 파일
#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <unordered_map>

/*
// D2D / D3D 헤더
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