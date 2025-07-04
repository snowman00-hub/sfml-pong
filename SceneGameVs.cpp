#include "stdafx.h"
#include "SceneGameVs.h"
#include "Bat.h"
#include "Ball.h"

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

	batLeft->SetVsMode();
	batRight->SetVsMode();
	batLeft->SetOrigin(Origins::MR);
	batRight->SetOrigin(Origins::ML);

	Scene::Init();
}

void SceneGameVs::Enter()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	batLeft->SetPosition({ 20.f, bounds.height * 0.5f });
	batRight->SetPosition({ bounds.width - 20.f, bounds.height * 0.5f });

	ballActive = false;

	Scene::Enter();
}

void SceneGameVs::Update(float dt)
{
	Scene::Update(dt);

	if (!ballActive)
	{
		batRightPos = batRight->GetPosition();
		batRightPos.x += ball->GetRadius();
		ball->SetPosition(batRightPos);

		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			ballActive = true;
			
			sf::Vector2f dir(-1.f, -1.f);
			dir.y = InputMgr::GetAxisRaw(Axis::Vertical);
			if (dir.y == 0.f)
				dir.y = -1.f;
			Utils::Normalize(dir);

			ball->Fire(dir, 500.f);
		}
	}
}

void SceneGameVs::SetGameOver()
{
	SCENE_MGR.ChangeScene(SceneIds::GameVs);
}