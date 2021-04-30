#include "BattleScene.h"
#include "Tank.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Missile.h"
#include "Image.h"
#include "PlayerShip.h"
#include "CommonFunction.h"
#include "BattleUi.h"
#include "Item.h"
#include "ItemManager.h"

HRESULT BattleScene::Init()
{

	SetClientRect(g_hWnd, TILE_X * TILESIZE+ UISPACE_X, TILESIZE * TILE_Y);

	bin = new Image();
	bin->Init("Image/mapImage2.bmp", TILE_X * TILESIZE + UISPACE_X, TILESIZE * TILE_Y);

	// �� ����
	enemyMgr = new EnemyManager();
	enemyMgr->Init();

	playerShip = new PlayerShip();
	playerShip->Init();

	itemMgr = new ItemManager();
	itemMgr->Init();

	sampleTile = ImageManager::GetSingleton()->AddImage(
		"����Ÿ��", "Image/SamlpTile_2.bmp", SAMPLE_TILE_X * TILESIZE, SAMPLE_TILE_Y * TILESIZE,
		SAMPLE_TILE_X, SAMPLE_TILE_Y, true, RGB(0, 0, 0));


	battleUi = new BattleUi();
	battleUi->Init();

	itemTimer = 0;

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

	// �� �׸���
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
		MessageBox(g_hWnd, "���̺�ε����", "error", MB_OK);
	}
	CloseHandle(hFile);
}

void BattleScene::CheckCollision()
{
	// ��Ʈ�ڽ� �޾ƿ���
	for (int i = 0; i < 4; i++)
	{
		//vEnemyHitRc[i] = enemyMgr->GetHitRc(i);
	}
	RECT imsiRC = {};
	RECT plRC = playerShip->GetShape();
	// �� <-> ��

	// �� <-> �÷��̾�

	// �� �̻��� <-> �÷��̾�

	// �÷��̾� �̻��� <-> ��

	// �� �̻��� <-> �÷��̾� �̻���

	// ��, �÷��̾� <-> ����
	if (playerShip)
	{
		if (playerShip->GetIsAlive())
		{
			for (int i = 0; i < sizeof(TileInfo) / sizeof(TILE_INFO); i++)
			{
				if (IntersectRect(&imsiRC, &plRC, &(TileInfo[i].rcTile)))
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
							//�÷��̾ �����ʿ���
						case 0:
							playerShip->SetPos({ float(TileInfo[i].rcTile.right+ playerShip->GetSize()/2 ),playerShip->GetPos().y });
							break;
							//�÷��̾ �Ʒ��ʿ���
						case 1:
							playerShip->SetPos({  playerShip->GetPos().x,float(TileInfo[i].rcTile.bottom + playerShip->GetSize() / 2)});
							break;
							//�÷��̾ ���ʿ���
						case 2:
							playerShip->SetPos({ float(TileInfo[i].rcTile.left - playerShip->GetSize()/2 ),playerShip->GetPos().y });
							break;
							//�÷��̾ ���ʿ���
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
	
	// ��, �÷��̾� <-> ��

	// ��, �÷��̾� <-> ��ö

	// ��, �÷��̾� <-> ��

	// ��, �÷��̾� <-> ����

	// ��, �÷��̾� �̻��� <-> ����
				   
	// ��, �÷��̾� �̻��� <-> ��
				   
	// ��, �÷��̾� �̻��� <-> ��ö
				   
	// ��, �÷��̾� �̻��� <-> ��
				   
	// ��, �÷��̾� �̻��� <-> ����

	// ��, �÷��̾�, �̻��� <-> ����
	
}

void BattleScene::ItemSkill(int a)
{
}
