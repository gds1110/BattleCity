#pragma once
#include "GameNode.h"
#include "Timer.h"

// ���� MainGame Ŭ������ ������ �̵�
class PlayerShip;
class EnemyManager;
class Image;
class TilemapTool;
class BattleUi;
class Item;
class ItemManager;
class Enemy;
class BattleScene : public GameNode
{
private:
	// ����Ÿ���� ����
	TILE_INFO TileInfo[TILE_X * TILE_Y];
	RECT rcMain;
	Image* sampleTile;
	Image* bin;
	Image* uiSpace;
	Image* numImage;
	ItemManager* itemMgr;
	EnemyManager* enemyMgr;
	PlayerShip* playerShip;
	BattleUi* battleUi;

	float itemTimer;

	//������ǥ����
	FPOINT prevPlPos;
	FPOINT prevEnPos[20];

	Item* item;
	// hitBox
	vector<RECT> vEnemyHitRc;
	vector<Enemy*> vEnemys;
	RECT playerHitRc;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void StageLoad(int stageNum);

	void CheckCollision();
	void HitBox();

	virtual ~BattleScene() {};

	void ItemSkill(int a);

	void Save(void);
	void Load(void);
};

