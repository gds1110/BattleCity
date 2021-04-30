#pragma once
#include "GameNode.h"




// ���� MainGame Ŭ������ ������ �̵�
class PlayerShip;
class EnemyManager;
class Image;
class TilemapTool;
class BattleUi;
class Item;
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


	Item* item;
	// hitBox
	//vector<RECT> vEnemyHitRc;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void StageLoad(int stageNum);

	void CheckCollision();

	virtual ~BattleScene() {};
};

