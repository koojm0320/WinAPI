//#include <windows.h>
//#include <tchar.h>
#include "Stdafx.h"
#include "MainGame.h"
//#include "CommonMacroFunction.h"



// 전역 변수:
// 
// 인스턴스: 윈도우가 현재 실행되고 있는 프로그램을 확인하기 위한 값.
// 같은 프로그램이면 같은 인스턴스 값을 가진다. -> 클래스가 메모리에 구현된 객체 -> 실행되고 있는 각각의 프로그램
HINSTANCE _hInstance;
// 윈도우 핸들(=창)
HWND _hWnd;
POINT _ptMouse;

void setWindowSize(int x, int y, int width, int height);

MainGame* _mg;
int centerX, centerY;
RECT _rc1, _rc2;
/*
* LP(로우포인터) C(const) T(tchar)
헷갈리면 함수 원형을 확인
LPSTR			= char*
LPCSTR			= const char*
LPTSTR			= tchar*
LPCTSTR			= const tchar*
*/

// 윈도우 타이틀

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LPTSTR _lpszClass = TEXT("Window API"); // 제목
//TCHAR* pszString = _T("Windows API");

/*		클래스로 만들어도 작동은 한다.

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
#define GET_WINDOWS_HANDLE()		(GET_WINDOWS_MANAGER()->getWindowsHandle())

class WindowsManager
{
public:
	HWND _hWnd = nullptr;
	HWND _hWnd = nullptr;


};
*/


// hInstance: 프로그램 인스턴스 핸들
// hPrevInstance: 이전에 실행된 인스턴스 핸들 (창 여러개일 경우 사용)
// lpszCmdParam: 명령형으로 입력된 프로그램 인수
// nCmdShow: 시작될 형태
int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	_mg = new MainGame();
	_hInstance = hInstance;

	// 1-1. 윈도우 창 구조체 선언 -> 초기화
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;			// 클래스 여분 메모리
	wndClass.cbWndExtra = 0;			// 윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 배경 색상
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		// 커서(C스타일 맞춰서 NULL로 써주자)
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// 아이콘
	wndClass.hInstance = hInstance;		// 식별자 정보
	wndClass.lpfnWndProc = WndProc;		// 프로시저
	wndClass.lpszClassName = WINNAME;		// 클래스 이름
	wndClass.lpszMenuName = NULL;				// 메뉴 이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	// 스타일 (다시 그리기 정보)

	// 1-2. 클래스 등록
	RegisterClass(&wndClass);

	// 1-3. 화면에 보여줄 창 생성
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

	// 1-4. 창 호출
	ShowWindow(_hWnd, nCmdShow);
	//UpdateWindow(_hWnd);  프레임워크 구축 없으면 사용한다.

	if (FAILED(_mg->init()))
		return 0;

	// 2.
	MSG message;
	//ZeroMemory(&message, sizeof(message));	업데이트 윈도우 사용시 쓴다.


	// 메시지 루프 두 가지 양립할 수 없음
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
		// TranslateMessage: 키보드 입력 메시지 처리 담당
		// 입력된 키가 문자키인지 확인 -> 대문자, 소문자, 한글 에 대한 메시지를 발생시킨다.
		// ㄴ WM_CHAR: 
		TranslateMessage(&message);
		// DispatchMessage: 프로시저에서 전달된 메시지를 실제 윈도우로 전달
		DispatchMessage(&message);
	}

	_mg->release();
	UnregisterClass(WINNAME, hInstance);
	return (int)message.wParam;
}


// HWND: 메시지 구분 번호, iMessage: 메시지에 대한 번호, WPARAM: unsigned int 
// -> 마우스 + 키보드 상태 체크, LPARAM(마우스 좌표 확인)
// WndProc: 메시지를 운영체제에 전달 -> 운영체제가 강제로 호출되게 한다. -> 윈도우를 생성할 때, 반드시 지정해줘야 한다.
// Proc 내에서 메시지를 전부 처리하는 게 아니고, 특정 메시지만을 처리하고 나머지는 DefWindowProc에서 처리하는게 일반적임.
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
		SWP_NOZORDER | SWP_NOMOVE);	// 윈도우 기본값임.
	// Z오더 - 레이어 개념
}