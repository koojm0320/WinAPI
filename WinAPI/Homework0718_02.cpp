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
RECT _rc1;
POINT polygon[6];

int centerX, centerY;
int randRadX, randRadY;
int elLeft, elRight, elTop, elBottom;
int randPrint;
int randVertex;

// ���� 1. ���� �� ���콺�� �߽��� �Ǵ� ����
// ���� 2. ũ�Ⱑ ������ ����
// ���� 3. ����� ������ ���� (��, �簢��, �ٰ���)

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) 
{
    HDC hdc;
    PAINTSTRUCT ps;

    static POINT pt = { 0,0 };
    char strPT[128];
    

    switch (iMessage)
    {
    case WM_CREATE:
        centerX = WINSIZE_X / 2;
        centerY = WINSIZE_Y / 2;

        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);


        switch (randPrint)
        {
        case 1:
            DrawRectMake(hdc, _rc1);
            break;
        case 2:
            Ellipse(hdc, elLeft, elTop, elRight, elBottom);
            break;
        case 3:
            Polygon(hdc, polygon, randVertex);
            break;
        }

        wsprintf(strPT, "X: %d     Y: %d", pt.x, pt.y);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));

        EndPaint(hWnd, &ps);
        break;

    case WM_MOUSEMOVE:
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_LBUTTONDOWN:
        centerX = LOWORD(lParam);
        centerY = HIWORD(lParam);

        randPrint = rand() % 3 + 1;

        randVertex = rand() % 3 + 3;    // ������ ���� ����

        randRadX = 30 + rand() % 150;
        randRadY = 30 + rand() % 150;

        switch (randPrint)
        {
        case 1:
            _rc1.left = centerX - randRadX / 2;
            _rc1.right = centerX + randRadX / 2;
            _rc1.top = centerY - randRadY / 2;
            _rc1.bottom = centerY + randRadY / 2;
            break;
        case 2:
            elLeft = centerX - randRadX / 2;
            elRight = centerX + randRadX / 2;
            elTop = centerY - randRadY / 2;
            elBottom = centerY + randRadY / 2;
            break;
        case 3:
            for (int i = 0; i < 5; i++)
            {
                polygon[i].x = centerX + rand() % 300 - 100;
                polygon[i].y = centerY + rand() % 300 - 100;
            }
            break;
        }


        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_LBUTTONUP:
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
