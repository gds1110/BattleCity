#pragma once
#include "GameNode.h"
#include "Timer.h"

// 기존 MainGame 클래스의 내용을 이동
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
	// 메인타일의 정보
	TILE_INFO TileInfo[TILE_X * TILE_Y];
	RECT rcMain;
	Image* sampleTile;
	Image* bin;
	Image* uiSpace;
	Image* numImage;
	Image* gameOver;
	POINT overPos;

	ItemManager* itemMgr;
	EnemyManager* enemyMgr;
	PlayerShip* playerShip;
	BattleUi* battleUi;

	bool gameOn;

	float itemTimer;

	//이전좌표정보
	FPOINT prevPlPos;
	FPOINT prevEnPos[20];

	Item* item;
	// hitBox
	//vector<RECT> vEnemyHitRc;
	map<int, RECT> mEnemyHitRc;
	vector<Enemy*> vEnemys;
	RECT playerHitRc;
	vector<RECT> enemyMissileRc;
	bool initCheck;
	int enemyFieldcount;

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


};

