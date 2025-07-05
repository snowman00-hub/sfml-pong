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

	batLeft->SetLeft();
	batLeft->SetVsMode();
	batRight->SetVsMode();

	Scene::Init();
}

void SceneGameVs::Enter()
{
	ballActive = false;

	Scene::Enter();
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