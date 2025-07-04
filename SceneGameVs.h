#pragma once
#include "Scene.h"

class Bat;
class Ball;

class SceneGameVs : public Scene
{
protected:
	Bat* bat1 = nullptr;
	Ball* ball1 = nullptr;
	Bat* bat2 = nullptr;
	Ball* ball2 = nullptr;

	bool ballActive = false;

public:
	SceneGameVs();
	~SceneGameVs() override = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;

	void SetGameOver();
};

