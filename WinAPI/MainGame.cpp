#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	// 배경 이미지 주소값
	//_bgImage = new GImage;
	//_bgImage->init("Resources/Images/mario.bmp", WINSIZE_X, WINSIZE_Y);

	// 플레이어 이미지 주소값
	//_plImage = new GImage;
	//_plImage->init("Resources/Images/Object/Player.bmp", 60, 60, true, RGB(255, 0, 255));

	// 프레임 이미지 주소값
	// _프레임 작업할 리소스 = new GImage;
	// _프레임 작업할 리소스-> init("주소", WINSIZE_X / 2 - 200, WINSIZE_Y / 2 - 200,
	//							이미지 크기x, 이미지 크기y,
	// 							10, 2
	// 						true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("마리오", "Resources/Images/mario.bmp", WINSIZE_X, WINSIZE_Y);
	
	SCENEMANAGER->addScene("테스트 씬", new ImageResource);
	SCENEMANAGER->changeScene("테스트 씬");

	rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);

	_countA = _countB = 0;
	_alphaA = _alphaB = 0;

	_isAlphaIncrease = false;

	_count = 0;
	_index = 0;
	_isLeft = false;

	// 지렁이
	_circleRad = 10;
	_angle = 0.0f;
	_speed = 5.0f;
	_space = 15.0f;
	_circleDX = cos(_angle) * _speed;
	_circleDY = sin(_angle) * _speed;

	int length = 50;
	float startX = rand() % WINSIZE_X;
	float startY = rand() % WINSIZE_Y;

	_ball.clear();
	for (int i = 0; i < length; ++i)
	{
		_ball.push_back({ startX - i * _space, startY });
	}

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	//SAFE_DELETE(_bgImage);
	//SAFE_DELETE(_plImage);
	//SAFE_DELETE(_리소스);
}

void MainGame::update(void)
{
	GameNode::update();

	SCENEMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "게임 종료?", "종료확인", MB_OKCANCEL))
		{
			PostQuitMessage(0);
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		//rc.left -= 3;
		//rc.right -= 3;
		_angle -= 0.07f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//rc.left += 3;
		//rc.right += 3;

		_angle += 0.07f;
	}

	_circleDX = cos(_angle) * _speed;
	_circleDY = sin(_angle) * _speed;

	// 원이 벽에 튕기는 로직
	_ball[0]._circleX += _circleDX;
	_ball[0]._circleY += _circleDY;

	if (_ball[0]._circleX - _circleRad < 0)
	{
		_ball[0]._circleX = _circleRad;
		_angle = 3.141592f - _angle;
	}
	else if (_ball[0]._circleX + _circleRad > WINSIZE_X)
	{
		_ball[0]._circleX = WINSIZE_X - _circleRad;
		_angle = 3.141592f - _angle;
	}

	if (_ball[0]._circleY - _circleRad < 0)
	{
		_ball[0]._circleY = _circleRad;
		_angle *= -1;
	}
	else if (_ball[0]._circleY + _circleRad > WINSIZE_Y)
	{
		_ball[0]._circleY = WINSIZE_Y - _circleRad;
		_angle *= -1;
	}

	// 앞 마디 공의 거리를 계산해서 경로 이동(위치 조정)
	for (size_t i = 1; i < _ball.size(); ++i)
	{
		float dx = _ball[i - 1]._circleX - _ball[i]._circleX;
		float dy = _ball[i - 1]._circleY - _ball[i]._circleY;

		// sqrt: 제곱근
		float distance = sqrt(dx * dx + dy * dy);
		
		if (distance > _space)
		{
			float followAngle = atan2(dy, dx);
			_ball[i]._circleX = _ball[i - 1]._circleX - cos(followAngle) * _space;
			_ball[i]._circleY = _ball[i - 1]._circleY - sin(followAngle) * _space;
		}
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

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	// ============

	// _bgImage->render(memDC, 0, 0);
	//_bgImage->alphaRender(memDC, _alphaA);

	//DrawRectMake(memDC, rc);
	//for (size_t i = 0; i < _ball.size(); i++)
	//{
	//	EllipseMakeCenter(memDC, _ball[i]._circleX, _ball[i]._circleY, _circleRad * 2, _circleRad * 2);
	//
	//}

	IMAGEMANAGER->alphaRender("마리오", getMemDC(), _alphaA);
	SCENEMANAGER->render();
	//IMAGEMANAGER->loopRender("배경 루프", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, 0);

	//_plImage->render(memDC, rc.left, rc.top);
	//_plImage->alphaRender(memDC, rc.left, rc.top, _alphaA);
	//_bgImage->render(memDC, rc.left, rc.right, 200, 200, 300, 300);
	//
	//_nine->frameRender(memDC, _nine->getX(), _nine->getY());



	// ============
	this->getBackBuffer()->render(getHDC());
}
