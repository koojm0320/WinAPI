//#include <windows.h>
//#include <tchar.h>
#include "Stdafx.h"
#include "MainGame.h"
//#include "CommonMacroFunction.h"



// ���� ����:
// 
// �ν��Ͻ�: �����찡 ���� ����ǰ� �ִ� ���α׷��� Ȯ���ϱ� ���� ��.
// ���� ���α׷��̸� ���� �ν��Ͻ� ���� ������. -> Ŭ������ �޸𸮿� ������ ��ü -> ����ǰ� �ִ� ������ ���α׷�
HINSTANCE _hInstance;
// ������ �ڵ�(=â)
HWND _hWnd;
POINT _ptMouse;

void setWindowSize(int x, int y, int width, int height);

MainGame* _mg;
int centerX, centerY;
RECT _rc1, _rc2;
/*
* LP(�ο�������) C(const) T(tchar)
�򰥸��� �Լ� ������ Ȯ��
LPSTR			= char*
LPCSTR			= const char*
LPTSTR			= tchar*
LPCTSTR			= const tchar*
*/

// ������ Ÿ��Ʋ

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LPTSTR _lpszClass = TEXT("Window API"); // ����
//TCHAR* pszString = _T("Windows API");

/*		Ŭ������ ���� �۵��� �Ѵ�.

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
#define GET_WINDOWS_HANDLE()		(GET_WINDOWS_MANAGER()->getWindowsHandle())

class WindowsManager
{
public:
	HWND _hWnd = nullptr;
	HWND _hWnd = nullptr;


};
*/


// hInstance: ���α׷� �ν��Ͻ� �ڵ�
// hPrevInstance: ������ ����� �ν��Ͻ� �ڵ� (â �������� ��� ���)
// lpszCmdParam: ��������� �Էµ� ���α׷� �μ�
// nCmdShow: ���۵� ����
int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	_mg = new MainGame();
	_hInstance = hInstance;

	// 1-1. ������ â ����ü ���� -> �ʱ�ȭ
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;			// Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;			// ������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// ��� ����
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		// Ŀ��(C��Ÿ�� ���缭 NULL�� ������)
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// ������
	wndClass.hInstance = hInstance;		// �ĺ��� ����
	wndClass.lpfnWndProc = WndProc;		// ���ν���
	wndClass.lpszClassName = WINNAME;		// Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;				// �޴� �̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	// ��Ÿ�� (�ٽ� �׸��� ����)

	// 1-2. Ŭ���� ���
	RegisterClass(&wndClass);

	// 1-3. ȭ�鿡 ������ â ����
	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,
		WINSTART_X,
		WINSTART_Y,
		WINSIZE_X,
		WINSIZE_Y,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	// 1-4. â ȣ��
	ShowWindow(_hWnd, nCmdShow);
	//UpdateWindow(_hWnd);  �����ӿ�ũ ���� ������ ����Ѵ�.

	if (FAILED(_mg->init()))
		return 0;

	// 2.
	MSG message;
	//ZeroMemory(&message, sizeof(message));	������Ʈ ������ ���� ����.


	// �޽��� ���� �� ���� �縳�� �� ����
	//while (true)
	//{
	//	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	//	{
	//		if (message.message == WM_QUIT) break;
	//		TranslateMessage(&message);
	//		DispatchMessage(&message);
	//	}
	//}

	while (GetMessage(&message, 0, 0, 0))
	{
		// TranslateMessage: Ű���� �Է� �޽��� ó�� ���
		// �Էµ� Ű�� ����Ű���� Ȯ�� -> �빮��, �ҹ���, �ѱ� �� ���� �޽����� �߻���Ų��.
		// �� WM_CHAR: 
		TranslateMessage(&message);
		// DispatchMessage: ���ν������� ���޵� �޽����� ���� ������� ����
		DispatchMessage(&message);
	}

	_mg->release();
	UnregisterClass(WINNAME, hInstance);
	return (int)message.wParam;
}


// HWND: �޽��� ���� ��ȣ, iMessage: �޽����� ���� ��ȣ, WPARAM: unsigned int 
// -> ���콺 + Ű���� ���� üũ, LPARAM(���콺 ��ǥ Ȯ��)
// WndProc: �޽����� �ü���� ���� -> �ü���� ������ ȣ��ǰ� �Ѵ�. -> �����츦 ������ ��, �ݵ�� ��������� �Ѵ�.
// Proc ������ �޽����� ���� ó���ϴ� �� �ƴϰ�, Ư�� �޽������� ó���ϰ� �������� DefWindowProc���� ó���ϴ°� �Ϲ�����.
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->mainProc(hWnd, iMessage, wParam, lParam);
}
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0,0,width, height };
	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);	// ������ �⺻����.
	// Z���� - ���̾� ����
}