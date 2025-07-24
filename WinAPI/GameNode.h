#pragma once
#include "GImage.h"

static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);


class GameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	// HRESULT: �Լ� ���� ���� üũ -> 32��Ʈ ������ (������ �ƴϸ� ����, �����̸� ����)
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	GImage* getBackBuffer(void) { return _backBuffer; }
	// LRESULT: �Ϲ������� �ݹ��Լ��� ��ȯ������ ���� ����
	// �޽��� ó���� ������ OS���� ��ȣ�� �ֱ� ���� ��
	// switch -> -1, 0, 1 ���·� ���� �˷��ش�. -> ���������� 0������ ����

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT mainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode();
	virtual ~GameNode();
};

