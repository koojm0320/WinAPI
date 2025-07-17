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
        // 출력
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        DrawRectMake(hdc, rc2);
        DrawRectMake(hdc, rc1);
        TextOut(hdc, 350, 5, "초기화: SPACE", strlen("초기화: SPACE"));

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

            // 1번박스 벽 충돌
            if (rc1.left < 0)
            {
                rc1.left = 0;
                rc1.right = rc1.left + rc1Width;
            }

            // 1, 2번박스 충돌
            if (rc1.left < rc2.right &&
                rc1.right > rc2.left &&
                rc1.bottom > rc2.top &&
                rc1.top < rc2.bottom)
            {
                rc2.left -= moveCounter;
                rc2.right -= moveCounter;
            }

            // 2번박스 벽 충돌
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

            // 1번박스 벽 충돌
            if (rc1.right > 800)
            {    
                rc1.right = 800;
                rc1.left = rc1.right - rc1Width;
            }

            // 1, 2번박스 충돌
            if (rc1.right > rc2.left && 
                rc1.left < rc2.right &&
                rc1.bottom > rc2.top && 
                rc1.top < rc2.bottom)
            {
                rc2.left += moveCounter;
                rc2.right += moveCounter;
            }

            // 2번박스 벽 충돌
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

            // 1번박스 벽 충돌
            if (rc1.top < 0)
            {    
                rc1.top = 0;
                rc1.bottom = rc1.top + rc1Height;
            }

            // 1, 2번 박스 충돌
            if (rc1.bottom > rc2.top &&
                rc1.top < rc2.bottom &&
                rc1.left < rc2.right &&
                rc1.right > rc2.left)
            {
                rc2.top -= moveCounter;
                rc2.bottom -= moveCounter;
            }

            // 2번 박스 벽 충돌
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

            // 1번 박스 벽 충돌
            if (rc1.bottom > 800)
            {    
                rc1.bottom = 800;
                rc1.top = rc1.bottom - rc1Height;
            }

            // 1, 2번 박스 충돌
            if (rc1.top < rc2.bottom &&
                rc1.bottom > rc2.top &&
                rc1.left < rc2.right &&
                rc1.right > rc2.left)
            {
                rc2.top += moveCounter;
                rc2.bottom += moveCounter;
            }

            // 2번 박스 벽 충돌
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