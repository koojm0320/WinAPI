#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;
	if (managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);
		RND->init();
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		SCENEMANAGER->init();
		// 석세스 오케이
		return S_OK;
	}
}

void GameNode::release(void)
{
	KillTimer(_hWnd, 1);

	RND->releaseSingleton();
	
	KEYMANAGER->releaseSingleton();
	
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();
	SAFE_DELETE(_backBuffer);
}

void GameNode::update(void)
{

	InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(void)
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);

		RND->releaseSingleton();
		KEYMANAGER->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

LRESULT GameNode::mainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);


		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
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
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

GameNode::GameNode()
{
}

GameNode::~GameNode()
{
}
