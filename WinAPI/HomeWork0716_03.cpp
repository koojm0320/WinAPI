#include <Windows.h>
#include <tchar.h>

HWND _hWnd;
HINSTANCE _hInstance;
LPTSTR _lpszClass = (TEXT("Windows API"));

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow
)
{
	_hInstance = hInstance;

	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = _lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		_lpszClass,
		_lpszClass,
		WS_OVERLAPPEDWINDOW,
		100, 100,
		800, 800,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	ShowWindow(_hWnd, nCmdShow);

	MSG message;

	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}

RECT r = { 100, 100, 200, 200 };
int moveCounter = 10;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, r.left, r.top, r.right, r.bottom);
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		break;


	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			r.left -= moveCounter;
			r.right -= moveCounter;
			if (r.left < 0)
			{
				r.left = 0;
				r.right = r.left + 100;
			}
			break;
		case VK_RIGHT:
			r.left += moveCounter;
			r.right += moveCounter;
			if (r.right > 800)
			{
				r.right = 800;
				r.left = r.right - 100;
			}
			break;
		case VK_UP:
			r.top -= moveCounter;
			r.bottom -= moveCounter;
			if (r.top < 0)
			{
				r.top = 0;
				r.bottom = r.top + 100;
			}
			break;
		case VK_DOWN:
			r.top += moveCounter;
			r.bottom += moveCounter;
			if (r.bottom > 800)
			{
				r.bottom = 800;
				r.top = r.bottom - 100;
			}
			break;
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}