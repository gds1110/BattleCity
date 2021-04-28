#pragma once
#include "GameNode.h"
// ���� Ÿ�� ����
#define SAMPLE_TILE_X	11
#define SAMPLE_TILE_Y	14
#define TILESIZE		32


// ���� �׸��� ���� ����
#define	TILE_X			26
#define	TILE_Y			26




// ���� MainGame Ŭ������ ������ �̵�
class PlayerShip;

class EnemyManager;
class Image;
class TilemapTool;
class BattleScene : public GameNode
{
private:
	// ����Ÿ���� ����
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

