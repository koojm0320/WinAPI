#include <Windows.h>
#include <tchar.h>

HWND _hWnd;
HINSTANCE _hInstance;
LPTSTR _lpszClass(TEXT("Windows API"));

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow
)
{
	_hInstance = hInstance;

	WNDCLASS wndClass{};

	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.lpszClassName = _lpszClass;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(_lpszClass, _lpszClass, WS_OVERLAPPEDWINDOW, 100, 100, 800, 800, NULL, NULL, hInstance, NULL);

	ShowWindow(_hWnd, nCmdShow);

	MSG message;

	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uint, WPARAM wparam, LPARAM lparam)
{
	switch (uint)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, uint, wparam, lparam);
}
