#pragma once
class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	SceneMgr() = default;
	~SceneMgr() = default;

	std::unordered_map<SceneIds, Scene*> scenes;

	SceneIds startScene = SceneIds::GameVs;
	SceneIds currentScene = SceneIds::None;
	SceneIds nextScene = SceneIds::None;

public:
	void Init();
	void Release();

	Scene* GetCurrentScene() { return scenes[currentScene]; }
	SceneIds GetCurrentSceneId() const { return currentScene; }
	void ChangeScene(SceneIds id);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

#define SCENE_MGR (SceneMgr::Instance())

