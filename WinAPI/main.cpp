// Project1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

//#pragma comment(linker, "/subsystem:console")
#pragma comment(linker, "/subsystem:windows")

#include <tchar.h>
#include < windows.h>

auto gWinClassName = TEXT("Windows Tutorial");

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(WM_DESTROY == msg)
	{
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	HINSTANCE hInst = (HINSTANCE)::GetModuleHandle(nullptr);
	WNDCLASS wc =					// Register the window class
	{
		CS_CLASSDC
		, WndProc
		, 0L
		, 0L
		, hInst
		, nullptr
		, LoadCursor(nullptr, IDC_ARROW)
		, (HBRUSH)GetStockObject(LTGRAY_BRUSH)
		, nullptr
		, gWinClassName
	};
	::RegisterClass(&wc);

	HWND hWnd = CreateWindow(gWinClassName
		, gWinClassName
		, WS_OVERLAPPEDWINDOW| WS_VISIBLE
		, 20
		, 10
		, 800
		, 600
		, nullptr
		, nullptr
		, hInst
		, nullptr);

	::ShowWindow(hWnd, SW_SHOW);
	::UpdateWindow(hWnd);
	::ShowCursor(TRUE);

	MSG msg{};
	while(msg.message!=WM_QUIT)
	{
		if(GetMessage(&msg, nullptr, 0U, 0U))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
	::UnregisterClass(gWinClassName, hInst);

	return 0;
}
