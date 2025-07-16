// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

// #include "framework.h"
#include <Windows.h>
#include <tchar.h>

#pragma region WinAPI
/*
▶API(Aplication Programming Interface)

- OS가 응용 프로그램 쪽에서 효율적으로 작업할 수 있도록 제공하는 함수의 집합

- 명령어의 집합 어플리케이션 프로그램에서 -> 오퍼레이팅 시스템의 기본적인 기능을 사용할 필요가 있는 경우
API에서 명령어 호출이 발생한다. (진행된다.)

EX)
하드웨어 ------ 운영체제(Windows) ------ 응용 프로그램
(API 함수)

● 장점

- 운영체제가 같으면 같은 기능의 집합을 사용하기에 *확장성 및 연동성, 그리고 유지 보수에 유리*
ㄴ 윈도우즈 != 리눅스

- 윈도우에서 구동되는 라이브러리화 된 툴킷 -> 에디터가 붙어 있는 라이브러리에서는 기본적으로 포함되어 있어
선행 지식을 요구할 때가 많은데 WinAPI가 그런 부분에서 도움이 된다.


● 단점

- 플랫폼 고착화 현상 발생 (가장 큰 단점)
ㄴ C언어로 개발된 플랫폼의 한계점 (BASE -> C언어)
    ㄴ 개발자의 역량으로 해결 가능 (CoCos2D, Unity2D 같은 것들)


▶ API 구조

(면접 질문 내용)
- 크게 3가지만 기억하자.
ㄴ a. EP
ㄴ b. ML (Message Loop)
ㄴ c. WP (WndProc)
*/
#pragma endregion

// 전역
// 인스턴스: 윈도우가 현재 실행되고 있는 프로그램을 확인하기 위한 값
//          같은 프로그램이면 같은 인스턴스 값을 가진다 -> 클래스가 메모리에 실제로 구현된 실체 -> 실행되고 있는 각각의 프로그램들
HINSTANCE _hInstance;

// 윈도우 핸들: 창
HWND _hWnd;

// LongPoint(LP)
// 윈도우 타이틀
LPTSTR _lpszClass = TEXT("Windows API");
// TCHAR* pszString = _T("Windows API");

/*
LPSTR   (Long Point String)         = char*
LPCSTR  (Long Point Const String)   = const char*
LPTSTR  (Long _T String)            = tchar*
LPCTSTR (Long _T Const String)      = const tchar*

▶ TCHAR (_t) -> 유니코드인지 멀티바이트인지 모를 때 사용할 수 있음

- char 또는 wchar_t 등으로 Type Casting 수행

- 문자열 상수를 사용하기 위해 사용된다.

EX)
멀티바이트 환경 -> (유니코드 환경) ->멀티바이트 환경 일 경우 사용

멀티바이트 환경 -> 멀티바이트 환경
유니코드 환경 -> 유니코드 환경
*/


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

//#define GET_WINDOWS_HANDLE()        (GET_WINDOWS_MANAGER->getWindowsHandle())
//
//class WindowsManager
//{
//public:
//    HWND _hWnd = nullptr;
//    HWND getWindowsHandle(void) const;
//};

