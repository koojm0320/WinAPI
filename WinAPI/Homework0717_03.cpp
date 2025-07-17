#include "Stdafx.h"

#pragma endregion

HINSTANCE _hInstance;
HWND _hWnd;
LPTSTR _lpszClass = TEXT("Windows API");

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

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
    wndClass.lpszClassName = _lpszClass;                                            // Ŭ���� �̸�           
    wndClass.lpszMenuName = NULL;                                                   // �޴� �̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                       // ��Ÿ�� (�ٽ� �׸��� ����)


    RegisterClass(&wndClass);

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

    ShowWindow(_hWnd, nCmdShow);




    MSG message;

    while (GetMessage(&message, 0, 0, 0))
    {

        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return message.wParam;
}

RECT rc1;
RECT rc2;
RECT soul;
const int moveCounter = 10;

// ���� + ��ȥ ���� �����̴� �Լ�
// ���� <-> ���� �浹 ���� bool
// void MoveLogic(rc1, soul) -> void MoveLogic(rc2, soul)

void BoxMove(RECT& rc, RECT& soul, int horizontal, int vertical)
{
    rc.left += horizontal;
    rc.right += horizontal;
    rc.top += vertical;
    rc.bottom += vertical;

    int rcWidth = rc.right - rc.left;
    int rcHeight = rc.bottom - rc.top;

    int soulWidth = soul.right - soul.left;
    int soulHeight = soul.bottom - soul.top;

    if (soul.left < rc.left) 
    {
        soul.left = rc.left;
        soul.right = soul.left + soulWidth;
    }
    if (soul.right > rc.right) 
    {
        soul.right = rc.right;
        soul.left = soul.right - soulWidth;
    }
    if (soul.top < rc.top) 
    {
        soul.top = rc.top;
        soul.bottom = soul.top + soulHeight;
    }
    if (soul.bottom > rc.bottom) 
    {
        soul.bottom = rc.bottom;
        soul.top = soul.bottom - soulHeight;
    }

    if (rc.left < 0)
    {
        rc.left = 0;
        rc.right = rc.left + rcWidth;
    }

    if (rc.right > 800)
    {
        rc.right = 800;
        rc.left = rc.right - rcWidth;
    }

    if (rc.top < 0)
    {
        rc.top = 0;
        rc.bottom = rc.top + rcHeight;
    }

    if (rc.bottom > 800)
    {
        rc.bottom = 800;
        rc.top = rc.bottom - rcHeight;
    }
}

bool isCollide(RECT rc1, RECT rc2)
{
    if (rc1.right < rc2.left || rc1.left > rc2.right || rc1.bottom < rc2.top || rc1.top > rc2.bottom)
    {
        return false;
    }
    return true;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;
    PAINTSTRUCT ps;

    switch (iMessage)
    {
    case WM_CREATE:
        rc1 = RectMake(100, 300, 150, 150);
        rc2 = RectMake(400, 300, 150, 150);
        soul = RectMake(150, 350, 75, 75);

        break;

        // ���
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        DrawRectMake(hdc, rc1);
        DrawRectMake(hdc, rc2);
        DrawRectMake(hdc, soul);

        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:
        break;

    case WM_RBUTTONDOWN:
        break;


    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            BoxMove(rc1, soul, -moveCounter, 0);
            break;

        case VK_RIGHT:
            BoxMove(rc1, soul, moveCounter, 0);
            break;

        case VK_UP:
            BoxMove(rc1, soul, 0, -moveCounter);
            break;

        case VK_DOWN:
            BoxMove(rc1, soul, 0, moveCounter);
            break;

        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);

            break;
        }

        if (isCollide(rc1, rc2))
        {
            RECT temp = rc1;
            rc1 = rc2;
            rc2 = temp;
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}