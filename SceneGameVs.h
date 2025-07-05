#pragma once
#include "Scene.h"

class Bat;
class Ball;
class TextGo;

class SceneGameVs : public Scene
{
protected:
	Bat* batLeft = nullptr;
	Bat* batRight = nullptr;
	Ball* ball = nullptr;

	TextGo* scoreMessage = nullptr;

	int leftScore = 0;
	int rightScore = 0;

	sf::RectangleShape line;

	sf::Vector2f ballStartPos;

	bool ballActive = false;

public:
	SceneGameVs();
	~SceneGameVs() override = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetGameOver();
	void LeftVictory() { leftScore++; }
	void RightVictory() { rightScore++; }
};

