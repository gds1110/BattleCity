#pragma once
#include "GameNode.h"
// 샘플 타일 정보
#define SAMPLE_TILE_X	11
#define SAMPLE_TILE_Y	14
#define TILESIZE		32


// 메인 그리기 공간 정보
#define	TILE_X			26
#define	TILE_Y			26




// 기존 MainGame 클래스의 내용을 이동
class PlayerShip;

class EnemyManager;
class Image;
class TilemapTool;
class BattleScene : public GameNode
{
private:
	// 메인타일의 정보
	TILE_INFO TileInfo[TILE_X * TILE_Y];
	RECT rcMain;
	Image* sampleTile;
	Image* bin;
	EnemyManager* enemyMgr;
	PlayerShip* playerShip;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void StageLoad(int stageNum);

	void CheckCollision();

	virtual ~BattleScene() {};
};

