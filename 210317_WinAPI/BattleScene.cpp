#include "BattleScene.h"
#include "Tank.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Missile.h"
#include "Image.h"
#include "PlayerShip.h"
#include "CommonFunction.h"
#include "BattleUi.h"
#include "config.h"

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
	//vEnemys;
	
	//hitBox
	//playerHitRc = {};
	
	HitBox();

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

	//Rectangle(hdc, vEnemyHitRc[0].left, vEnemyHitRc[0].top, vEnemyHitRc[0].right, vEnemyHitRc[0].bottom);

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
	// 더미 Rc
	RECT dummyRc = { };

	// 적 <-> 적
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (IntersectRect(&dummyRc, &vEnemyHitRc[i], &vEnemyHitRc[j]))
			{
				if (i == j) continue;
				else
				{
					//vEnemys[i]->Direction();
					//vEnemys[j]->Move();
				}
			}
		}
		
	}

	// 적 <-> 플레이어
	if (IntersectRect(&dummyRc, &vEnemyHitRc[0], &playerHitRc))
	{
		int x = 1;
	}


	// 적 미사일 <-> 플레이어

	// 플레이어 미사일 <-> 적

	// 적 미사일 <-> 플레이어 미사일

	// 적, 플레이어 <-> 벽돌

	for (int j = 0; j < TILE_X * TILE_Y; j++)
	{
		HitBox();
		for (int i = 0; i < 4; i++)
		{
			if (IntersectRect(&dummyRc, &vEnemys[i]->hitRc, &TileInfo[j].rcTile))
			{
				switch (TileInfo[j].tileType)
				{
				case TileType::NORMAL: case TileType::IRON: case TileType::RIVER: case TileType::EAGLE:
					switch (vEnemys[i]->GetState())
					{
						// 왼쪽으로 이동
					case 2:
						vEnemys[i]->SetPos({ float(TileInfo[j].rcTile.right + vEnemys[0]->GetSizeW() / 2),vEnemys[i]->GetPos().y });
						break;
						// 위로 이동
					case 0:
						vEnemys[i]->SetPos({ vEnemys[i]->GetPos().x,float(TileInfo[j].rcTile.bottom + vEnemys[0]->GetSizeH() / 2) });
						break;
						// 오른쪽으로 이동
					case 3:
						vEnemys[i]->SetPos({ float(TileInfo[j].rcTile.left - vEnemys[0]->GetSizeW() / 2),vEnemys[i]->GetPos().y });
						break;
						//아래로 이동
					case 1:
						vEnemys[i]->SetPos({ vEnemys[i]->GetPos().x ,float(TileInfo[j].rcTile.top - vEnemys[0]->GetSizeH() / 2) });

						break;
					}
					vEnemys[i]->SetIsCol(true);
					break;
				case TileType::BLACK:
					break;
				default:
					break;
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

void BattleScene::HitBox()
{
	// 플레이어 RECT
	playerHitRc = playerShip->GetShape();

	// enemy RECT
	vEnemys = enemyMgr->GetEnemys();
	for (int i = 0; i < 4; i++)
	{
		vEnemyHitRc.push_back(vEnemys[i]->hitRc);
	}
}
