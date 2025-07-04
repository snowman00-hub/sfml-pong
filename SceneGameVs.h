#pragma once
#include "Scene.h"

class Bat;
class Ball;

class SceneGameVs : public Scene
{
protected:
	Bat* batLeft = nullptr;
	Bat* batRight = nullptr;
	Ball* ball = nullptr;

	bool ballActive = false;

	sf::Vector2f batRightPos;

public:
	SceneGameVs();
	~SceneGameVs() override = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;

	void SetGameOver();
};