// 유니코드 기반(w)
// winAPI 메인 함수
// hInstance: 프로그램에 대한 인스턴스 핸들
// hPrevInstance: 이전에 실행된 인스턴스 핸들
// lpszCmdParam: 명형형으로 입력된 프로그램 인수
// nCmdShow: 실행될 형태
// 경고 메세지: _In_, _In_opt_ 주석을 안적어서 나오는 오류임, 빌드는 잘 됨.
int APIENTRY WinMain(   HINSTANCE hInstance,
                        HINSTANCE hPrevInstance,
                        LPSTR   lpszCmdParam,
                        int     nCmdShow)
{

    _hInstance = hInstance;
    /*
    ▶ WinMain의 역할
    1. 윈도우 창을 세팅 후 화면에 띄운다.
        ㄴ 띄우기 위해서는 4가지를 처리해야 함

    2. 메세지 루프
    */

    //1-1 첫 번째 처리 요소. 위도우 창 구조체 선언 -> 초기화
    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;                                                        // 클래스 여분 메모리
    wndClass.cbWndExtra = 0;                                                        // 윈도우 여분 메모리
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);                   // 배경 색상
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                                 // 마우스 커서
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                               // 아이콘 
    wndClass.hInstance = hInstance;                                                 // 식별자 정보
    wndClass.lpfnWndProc = WndProc;                                                 // 프로시저
    wndClass.lpszClassName = _lpszClass;                                            // 클래스 이름           
    wndClass.lpszMenuName = NULL;                                                   // 메뉴 이름
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                       // 스타일 (다시 그리기 정보)

    // 1-2 두 번째 처리 요소. 클래스 등록
    RegisterClass(&wndClass);

    /*
    #define CreateWindowA
    (
    lpClassName, 
    lpWindowName, 
    dwStyle, 
    x, y,
    nWidth, nHeight, 
    hWndParent, 
    hMenu, 
    hInstance, 
    lpParam
    )
    */

    // 1-3 세 번째 처리 요소. 화면에 보여줄 창 생성
    _hWnd = CreateWindow
    (
        _lpszClass,
        _lpszClass,
        WS_OVERLAPPEDWINDOW,
        400,
        100,
        800,
        800,
        NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

    // 1-4 네 번째 처리 요소. 
    ShowWindow(_hWnd, nCmdShow);
    //UpdateWindow(_hWnd);



    // 2.
    // MSG : 구조체
    MSG message; 
    // MSG message{};
    // ZeroMemory(&message, sizeof(message));

    // 기본 메시지 루프
    // GetMassage: 메세지를 꺼내올 수 있을 때까지 멈춰 있는 함수 
    // ㄴ GetMassage-> 메세지 큐로부터 하나의 메세지를 가져오는 역할을 한다.
    //      ㄴ 단, 메세지 큐가 비어있을 경우 메세지가 들어올 때까지 대기
    // PeekMassage: 메세지가 없더라도 반환하는 함수

    // GetMessage와 PeekMessage
    
    /*
    while (true)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT) break;
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
    */
    while (GetMessage(&message, 0, 0, 0))
    {
        // TranslateMessage: 키보드 입력 메세지 처리 담당
        // ㄴ 입력된 키가 문자키인지 확인을 하고 대문자 / 소문자 / 한글 / 영문인지에 대한 메세지를 발생 시킨다.
        // ㄴ WM_CHAR: 
        TranslateMessage(&message);
        // DispatchMessage: 프로시저에서 전달된 메세지를 실제 윈도우로 전달
        DispatchMessage(&message);
    }

    return message.wParam;
}

// HWND: 메세지 구분 번호, iMessage: 메세지에 대한 번호, WPARAM: unsigned int -> 마우스 + 키보드, LPARAM: 마우스 클릭 좌표를 확인
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    /*
    - WndProc: 메세지를 윈도우 운영체제로 전달하고 운영체제가 강제로 호출되게 만듦.
    ㄴ 윈도우를 생성할 때 반드시 지정해 줘야 한다.

    - Proc 내에서 메세지를 전부 처리하는 게 아닌 특정 메세지만 처리하고 나머지는 DefWindowProc에서 처리하는 것이 일반적
    */

    // HDC: Handle Device Context
    HDC hdc;
    PAINTSTRUCT ps;

    char str[] = "오케이";
    // char str2* = "오케이";
    // str[2] = 'c';
    // str2[2] = 'c';
    // ㄴ char[]: 
    // ㄴ char* : 원칙적으로 수정이 불가능

    // 사각형의 좌표를 저장하기 위한 구조체       ★ 매우 중요 ! ★
    // 점을 찍는 역할
    RECT rc = { 100, 100, 200, 200 };
    
    switch (iMessage)
    {
    case WM_CREATE:
        break;

        // 출력
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        // TextOut(): hdc, x, y, string, stringlen (문자열 길이 반환)
        TextOut(hdc, 300, 300, "과제가 너무 재미있다", strlen("과제가 너무 재밌다"));

        SetTextColor(hdc, RGB(255, 0, 0));
        TextOut(hdc, 300, 400, "더 많은 과제가 필요", strlen("더 많은 과제가 필요"));

        // SetPixel(hdc, 300, 200, RGB(255, 0, 0));
        for (int i = 0; i < 10000; i++)
        {
            SetPixel(hdc, rand() % 800, rand() % 800, RGB(rand() % 255, rand() % 255, rand() % 255));
        }

        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                SetPixel(hdc, 400 + i, 400 + j, RGB(255, i * 2, i * 2));
            }
        }

        // MoveToEx(): SX, SY   시작점 지정
        MoveToEx(hdc, 400, 400, NULL);
        // EX, EY
        LineTo(hdc, 200, 400);

        MoveToEx(hdc, 400, 400, NULL);
        LineTo(hdc, 200, 200);
        
        Ellipse(hdc, 300, 100, 200, 200);

        // 선을 이어주는 역할
        // Rectangle(hdc, 100, 100, 200, 200);
        Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:
        break;

    case WM_RBUTTONDOWN:

        hdc = GetDC(hWnd);

        SetTextColor(hdc, RGB(0, 0, 255));
        TextOut(hdc, 350, 500, str, strlen(str));

        ReleaseDC(hWnd, hdc);

        break;


    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            break;

        case VK_RIGHT:
            break;

        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);

            break;
        }
        break;

    case WM_DESTROY:
        // bool -> T/F -> False -> 루프 종료
        PostQuitMessage(0);
        return 0;
    }

    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}