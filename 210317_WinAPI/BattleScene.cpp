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

	StageLoad(2);


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
	// 히트박스 받아오기
	for (int i = 0; i < 4; i++)
	{
		//vEnemyHitRc[i] = enemyMgr->GetHitRc(i);
	}
	RECT imsiRC = {};
	// 적 <-> 적

	// 적 <-> 플레이어

	// 적 미사일 <-> 플레이어

	// 플레이어 미사일 <-> 적

	// 적 미사일 <-> 플레이어 미사일

	// 적, 플레이어 <-> 벽돌
	if (playerShip)
	{
		if (playerShip->GetIsAlive())
		{
			for (int i = 0; i < sizeof(TileInfo) / sizeof(TILE_INFO); i++)
			{
				if (IntersectRect(&imsiRC, &playerShip->GetShape(), &TileInfo[i].rcTile))
				{
					switch (TileInfo[i].tileType)
					{
					case TileType::BLACK:
						break;
					case TileType::BUSH:
						break;
					case TileType::EAGLE:
						break;
					case TileType::ICE:
						break;
					case TileType::IRON:
						break;
					case TileType::NORMAL:
						break;
					case TileType::RIVER:
						break;
					}
				}
			}
		}
	}
	
	// 적, 플레이어 <-> 강

	// 적, 플레이어 <-> 강철

	// 적, 플레이어 <-> 숲

	// 적, 플레이어 <-> 얼음

	// 적, 플레이어 미사일 <-> 벽돌
				   
	// 적, 플레이어 미사일 <-> 강
				   
	// 적, 플레이어 미사일 <-> 강철
				   
	// 적, 플레이어 미사일 <-> 숲
				   
	// 적, 플레이어 미사일 <-> 얼음

	// 적, 플레이어, 미사일 <-> 수리
	
}
