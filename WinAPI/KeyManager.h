#pragma once
#include "SingletonBase.h"

#define KEY_MAX 256

class KeyManager : public SingletonBase <KeyManager>
{
private:
	//bool _keyUp[KEY_MAX];
	//bool _keyDown[KEY_MAX];

	// bitset: STL -> ��Ʈ������ �ϱ����� �Լ� ����
	// set(), flip(), any, size(), reset() �� ������ ������ ���� ����µ����� ���� ����.
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

