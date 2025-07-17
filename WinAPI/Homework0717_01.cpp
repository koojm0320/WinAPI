#include "Stdafx.h"

#pragma endregion

HINSTANCE _hInstance;
HWND _hWnd;
LPTSTR _lpszClass = TEXT("Windows API");

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

RECT rc;

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

void DrawCircle(HDC hdc, float cx, float cy, float rad)
{
    const int n = 360;
    for (int i = 0; i <= 360; ++i)
    {
        float angle = 2.0f * 3.141592f * i / n;
        float x = cx + rad * cosf(angle);
        float y = cy + rad * sinf(angle);

        if (i == 0)
        {
            MoveToEx(hdc, (int)x, (int)y, NULL);
        }
        else
        {
            LineTo(hdc, (int)x, (int)y);
        }
    }
}

void DrawStar(HDC hdc, float cx, float cy, float rad)
{
    POINT star[5];
    float angleZero = -3.141592f / 2.0f;

    for (int i = 0; i < 5; i++)
    {
        float angle = angleZero + 3.141592f * 2.0f * i / 5.0f;
        star[i].x = (LONG)(cx + rad * cosf(angle));
        star[i].y = (LONG)(cy + rad * sinf(angle));
    }

    MoveToEx(hdc, star[0].x, star[0].y, NULL);
    LineTo(hdc, star[2].x, star[2].y);
    LineTo(hdc, star[4].x, star[4].y);
    LineTo(hdc, star[1].x, star[1].y);
    LineTo(hdc, star[3].x, star[3].y);
    LineTo(hdc, star[0].x, star[0].y);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;
    PAINTSTRUCT ps;

    switch (iMessage)
    {
    case WM_CREATE:
        break;

        // ���
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        //EllipseMake(hdc, 200, 200, 300, 300);
        //DrawRectMake(hdc, rc);
        //MakeStar(hdc, 400, 400, 200);

        DrawCircle(hdc, 400, 400, 100);
        DrawStar(hdc, 400, 400, 100);

        for (int i = 0; i < 5; i++)
        {

        }

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
