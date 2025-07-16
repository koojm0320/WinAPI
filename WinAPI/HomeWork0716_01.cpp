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
		810, 800,
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

int drawCount = 0;

void DrawText(HDC hdc, int index)
{
	
	switch (index)
	{
	case 0:
		MoveToEx(hdc, 50, 50, NULL);
		LineTo(hdc, 150, 50);
		LineTo(hdc, 150, 100);
		MoveToEx(hdc, 25, 150, NULL);
		LineTo(hdc, 200, 150);
		MoveToEx(hdc, 100, 150, NULL);
		LineTo(hdc, 100, 225);
		break;

	case 1:
		// Áø 300-450
		MoveToEx(hdc, 300, 50, NULL);
		LineTo(hdc, 400, 50);
		LineTo(hdc, 300, 150);
		MoveToEx(hdc, 350, 100, NULL);
		LineTo(hdc, 400, 150);
		MoveToEx(hdc, 450, 50, NULL);
		LineTo(hdc, 450, 150);
		MoveToEx(hdc, 325, 150, NULL);
		LineTo(hdc, 325, 225);
		LineTo(hdc, 450, 225);
		break;

	case 2:
		// ¸ð 550-700
		MoveToEx(hdc, 550, 50, NULL);
		LineTo(hdc, 700, 50);
		LineTo(hdc, 700, 150);
		LineTo(hdc, 550, 150);
		LineTo(hdc, 550, 50);
		MoveToEx(hdc, 625, 150, NULL);
		LineTo(hdc, 625, 225);
		LineTo(hdc, 550, 225);
		LineTo(hdc, 700, 225);
		break;

	case 3:
		// U 10-60
		MoveToEx(hdc, 10, 250, NULL);
		LineTo(hdc, 10, 350);
		LineTo(hdc, 20, 400);
		LineTo(hdc, 50, 400);
		LineTo(hdc, 60, 350);
		LineTo(hdc, 60, 250);
		break;

	case 4:
		// N 70-120
		MoveToEx(hdc, 70, 400, NULL);
		LineTo(hdc, 70, 250);
		LineTo(hdc, 120, 400);
		LineTo(hdc, 120, 250);
		break;

	case 5:
		// R 130-180
		MoveToEx(hdc, 130, 400, NULL);
		LineTo(hdc, 130, 250);
		LineTo(hdc, 170, 250);
		LineTo(hdc, 180, 260);
		LineTo(hdc, 180, 290);
		LineTo(hdc, 170, 300);
		LineTo(hdc, 130, 300);
		LineTo(hdc, 180, 400);
		break;

	case 6:
		// E 190-240
		MoveToEx(hdc, 240, 250, NULL);
		LineTo(hdc, 190, 250);
		LineTo(hdc, 190, 400);
		LineTo(hdc, 240, 400);
		MoveToEx(hdc, 190, 325, NULL);
		LineTo(hdc, 240, 325);
		break;

	case 7:
		// A 250-300
		MoveToEx(hdc, 250, 400, NULL);
		LineTo(hdc, 275, 250);
		LineTo(hdc, 300, 400);
		MoveToEx(hdc, 262, 325, NULL);
		LineTo(hdc, 288, 325);
		break;

	case 8:
		// L 310-360
		MoveToEx(hdc, 310, 250, NULL);
		LineTo(hdc, 310, 400);
		LineTo(hdc, 360, 400);
		break;

	case 9:
		// E 440-490
		MoveToEx(hdc, 490, 250, NULL);
		LineTo(hdc, 440, 250);
		LineTo(hdc, 440, 400);
		LineTo(hdc, 490, 400);
		MoveToEx(hdc, 440, 325, NULL);
		LineTo(hdc, 490, 325);
		break;

	case 10:
		// N 500-550
		MoveToEx(hdc, 500, 400, NULL);
		LineTo(hdc, 500, 250);
		LineTo(hdc, 550, 400);
		LineTo(hdc, 550, 250);
		break;

	case 11:
		// G 560-610
		MoveToEx(hdc, 610, 250, NULL);
		LineTo(hdc, 580, 250);
		LineTo(hdc, 560, 270);
		LineTo(hdc, 560, 380);
		LineTo(hdc, 580, 400);
		LineTo(hdc, 610, 400);
		LineTo(hdc, 610, 325);
		LineTo(hdc, 590, 325);
		break;

	case 12:
		// I 620-670
		MoveToEx(hdc, 620, 250, NULL);
		LineTo(hdc, 670, 250);
		MoveToEx(hdc, 645, 250, NULL);
		LineTo(hdc, 645, 400);
		MoveToEx(hdc, 620, 400, NULL);
		LineTo(hdc, 670, 400);
		break;

	case 13:
		// N 680-730
		MoveToEx(hdc, 680, 400, NULL);
		LineTo(hdc, 680, 250);
		LineTo(hdc, 730, 400);
		LineTo(hdc, 730, 250);
		break;

	case 14:
		// E 740-790
		MoveToEx(hdc, 790, 250, NULL);
		LineTo(hdc, 740, 250);
		LineTo(hdc, 740, 400);
		LineTo(hdc, 790, 400);
		MoveToEx(hdc, 740, 325, NULL);
		LineTo(hdc, 790, 325);
		break;

	}
}


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
		
		for (int  i = 0; i <= drawCount; i++)
		{
			DrawText(hdc, i);
		}
		
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		//hdc = GetDC(hWnd);
		
		if (drawCount < 15)
		{
			drawCount++;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else if (drawCount >= 14)
		{
			drawCount = 14;
		}
		else if (drawCount < 0)
		{
			drawCount = 0;
		}
		//ReleaseDC(hWnd, hdc);
		break;

	case WM_RBUTTONDOWN:

		hdc = GetDC(hWnd);

		if (drawCount < 15)
		{
			--drawCount;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (drawCount >= 14)
		{
			drawCount = 14;
		}
		else if (drawCount < 0)
		{
			drawCount = 0;
		}

		ReleaseDC(hWnd, hdc);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
