#pragma once
#include <list>

// 만약 코어 없는 프로젝트일 경우 사용하는 것

// 전방 선언
class SceneManager;
class GameObject;

class CScene
{
	friend SceneManager;

private:
	std::list<GameObject> m_listObj[(int)Layer::Size];

private:
	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

private:
	void SceneInit();
	void SceneUpdate();

protected:
	void addScene(GameObject gameObj);

public:
	CScene();
	virtual ~CScene();
};

