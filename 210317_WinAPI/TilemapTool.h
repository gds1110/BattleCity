#pragma once
#include "GameNode.h"

// 샘플 타일 정보
#define SAMPLE_TILE_X	11
#define SAMPLE_TILE_Y	14
#define TILESIZE		32

// 메인 그리기 공간 정보
#define	TILE_X			26
#define	TILE_Y			26



class Image;
class Button;
class TilemapTool : public GameNode
{
private:
	// 샘플 타일 이미지
	Image* sampleTile;
	TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT rcSample;

	// 메인타일의 정보
	RECT rcMain;

	POINT ptStartSelectedFrame;
	POINT ptEndSelectedFrame;

	POINT ptSelected[2];
	HBRUSH hSelectedBrush;
	HBRUSH hOldSelectedBrush;

	Button* btnsave;
	Button* btnload;
	Button* btnplus;
	Button* btnminu;

	static int gStageNum;

	//int selectedFrameX;
	//int selectedFrameY;

public:
	static TILE_INFO tileInfo[TILE_X * TILE_Y];
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	static void Save(void);
	static void Load(void);
	static void PlusStage(void);
	static void MinusStage(void);

	virtual ~TilemapTool() {};
};

