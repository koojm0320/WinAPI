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
const int moveCounter = 10;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;
    PAINTSTRUCT ps;

    int rc1Width = rc1.right - rc1.left;
    int rc1Height = rc1.bottom - rc1.top;

    int rc2Width =  rc2.right -  rc2.left;
    int rc2Height = rc2.bottom - rc2.top;

    switch (iMessage)
    {
    case WM_CREATE:
        rc1 = RectMake(100, 300, 100, 100);
        rc2 = RectMake(400, 300, 100, 100);
        
        break;
        // ���
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        DrawRectMake(hdc, rc2);
        DrawRectMake(hdc, rc1);
        TextOut(hdc, 350, 5, "�ʱ�ȭ: SPACE", strlen("�ʱ�ȭ: SPACE"));

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
            rc1.left -= moveCounter;
            rc1.right -= moveCounter;

            // 1���ڽ� �� �浹
            if (rc1.left < 0)
            {
                rc1.left = 0;
                rc1.right = rc1.left + rc1Width;
            }

            // 1, 2���ڽ� �浹
            if (rc1.left < rc2.right &&
                rc1.right > rc2.left &&
                rc1.bottom > rc2.top &&
                rc1.top < rc2.bottom)
            {
                rc2.left -= moveCounter;
                rc2.right -= moveCounter;
            }

            // 2���ڽ� �� �浹
            if (rc2.left < 0)
            {
                rc2.left = 0;
                rc2.right = rc2.left + rc2Width;
                rc1.left = rc2.right;
                rc1.right = rc1.left + rc1Width;
            }
            break;

        case VK_RIGHT:
            rc1.left += moveCounter;
            rc1.right += moveCounter;

            // 1���ڽ� �� �浹
            if (rc1.right > 800)
            {    
                rc1.right = 800;
                rc1.left = rc1.right - rc1Width;
            }

            // 1, 2���ڽ� �浹
            if (rc1.right > rc2.left && 
                rc1.left < rc2.right &&
                rc1.bottom > rc2.top && 
                rc1.top < rc2.bottom)
            {
                rc2.left += moveCounter;
                rc2.right += moveCounter;
            }

            // 2���ڽ� �� �浹
            if (rc2.right > 800)
            {
                rc2.right = 800;
                rc2.left = rc2.right - rc2Width;
                rc1.right = rc2.left;
                rc1.left = rc1.right - rc1Width;
            }

            break;

        case VK_UP:
            rc1.top -= moveCounter;
            rc1.bottom -= moveCounter;

            // 1���ڽ� �� �浹
            if (rc1.top < 0)
            {    
                rc1.top = 0;
                rc1.bottom = rc1.top + rc1Height;
            }

            // 1, 2�� �ڽ� �浹
            if (rc1.bottom > rc2.top &&
                rc1.top < rc2.bottom &&
                rc1.left < rc2.right &&
                rc1.right > rc2.left)
            {
                rc2.top -= moveCounter;
                rc2.bottom -= moveCounter;
            }

            // 2�� �ڽ� �� �浹
            if (rc2.top < 0)
            {
                rc2.top = 0;
                rc2.bottom = rc2.top + rc2Height;
                rc1.top = rc2.bottom;
                rc1.bottom = rc1.top + rc1Height;
            }


            break;

        case VK_DOWN:
            rc1.top += moveCounter;
            rc1.bottom += moveCounter;

            // 1�� �ڽ� �� �浹
            if (rc1.bottom > 800)
            {    
                rc1.bottom = 800;
                rc1.top = rc1.bottom - rc1Height;
            }

            // 1, 2�� �ڽ� �浹
            if (rc1.top < rc2.bottom &&
                rc1.bottom > rc2.top &&
                rc1.left < rc2.right &&
                rc1.right > rc2.left)
            {
                rc2.top += moveCounter;
                rc2.bottom += moveCounter;
            }

            // 2�� �ڽ� �� �浹
            if (rc2.bottom > 800)
            {     
                rc2.bottom = 800;
                rc2.top = rc2.bottom - rc2Height;
                rc1.bottom = rc2.top;
                rc1.top = rc1.bottom - rc1Height;
            }


            break;

        case VK_SPACE:
            rc1 = RectMake(100, 300, 100, 100);
            rc2 = RectMake(400, 300, 100, 100);
            break;

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