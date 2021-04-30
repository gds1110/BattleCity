#pragma once
#include "GameNode.h"


// 기존 MainGame 클래스의 내용을 이동
class PlayerShip;
class EnemyManager;
class Image;
class TilemapTool;
class BattleUi;
class Enemy;
class BattleScene : public GameNode
{
private:
	// 메인타일의 정보
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

