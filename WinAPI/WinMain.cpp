
#include "Stdafx.h"
HINSTANCE _hInstance;

HWND _hWnd;
POINT _ptMouse = { 0,0 };

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

int centerX, centerY;
RECT _rc1, _rc2;

int APIENTRY WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPSTR       lpszCmdParam,
    int         nCmdShow
)
{

    _hInstance = hInstance;

    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;                                                        // 클래스 여분 메모리
    wndClass.cbWndExtra = 0;                                                        // 윈도우 여분 메모리
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);                   // 배경 색상
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                                 // 마우스 커서
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                               // 아이콘 
    wndClass.hInstance = hInstance;                                                 // 식별자 정보
    wndClass.lpfnWndProc = WndProc;                                                 // 프로시저
    wndClass.lpszClassName = WINNAME;                                               // 클래스 이름           
    wndClass.lpszMenuName = NULL;                                                   // 메뉴 이름
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                       // 스타일 (다시 그리기 정보)


    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
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
        NULL
    );

    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

    ShowWindow(_hWnd, nCmdShow);

    MSG message;

    while (GetMessage(&message, 0, 0, 0))
    {

        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;
    PAINTSTRUCT ps;

    static POINT pt = { 0,0 };
    char strPT[128];

    switch (iMessage)
    {
    case WM_CREATE:
        _rc1 = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);
        _rc2 = RectMakeCenter(WINSIZE_X / 2 + 200, WINSIZE_Y / 2, 100, 100);

        centerX = WINSIZE_X / 2;
        centerY = WINSIZE_Y / 2;
        break;

        // 출력
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        // -> 숫자 -> 문자열 -> 출력
        wsprintf(strPT, "X: %d     Y: %d", pt.x, pt.y);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));
        
        DrawRectMake(hdc, _rc1);
        DrawRectMake(hdc, _rc2);

        Rectangle(hdc, centerX, centerY, 100, 100);

        EndPaint(hWnd, &ps);
        break;

    case WM_MOUSEMOVE:
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        InvalidateRect(hWnd, NULL, TRUE);

        break;

    case WM_LBUTTONDOWN:
        centerX = RND->getInt(WINSIZE_X);
        centerY = RND->getInt(WINSIZE_Y);

        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_RBUTTONDOWN:
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
        PostQuitMessage(0);
        return 0;
    }

    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    AdjustWindowRect(&rc, WINSTYLE, false);

    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}