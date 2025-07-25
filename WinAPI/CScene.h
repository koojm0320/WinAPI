#pragma once
#include <list>

// ���� �ھ� ���� ������Ʈ�� ��� ����ϴ� ��

// ���� ����
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

