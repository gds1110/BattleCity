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
#include "Item.h"
#include "ItemManager.h"

HRESULT BattleScene::Init()
{

	SetClientRect(g_hWnd, TILE_X * TILESIZE+ UISPACE_X, TILESIZE * TILE_Y);


	playerShip = new PlayerShip();
	playerShip->Init();
	if (SceneManager::GetSingleton()->currStage != 1) {
		playerShip->PlayerLoad();
	}
	
	bin = new Image();
	bin->Init("Image/mapImage2.bmp", TILE_X * TILESIZE + UISPACE_X, TILESIZE * TILE_Y);

	// 적 생성
	enemyMgr = new EnemyManager();
	enemyMgr->Init();

	gameOn = true;

	itemMgr = new ItemManager();
	itemMgr->Init();

	sampleTile = ImageManager::GetSingleton()->AddImage(
		"샘플타일", "Image/SamlpTile_2.bmp", SAMPLE_TILE_X * TILESIZE, SAMPLE_TILE_Y * TILESIZE,
		SAMPLE_TILE_X, SAMPLE_TILE_Y, true, RGB(0, 0, 0));
	battleUi = new BattleUi();
	battleUi->Init();

	itemTimer = 0;


	//vEnemys;
	
	//hitBox
	//playerHitRc = {};
	
	HitBox();
	StageLoad(SceneManager::currStage);

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
	itemTimer += TimerManager::GetSingleton()->GetElapsedTime();
	int random;
	int typeRandom;

	if (itemTimer > 3.0f)
	{
		random = rand()% (TILE_X * TILE_Y);
		typeRandom = rand() % 8;
		if (TileInfo[random].tileType == TileType::BLACK)
		{
			itemMgr->DropItem({ TileInfo[random].rcTile.left+(TILESIZE/2),TileInfo[random].rcTile.top+ (TILESIZE / 2) }, typeRandom);
			itemTimer = 0;
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		if (SceneManager::currStage < 3)
		{
			//playerShip->SetPos({ 100,100 });
			playerShip->PlayerSave();
			SceneManager::GetSingleton()->currStage += 1;

		}
			SceneManager::GetSingleton()->ChangeScene("로딩씬");
			//Release();
			Init();
	}

	if (enemyMgr)
	{
		enemyMgr->Update();
		//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN)) {
		//	/*enemyMgr->miE1();
		//	enemyMgr->miE2();*/

		//	if (SceneManager::currStage < 3)
		//	{
		//		SceneManager::GetSingleton()->currStage += 1;
		//	}
		//	SceneManager::GetSingleton()->ChangeScene("로딩씬");
		//}

		//if (enemyMgr->GetIsEnemyCount() <= 0 && enemyMgr->GetRegenEnemyCount() <= 0)
		//{
		//	if (SceneManager::currStage < 3)
		//	{
		//		SceneManager::GetSingleton()->currStage += 1;
		//	}
		//	SceneManager::GetSingleton()->ChangeScene("로딩씬");
		//}
	}
	

	if (playerShip)
	{
		playerShip->Update();
	}

	if (battleUi)
	{
		battleUi->Update();
	}
	if (itemMgr)
	{
		itemMgr->Update();
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
	
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		if (TileInfo[i].tileType != TileType::BUSH)
		{
			sampleTile->FrameRender(hdc,
				TileInfo[i].rcTile.left,
				TileInfo[i].rcTile.top,
				TileInfo[i].frameX,
				TileInfo[i].frameY);
		}

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
		if (TileInfo[i].tileType == TileType::BUSH)
		{
			sampleTile->FrameRender(hdc,
				TileInfo[i].rcTile.left,
				TileInfo[i].rcTile.top,
				TileInfo[i].frameX,
				TileInfo[i].frameY);
		}
		
	}
	if (itemMgr)
	{
		itemMgr->Render(hdc);
	}
	if (battleUi)
	{
		battleUi->Render2(hdc,playerShip->GetHp(),enemyMgr->GetIsEnemyCount());
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

	// 적 <-> 적

	// 적 <-> 플레이어
	if (IntersectRect(&dummyRc, &vEnemyHitRc[0], &playerHitRc))
	{
		
	}


	// 적 미사일 <-> 플레이어

	// 플레이어 미사일 <-> 적

	// 적 미사일 <-> 플레이어 미사일

	//적<->타일
	for (int j = 0; j < TILE_X * TILE_Y; j++)
	{
		HitBox();
		for (int i = 0; i < enemyMgr->GetIsEnemyCount(); i++)
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
	//플레이어<->타일
	if (playerShip)
	{
		if (playerShip->GetIsAlive())
		{
			for (int i = 0; i < sizeof(TileInfo) / sizeof(TILE_INFO); i++)
			{
				if (IntersectRect(&dummyRc, &playerHitRc, &(TileInfo[i].rcTile)))
				{
					switch (TileInfo[i].tileType)
					{
					case TileType::BLACK:
						break;
					case TileType::BUSH:
						break;
					
						
					case TileType::ICE:
						break;
					
						
					case TileType::NORMAL:case TileType::RIVER:case TileType::IRON:case TileType::EAGLE:
						
						switch (playerShip->GetMoveStat())
						{
							//플레이어가 오른쪽에서
						case 0:
							playerShip->SetPos({ float(TileInfo[i].rcTile.right+ playerShip->GetSize()/2 ),playerShip->GetPos().y });
							break;
							//플레이어가 아래쪽에서
						case 1:
							playerShip->SetPos({  playerShip->GetPos().x,float(TileInfo[i].rcTile.bottom + playerShip->GetSize() / 2)});
							break;
							//플레이어가 왼쪽에서
						case 2:
							playerShip->SetPos({ float(TileInfo[i].rcTile.left - playerShip->GetSize()/2 ),playerShip->GetPos().y });
							break;
							//플레이어가 위쪽에서
						case 3:
							playerShip->SetPos({playerShip->GetPos().x ,float(TileInfo[i].rcTile.top - playerShip->GetSize() / 2 )});
							break;
						}
						
						
					
						break;
					}
				}
			}
		}
	}
	RECT MissileRC = {};
	MissileRC = playerShip->GetMissileShape(0);
	//플레이어미사일<->적
	if (enemyMgr)
	{
		for (int i = 0; i < enemyMgr->GetIsEnemyCount(); i++)
		{
			if (vEnemys[i]->GetIsAlive()) 
			{
				if (IntersectRect(&dummyRc, &vEnemys[i]->hitRc, &MissileRC))
				{
					playerShip->MissileDead(0);
					vEnemys[i]->Dead();
					enemyMgr->Dead();
				}
				
			}
			
		}
	}
	MissileRC = playerShip->GetMissileShape(0);
	for (int i = 0; i < sizeof(TileInfo) / sizeof(TILE_INFO); i++)
	{
		if (IntersectRect(&dummyRc, &MissileRC, &(TileInfo[i].rcTile)))
		{
			switch (TileInfo[i].tileType)
			{
			case TileType::BLACK:case TileType::BUSH:case TileType::ICE:case TileType::RIVER:
				break;
			case TileType::IRON:case TileType::EAGLE:
				playerShip->MissileDead(0);
				break;

			case TileType::NORMAL:
				TileInfo[i].tileType = TileType::BLACK;
				TileInfo[i].frameY = 13;
				playerShip->MissileDead(0);
				break;
			}
		}
	}
	

	
	
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
	if (playerShip) {
		playerHitRc = playerShip->GetShape();
	}
	// enemy RECT
	if (enemyMgr) {
		vEnemys = enemyMgr->GetEnemys();
		for (int i = 0; i < 4; i++)
		{
			vEnemyHitRc.push_back(vEnemys[i]->hitRc);
		}
	}
}

void BattleScene::ItemSkill(int a)
{

}


