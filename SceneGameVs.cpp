#include "stdafx.h"
#include "SceneGameVs.h"
#include "Bat.h"
#include "Ball.h"
#include "TextGo.h"

SceneGameVs::SceneGameVs()
	: Scene(SceneIds::GameVs)
{
}

void SceneGameVs::Init()
{
	batLeft = (Bat*)AddGameObject(new Bat("BatLeft"));
	batRight = (Bat*)AddGameObject(new Bat("BatRight"));
	ball = (Ball*)AddGameObject(new Ball("Ball"));

	ball->SetBat(batRight);
	ball->SetBat2(batLeft);
	ball->SetVsMode();

	batLeft->SetLeft();
	batLeft->SetVsMode();
	batRight->SetVsMode();

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	line.setSize({ 5.f, bounds.height});
	line.setFillColor(sf::Color::Cyan);
	line.setPosition(bounds.width * 0.5f, 0.f);
	Utils::SetOrigin(line, Origins::TC);

	fontIds.push_back("fonts/DS-DIGIT.TTF");
	scoreMessage = (TextGo*)AddGameObject(new TextGo("fonts/DS-DIGIT.TTF"));
	scoreMessage->SetCharacterSize(100);
	scoreMessage->SetFillColor(sf::Color::Green);
	scoreMessage->SetPosition({ bounds.width * 0.5f,  0.f });

	guideMessage = (TextGo*)AddGameObject(new TextGo("fonts/DS-DIGIT.TTF"));
	guideMessage->SetCharacterSize(80);
	guideMessage->SetFillColor(sf::Color::Blue);
	guideMessage->SetPosition({ bounds.width * 0.5f,  bounds.height * 0.35f });
	guideMessage->SetString("Space to Start");

	Scene::Init();
}

void SceneGameVs::Enter()
{
	Scene::Enter();

	scoreMessage->SetString(std::to_string(leftScore) + "      " + std::to_string(rightScore));
	scoreMessage->SetOrigin(Origins::TC);
	guideMessage->SetActive(true);
	guideMessage->SetOrigin(Origins::TC);

	ballActive = false;
}

void SceneGameVs::Update(float dt)
{
	Scene::Update(dt);

	if (!ballActive)
	{
		ballStartPos = batRight->GetPosition();
		ballStartPos.x -= ball->GetRadius();
		ball->SetPosition(ballStartPos);

		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			ballActive = true;
			guideMessage->SetActive(false);
			
			sf::Vector2f dir(-1.f, -1.f);
			dir.y = InputMgr::GetAxisRaw(Axis::Vertical);
			if (dir.y == 0.f)
				dir.y = -1.f;
			Utils::Normalize(dir);

			ball->Fire(dir, 700.f);
		}
	}
}

void SceneGameVs::Draw(sf::RenderWindow& window)
{
	window.draw(line);

	Scene::Draw(window);
}

void SceneGameVs::SetGameOver()
{
	SCENE_MGR.ChangeScene(SceneIds::GameVs);
}