#include "MainGame.h"
#include "Stdafx.h"

HRESULT MainGame::init(void)
{
	GameNode::init();

	// 배경 이미지 주소값
	_bgImage = new GImage;
	_bgImage->init("Resources/Images/mario.bmp", WINSIZE_X, WINSIZE_Y);

	// 플레이어 이미지 주소값
	//_plImage = new GImage;
	//_plImage->init("Resources/Images/Object/Player.bmp", 60, 60, true, RGB(255, 0, 255));

	// 프레임 이미지 주소값
	// _프레임 작업할 리소스 = new GImage;
	// _프레임 작업할 리소스-> init("주소", WINSIZE_X / 2 - 200, WINSIZE_Y / 2 - 200,
	//							이미지 크기x, 이미지 크기y,
	// 							10, 2
	// 						true, RGB(255, 0, 255));


	

	rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);

	_countA = _countB = 0;
	_alphaA = _alphaB = 0;

	_isAlphaIncrease = false;

	_count = 0;
	_index = 0;
	_isLeft = false;

	_circleRad = 10;
	_circleDX = 10;
	_circleDY = 10;
	int length = 100;
	int startX = rand() % WINSIZE_X;
	int startY = rand() % WINSIZE_Y;

	_ball.clear();
	for (int i = 0; i < length; ++i)
	{
		_ball.push_back({ startX,startY });
	}

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SAFE_DELETE(_bgImage);
	//SAFE_DELETE(_plImage);
	//SAFE_DELETE(_리소스);
}

void MainGame::update(void)
{
	GameNode::update();

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "게임 종료?", "종료확인", MB_OKCANCEL))
		{
			PostQuitMessage(0);
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		rc.top -= 3;
		rc.bottom -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		rc.top += 3;
		rc.bottom += 3;
		// _isLeft = true;
	}	// _nine->setX(_nine->getX())
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		rc.left -= 3;
		rc.right -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		rc.left += 3;
		rc.right += 3;
	}

	// 원이 벽에 튕기는 로직
	_ball[0]._circleX += _circleDX;
	_ball[0]._circleY += _circleDY;

	if (_ball[0]._circleX - _circleRad < 0)
	{
		_ball[0]._circleX = _circleRad;
		_circleDX *= -1;
	}
	else if (_ball[0]._circleX + _circleRad > WINSIZE_X)
	{
		_ball[0]._circleX = WINSIZE_X - _circleRad;
		_circleDX *= -1;
	}

	if (_ball[0]._circleY - _circleRad < 0)
	{
		_ball[0]._circleY = _circleRad;
		_circleDY *= -1;
	}
	else if (_ball[0]._circleY + _circleRad > WINSIZE_Y)
	{
		_ball[0]._circleY = WINSIZE_Y - _circleRad;
		_circleDY *= -1;
	}

	for (int i = _ball.size() - 1; i > 0; --i)
	{
		_ball[i] = _ball[i - 1];
	}


	//_countA++;
	//if (_countA % 3 == 0)
	//{
	//	_alphaA++;
	//	if (_alphaA >= 255) _alphaA = 0;
	//}

	_countB++;
	if (_countB % 3 == 0)
	{
		_alphaB += 5;
		if (_alphaB >= 255) _alphaB = 0;
	}

	if (_alphaA == 0 || _alphaA == 255) _isAlphaIncrease = !_isAlphaIncrease;
	if (_isAlphaIncrease) _alphaA++; else _alphaA--;

	//// 프레임 처리
	//if (_isLeft)
	//{
	//	_count++;
	//
	//	_nine->setFrameY(1);
	//
	//	if (_count % 3 == 0)
	//	{
	//		_index--;
	//		if (_index < 0)
	//		{
	//			_index = 10;
	//		}
	//		_nine->setFrameX(_index);
	//	}
	//}
	//else
	//{
	//	_count++;
	//	_nine->setFrameY(0);
	//
	//	if (_count % 2 == 0)
	//	{
	//		_index++;
	//
	//		if (_index > 10)
	//		{
	//			_index = 0;
	//		}
	//		_nine->setFrameY(_index);
	//	}
	//}
}

void MainGame::render(HDC hdc)
{
	HDC memDC = this->getBackBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	// ============

	// _bgImage->render(memDC, 0, 0);
	//_bgImage->alphaRender(memDC, _alphaA);

	//DrawRectMake(memDC, rc);
	for (size_t i = 0; i < _ball.size(); i++)
	{
		EllipseMakeCenter(memDC, _ball[i]._circleX, _ball[i]._circleY, _circleRad * 2, _circleRad * 2);

	}

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		DrawRectMake(hdc, rc);
	}

	//_plImage->render(memDC, rc.left, rc.top);
	//_plImage->alphaRender(memDC, rc.left, rc.top, _alphaA);
	//_bgImage->render(memDC, rc.left, rc.right, 200, 200, 300, 300);
	//
	//_nine->frameRender(memDC, _nine->getX(), _nine->getY());



	// ============
	this->getBackBuffer()->render(hdc, 0, 0);
}
