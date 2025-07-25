#pragma once
#include "SingletonBase.h"

class GameNode;

class SceneManager : public SingletonBase <SceneManager>
{
public:
	typedef std::map<std::string, GameNode*> mapSceneList;
	typedef std::map<std::string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mScenelist;
	mapSceneList _mLoadingScenelist;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	GameNode* addScene(std::string sceneName, GameNode* scene);
	GameNode* addLoadingScene(std::string sceneName, GameNode* scene);

	HRESULT changeScene(std::string sceneName);

	friend DWORD CALLBACK loadingThread(LPVOID prc);

	SceneManager() {}
	~SceneManager() {}
};

