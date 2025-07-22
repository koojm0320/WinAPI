#pragma once
#include "GImage.h"


class GameNode
{
private:
	GImage* _backBuffer;
	void setBackBuffer(void);

public:
	// HRESULT: �Լ� ���� ���� üũ -> 32��Ʈ ������ (������ �ƴϸ� ����, �����̸� ����)
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	GImage* getBackBuffer(void) { return _backBuffer; }
	// LRESULT: �Ϲ������� �ݹ��Լ��� ��ȯ������ ���� ����
	// �޽��� ó���� ������ OS���� ��ȣ�� �ֱ� ���� ��
	// switch -> -1, 0, 1 ���·� ���� �˷��ش�. -> ���������� 0������ ����
	LRESULT mainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode();
	virtual ~GameNode();
};

