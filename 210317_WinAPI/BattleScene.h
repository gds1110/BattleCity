#pragma once
#include "GameNode.h"


// ���� MainGame Ŭ������ ������ �̵�
class PlayerShip;
class EnemyManager;
class Image;
class TilemapTool;
class BattleUi;
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
	EnemyManager* enemyMgr;
	PlayerShip* playerShip;
	BattleUi* battleUi;

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
};

