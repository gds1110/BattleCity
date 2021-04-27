#include "BattleScene.h"
#include "Tank.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Missile.h"
#include "Image.h"
#include "Iori.h"
#include "PlayerShip.h"


HRESULT BattleScene::Init()
{
	bin = new Image();
	bin->Init("Image/backGround_01.bmp", WINSIZE_X, WINSIZE_Y);

	tank = new Tank();
	tank->Init();

	enemyMgr = new EnemyManager();
	enemyMgr->Init();

	playerShip = new PlayerShip();
	playerShip->Init();

	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(playerShip);
	SAFE_RELEASE(bin);
	SAFE_RELEASE(tank);
	SAFE_RELEASE(enemyMgr);
}

void BattleScene::Update()
{
	if (tank)
	{
		//tank->Update();
	}

	if (enemyMgr)
	{
		enemyMgr->Update();
	}

	if (playerShip)
	{
		playerShip->Update();
	}

	CheckCollision();
}

void BattleScene::Render(HDC hdc)
{
	if (bin)
	{
		bin->Render(hdc/*, -100, 100*/);
	}

	if (tank)
	{
		tank->Render(hdc);
	}

	if (enemyMgr)
	{
		enemyMgr->Render(hdc);
	}

	if (playerShip)
	{
		playerShip->Render(hdc);
	}
}

void BattleScene::CheckCollision()
{
	// 利 <-> 攀农 固荤老 
	float distance;
	FPOINT enemyPos;
	FPOINT missilePos;
	float x, y;
	int r1, r2;
	Missile* missileArray = tank->GetMissile();

	//for (int i = 0; i < enemyCount; i++)
	//{
	//	if (enemy[i].GetIsAlive() == false)	continue;

	//	for (int j = 0; j < tank->GetMissileCount(); j++)
	//	{
	//		if (missileArray[j].GetIsFired() == false)	continue;

	//		enemyPos = enemy[i].GetPos();
	//		missilePos = missileArray[j].GetPos();

	//		x = enemyPos.x - missilePos.x;
	//		y = enemyPos.y - missilePos.y;

	//		distance = sqrtf(x * x + y * y);

	//		r1 = enemy[i].GetSize() / 2;
	//		r2 = missileArray[j].GetSize() / 2;

	//		if (distance <= r1 + r2)
	//		{
	//			enemy[i].SetIsAlive(false);
	//			missileArray[j].SetIsFired(false);
	//			break;
	//		}
	//	}
	//}

	// 利 <-> 攀农

	// 利 固荤老 <-> 攀农

	// 利 固荤老 <-> 攀农 固荤老
}
