#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;

DWORD CALLBACK loadingThread(LPVOID prc)
{
	// !Do Nothing
	return 0;
}

HRESULT SceneManager::init(void)
{
	_currentScene = nullptr;
	_loadingScene = nullptr;
	_readyScene = nullptr;


	return S_OK;
}

void SceneManager::release(void)
{
	mapSceneIter miSceneList = _mScenelist.begin();

	for (; miSceneList != _mScenelist.end();)
	{
		if (miSceneList->second != nullptr)
		{
			if (miSceneList->second == _currentScene)
			{
				miSceneList->second->release();

			}
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mScenelist.erase(miSceneList);
		}
		else ++miSceneList;
	}
	_mScenelist.clear();

	// Unreal에서는 for each를 쓰지 않음
	// 간편하지만, 안전하지 않은 방법
	//for each (auto scene in _mScenelist)
	//{
	//	scene.second->release();
	//	SAFE_DELETE(scene.second);
	//}
}

void SceneManager::update(void)
{
	if (_currentScene) _currentScene->update();
}

void SceneManager::render(void)
{
	if (_currentScene) _currentScene->render();

}

GameNode* SceneManager::addScene(std::string sceneName, GameNode* scene)
{
	if (!scene) return nullptr;

	_mScenelist.insert(make_pair(sceneName, scene));

	return nullptr;
}

GameNode* SceneManager::addLoadingScene(std::string sceneName, GameNode* scene)
{
	// !Do Nothing
	return nullptr;
}

HRESULT SceneManager::changeScene(std::string sceneName)
{
	mapSceneIter find = _mScenelist.find(sceneName);

	if (find == _mScenelist.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}

