#pragma once
#include "SingletonBase.h"

#define KEY_MAX 256

class KeyManager : public SingletonBase <KeyManager>
{
private:
	//bool _keyUp[KEY_MAX];
	//bool _keyDown[KEY_MAX];

	// bitset: STL -> 비트연산을 하기위한 함수 지원
	// set(), flip(), any, size(), reset() 등 이정도 있으면 포폴 만드는데에는 지장 없다.
	std::bitset<KEY_MAX> _KeyUp;
	std::bitset<KEY_MAX> _KeyDown;

public:
	HRESULT init(void);

	bool isOnceKeyUp(int key);
	bool isOnceKeyDown(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	std::bitset<KEY_MAX> getKeyUp(void) { return _KeyUp; }
	std::bitset<KEY_MAX> getKeyDown(void) { return _KeyDown; }

	void setKeyUp(int key, bool state) { _KeyUp.set(key, state); }
	void setKeyDown(int key, bool state) { _KeyDown.set(key, state); }
};

