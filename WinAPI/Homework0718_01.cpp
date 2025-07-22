#include "Stdafx.h"

HINSTANCE _hInstance;
HWND _hWnd;

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR   lpszCmdParam,
    int     nCmdShow)
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
    wndClass.lpszClassName = WINNAME;                                            // 클래스 이름           
    wndClass.lpszMenuName = NULL;                                                   // 메뉴 이름
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                       // 스타일 (다시 그리기 정보)


    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        WINNAME,
        WINNAME,
        WS_OVERLAPPEDWINDOW,
        WINSTART_X,
        WINSTART_X,
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

RECT _rc1;
int centerX, centerY;
int currnetX, currnetY;
bool isSelected = false;

// 1. 마우스 누르고 있을 때, 마우스를 뗄 때의 좌표를 저장 
// 2. 두 좌표의 차이 : 속도 -> 저장, 크기(speed)도 저장
// 3. 가속도: 속도의 반대방향 (가속도 < 속도) 대략 0.1정도
// 4. 속도 = 가속도 * deltatime + 현재속도
// 5. 현재위치 =  속도 * deltatime + 위치
int pressX, pressY;
int upX, upY;
float deltatime = 1;
float drag = 0.1;
float vlX, vlY;
float accX, accY;

DWORD lastUpdateTime = 0;

// vlX = upX - pressX;
// vlY = upY - pressY;
// 
// accX = vlX * (-1.0) * (drag);
// accY = vlY * (-1.0) * (drag);
// 
// vlX = accX * deltatime + vlX;
// vlY = accY * deltatime + vlY;
// 
// currnetX = vlX * deltatime + currnetX;
// currnetY = vlY * deltatime + currnetY;


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;
    PAINTSTRUCT ps;

    static POINT pt = { 0,0 };
    char strPT[128];

    switch (iMessage)
    {
    case WM_TIMER:
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_CREATE:
        _rc1 = RectMake(100, 100, 100, 100);

        centerX = WINSIZE_X / 2;
        centerY = WINSIZE_Y / 2;

        break;

        // 출력
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        DrawRectMake(hdc, _rc1);

        // GetTickCount()
        wsprintf(strPT, "X: %d     Y: %d", pt.x, pt.y);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));


        EndPaint(hWnd, &ps);
        break;

    case WM_MOUSEMOVE:
        // 마우스 좌표 갱신
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        // 사각형 좌표 갱신
        if (isSelected == true)
        {
            _rc1 = RectMake(pt.x - currnetX, pt.y - currnetY, 100, 100);
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_LBUTTONDOWN:
        if (pt.x < _rc1.right && 
            pt.x > _rc1.left &&
            pt.y < _rc1.bottom &&
            pt.y > _rc1.top)
        {
            pressX = pt.x - _rc1.left;
            pressY = pt.y - _rc1.top;
            isSelected = true;
        }

        break;

    case WM_LBUTTONUP:
        upX = LOWORD(lParam);
        upY = HIWORD(lParam);

        vlX = upX - pressX;
        vlY = upY - pressY;

        accX = vlX * (-1.0) * (drag);
        accY = vlY * (-1.0) * (drag);

        isSelected = false;

        InvalidateRect(hWnd, NULL, TRUE);

        break;

    case WM_RBUTTONDOWN:
        break;


    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);

            break;
        }
        InvalidateRect(hWnd, NULL, TRUE);
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