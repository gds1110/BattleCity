#pragma once
#include "GameNode.h"

// ���� Ÿ�� ����
#define SAMPLE_TILE_X	11
#define SAMPLE_TILE_Y	11
#define TILESIZE		32

// ���� �׸��� ���� ����
#define	TILE_X			26
#define	TILE_Y			26

typedef struct tagTile
{
	RECT rcTile;
	int frameX;
	int frameY;
} TILE_INFO;

class Image;
class TilemapTool : public GameNode
{
private:
	// ���� Ÿ�� �̹���
	Image* sampleTile;
	TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT rcSample;

	// ����Ÿ���� ����
	TILE_INFO tileInfo[TILE_X * TILE_Y];
	RECT rcMain;

	POINT ptStartSelectedFrame;
	POINT ptEndSelectedFrame;

	POINT ptSelected[2];
	HBRUSH hSelectedBrush;
	HBRUSH hOldSelectedBrush;

	//int selectedFrameX;
	//int selectedFrameY;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~TilemapTool() {};
};

