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

POINT downPt;               // ���콺�� ó�� ������ ���� ȭ�� ��ǥ

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR   lpszCmdParam,
    int     nCmdShow)
{

    _hInstance = hInstance;

    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;                                                        // Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0;                                                        // ������ ���� �޸�
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);                   // ��� ����
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                                 // ���콺 Ŀ��
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                               // ������ 
    wndClass.hInstance = hInstance;                                                 // �ĺ��� ����
    wndClass.lpfnWndProc = WndProc;                                                 // ���ν���
    wndClass.lpszClassName = WINNAME;                                               // Ŭ���� �̸�           
    wndClass.lpszMenuName = NULL;                                                   // �޴� �̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                       // ��Ÿ�� (�ٽ� �׸��� ����)


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


// 1. ���콺 ������ ���� ��, ���콺�� �� ���� ��ǥ�� ���� 
// 2. �� ��ǥ�� ���� : �ӵ� -> ����, ũ��(speed)�� ����
// 3. ���ӵ�: �ӵ��� �ݴ���� (���ӵ� < �ӵ�) �뷫 0.1����
// 4. �ӵ� = ���ӵ� * deltatime + ����ӵ�
// 5. ������ġ =  �ӵ� * deltatime + ��ġ 

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
    // �巡�� ���� ���� ���� ���� ����
    if (isSelected) return;

    // 1. ���ӵ� ���
    accX = -vlX * drag;
    accY = -vlY * drag;

    // 2. �ӵ� ������Ʈ
    vlX += accX;
    vlY += accY;

    // 3. ��ġ ������Ʈ
    currnetX += vlX;
    currnetY += vlY;

    // �� �浹 ó��
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    if (currnetX < 0)
    {
        currnetX = 0;
        vlX *= -1; // �ӵ� ���� ����
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

    // ���� RECT ��ġ ������Ʈ
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
        updatePhysics(hWnd); // �� Ÿ�̸� ƽ���� ���� ����
        InvalidateRect(hWnd, NULL, TRUE); // ȭ�� �ٽ� �׸��� ��û
        break;

    case WM_CREATE:
        currnetX = 100.0f;
        currnetY = 100.0f;
        SetRect(&_rc1, (int)currnetX, (int)currnetY, (int)currnetX + 100, (int)currnetY + 100);

        // ���� ������ ���� Ÿ�̸� ���� (�� 60 FPS)
        SetTimer(hWnd, 1, 16, NULL);

        break;

        // ���
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        DrawRectMake(hdc, _rc1);

        // GetTickCount()


        EndPaint(hWnd, &ps);
        break;

    case WM_MOUSEMOVE:
        // ���콺 ��ǥ ����
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        // �簢�� ��ǥ ����
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

        // �簢�� ���θ� Ŭ���ߴ��� Ȯ��
        if (PtInRect(&_rc1, pt))
        {
            isSelected = true;
            // �ӵ� �ʱ�ȭ
            vlX = 0;
            vlY = 0;
            // �簢�� �»�ܺ��� ���콺 Ŭ�� ���������� ����(offset) ����
            pressX = pt.x - _rc1.left;
            pressY = pt.y - _rc1.top;
            // ������ ȿ���� ���� ���콺�� ���� ������ ��ǥ ����
            downPt = pt;
        }

        break;

    case WM_LBUTTONUP:
        if (isSelected)
        {
            isSelected = false;
            // ���콺�� �� ���� ��ǥ
            int upX = LOWORD(lParam);
            int upY = HIWORD(lParam);

            // ó�� ���� ��ǥ�� �� ��ǥ�� ���̷� "������" �ӵ��� ���
            // ���� 0.2 ���ؼ� �ӵ��� ������ ����
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