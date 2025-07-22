#include "Stdafx.h"

HINSTANCE _hInstance;
HWND _hWnd;

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);
void updatePhysics(HWND hWnd);

RECT _rc1;
bool isSelected = false;

int pressX, pressY;
int upX, upY;
float deltatime = 1.0f;
float drag = 0.2f;
float vlX, vlY;
float accX, accY;
int centerX, centerY;
int currnetX, currnetY;

POINT downPt;               // 마우스를 처음 눌렀을 때의 화면 좌표

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


// 1. 마우스 누르고 있을 때, 마우스를 뗄 때의 좌표를 저장 
// 2. 두 좌표의 차이 : 속도 -> 저장, 크기(speed)도 저장
// 3. 가속도: 속도의 반대방향 (가속도 < 속도) 대략 0.1정도
// 4. 속도 = 가속도 * deltatime + 현재속도
// 5. 현재위치 =  속도 * deltatime + 위치 

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

void updatePhysics(HWND hWnd)
{
    // 드래그 중일 때는 물리 연산 중지
    if (isSelected) return;

    // 1. 가속도 계산
    accX = -vlX * drag;
    accY = -vlY * drag;

    // 2. 속도 업데이트
    vlX += accX;
    vlY += accY;

    // 3. 위치 업데이트
    currnetX += vlX;
    currnetY += vlY;

    // 벽 충돌 처리
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    if (currnetX < 0)
    {
        currnetX = 0;
        vlX *= -1; // 속도 방향 반전
    }
    if (currnetX > clientRect.right - 100)
    {
        currnetX = (float)(clientRect.right - 100);
        vlX *= -1;
    }
    if (currnetY < 0)
    {
        currnetY = 0;
        vlY *= -1;
    }
    if (currnetY > clientRect.bottom - 100)
    {
        currnetY = (float)(clientRect.bottom - 100);
        vlY *= -1;
    }

    // 최종 RECT 위치 업데이트
    SetRect(&_rc1, (int)currnetX, (int)currnetY, (int)currnetX + 100, (int)currnetY + 100);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;
    PAINTSTRUCT ps;

    static POINT pt = { 0,0 };
    char strPT[128];

    switch (iMessage)
    {
    case WM_TIMER:
        updatePhysics(hWnd); // 매 타이머 틱마다 물리 연산
        InvalidateRect(hWnd, NULL, TRUE); // 화면 다시 그리기 요청
        break;

    case WM_CREATE:
        currnetX = 100.0f;
        currnetY = 100.0f;
        SetRect(&_rc1, (int)currnetX, (int)currnetY, (int)currnetX + 100, (int)currnetY + 100);

        // 물리 루프를 위한 타이머 설정 (약 60 FPS)
        SetTimer(hWnd, 1, 16, NULL);

        break;

        // 출력
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        DrawRectMake(hdc, _rc1);

        // GetTickCount()


        EndPaint(hWnd, &ps);
        break;

    case WM_MOUSEMOVE:
        // 마우스 좌표 갱신
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        // 사각형 좌표 갱신
        if (isSelected == true)
        {
            currnetX = (float)(pt.x - pressX);
            currnetY = (float)(pt.y - pressY);
            SetRect(&_rc1, (int)currnetX, (int)currnetY, (int)currnetX + 100, (int)currnetY + 100);
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_LBUTTONDOWN:
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        // 사각형 내부를 클릭했는지 확인
        if (PtInRect(&_rc1, pt))
        {
            isSelected = true;
            // 속도 초기화
            vlX = 0;
            vlY = 0;
            // 사각형 좌상단부터 마우스 클릭 지점까지의 간격(offset) 저장
            pressX = pt.x - _rc1.left;
            pressY = pt.y - _rc1.top;
            // 던지기 효과를 위해 마우스를 누른 시점의 좌표 저장
            downPt = pt;
        }

        break;

    case WM_LBUTTONUP:
        if (isSelected)
        {
            isSelected = false;
            // 마우스를 뗄 때의 좌표
            int upX = LOWORD(lParam);
            int upY = HIWORD(lParam);

            // 처음 누른 좌표와 뗀 좌표의 차이로 "던지는" 속도를 계산
            // 값을 0.2 곱해서 속도를 적절히 조절
            vlX = (float)(upX - downPt.x) * 0.2f;
            vlY = (float)(upY - downPt.y) * 0.2f;
        }

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
        break;

    case WM_DESTROY:
        KillTimer(hWnd, 1);
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