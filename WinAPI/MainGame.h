#pragma once
#include "Stdafx.h"
#include "GameNode.h"

class MainGame : public GameNode
{
private:
	GImage* _bgImage;
	//GImage* _plImage;

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

