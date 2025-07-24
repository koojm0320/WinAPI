#pragma once
#include "GImage.h"

static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);


class GameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	// HRESULT: 함수 성공 여부 체크 -> 32비트 정수형 (음수가 아니면 성공, 음수이면 실패)
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	GImage* getBackBuffer(void) { return _backBuffer; }
	// LRESULT: 일반적으로 콜백함수의 반환형으로 자주 사용됨
	// 메시지 처리가 끝나면 OS에게 신호를 주기 위한 값
	// switch -> -1, 0, 1 형태로 값을 알려준다. -> 공통적으로 0나오면 리턴

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT mainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode();
	virtual ~GameNode();
};

