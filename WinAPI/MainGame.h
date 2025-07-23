#pragma once
#include "Stdafx.h"
#include "GameNode.h"

struct Ball
{
	float _circleX, _circleY;
};

class MainGame : public GameNode
{
private:
	GImage* _bgImage;
	//GImage* _plImage;
	//GImage* _nine;

	float _rotation;

	int _count;
	int _index;
	int _isLeft;
 
	int _circleRad;
	float _circleDX, _circleDY;
	float _angle;
	float _speed;
	float _space;

	std::vector<Ball> _ball;

	RECT rc;

	int _countA, _countB;
	int _alphaA, _alphaB;

	bool _isAlphaIncrease;

public:
	HRESULT init(void) override;
	void release(void) override;
	void update(void) override;
	void render(HDC hdc) override;
};

