#include "BattleScene.h"
#include "Tank.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Missile.h"
#include "Image.h"
#include "PlayerShip.h"
#include "CommonFunction.h"
#include "BattleUi.h"

HRESULT BattleScene::Init()
{
	SetClientRect(g_hWnd, TILE_X * TILESIZE+ UISPACE_X, TILESIZE * TILE_Y);

	bin = new Image();
	bin->Init("Image/mapImage2.bmp", TILE_X * TILESIZE + UISPACE_X, TILESIZE * TILE_Y);

	// 적 생성
	enemyMgr = new EnemyManager();
	enemyMgr->Init();

	playerShip = new PlayerShip();
	playerShip->Init();

	sampleTile = ImageManager::GetSingleton()->AddImage(
		"샘플타일", "Image/SamlpTile_2.bmp", SAMPLE_TILE_X * TILESIZE, SAMPLE_TILE_Y * TILESIZE,
		SAMPLE_TILE_X, SAMPLE_TILE_Y, true, RGB(0, 0, 0));

	battleUi = new BattleUi();
	battleUi->Init();

	StageLoad(1);


	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(battleUi);
	SAFE_RELEASE(playerShip);
	SAFE_RELEASE(bin);
	SAFE_RELEASE(enemyMgr);
}

void BattleScene::Update()
{
	
	if (enemyMgr)
	{
		enemyMgr->Update();
	}


	if (playerShip)
	{
		playerShip->Update();
	}

	if (battleUi)
	{
		battleUi->Update();
	}

	CheckCollision();
}

void BattleScene::Render(HDC hdc)
{
	if (bin)
	{
		bin->Render(hdc);
	}
	
	if (uiSpace)
	{
		uiSpace->Render(hdc, TILE_X * TILESIZE, 0);
	}
	
	

	if (enemyMgr)
	{
		enemyMgr->Render(hdc);
	}

	if (playerShip)
	{
		playerShip->Render(hdc);
	}

	// 맵 그리기
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		sampleTile->FrameRender(hdc,
			TileInfo[i].rcTile.left,
			TileInfo[i].rcTile.top,
			TileInfo[i].frameX,
			TileInfo[i].frameY);
	}

	if (battleUi)
	{
		battleUi->Render(hdc);
	}

}

void BattleScene::StageLoad(int stageNum)
{
	string fileName = "Save/saveMapData";
	fileName += to_string(stageNum) + ".map";
	DWORD readBytes;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (ReadFile(hFile, TileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readBytes, NULL))
	{

	}
	else
	{
		MessageBox(g_hWnd, "세이브로드실패", "error", MB_OK);
	}
	CloseHandle(hFile);
}

void BattleScene::CheckCollision()
{
	// 적 <-> 탱크 미사일 
	float distance;
	FPOINT enemyPos;
	FPOINT missilePos;
	float x, y;
	int r1, r2;
	//Missile* missileArray = tank->GetMissile();

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

	// 적 <-> 탱크

	// 적 미사일 <-> 탱크

	// 적 미사일 <-> 탱크 미사일
}
