#include "ScoreScene.h"
#include "Image.h"
#include "CommonFunction.h"

HRESULT ScoreScene::Init()
{
	SetClientRect(g_hWnd, TILE_X * TILESIZE + UISPACE_X, TILESIZE * TILE_Y);
	ScoreImg = ImageManager::GetSingleton()->AddImage(
		"스코어", "Image/ScoreSceneImage.bmp", TILE_X * TILESIZE + UISPACE_X,
		TILESIZE * TILE_Y, true, RGB(255, 0, 255));
	numImage = ImageManager::GetSingleton()->AddImage(
		"숫자이미지", "Image/Number_w.bmp", 160,
		56, 5, 2, true, RGB(255, 0, 255));
    return S_OK;
}

void ScoreScene::Release()
{
}

void ScoreScene::Update()
{
}

void ScoreScene::Render(HDC hdc)
{
	ScoreImg->Render(hdc);

	//highScore
	numImage->Render(hdc, 600, 100, false);


	//Stage
	numImage->FrameRender(hdc,
		590,
		180,
		1 % 5,
		1 / 5,
		true);
	
	//1P
	numImage->FrameRender(hdc,
		250,
		290,
		1 % 5,
		1 / 5,
		true);
	//2P
	numImage->FrameRender(hdc,
		800,
		290,
		2 % 5,
		2 / 5,
		true);

	//1P point_1p 
	for (int i = 0; i < 4; i++)
	{
		numImage->FrameRender(hdc,
			150,
			370 + (i * 80) + 5,
			point_1p[i] % 5,
			point_1p[i] / 5,
			true);
	}

	//1P ENEMYTANK TYPE
	for (int i = 0; i < 4; i++)
	{
		numImage->FrameRender(hdc,
			390,
			370+(i*80)+5,
			enemyType_1p[i]%5,
			enemyType_1p[i] / 5,
			true);
	}


	//2P ENEMYTANK TYPE

	for (int i = 0; i < 4; i++)
	{
		numImage->FrameRender(hdc,
			600,
			370 + (i * 80) + 5,
			enemyType_2p[i] % 5,
			enemyType_2p[i] / 5,
			true);
	}
	//2P point_2p

	for (int i = 0; i < 4; i++)
	{
		numImage->FrameRender(hdc,
			750,
			370 + (i * 80) + 5,
			point_2p[i] % 5,
			point_2p[i] / 5,
			true);
	}


	numImage->FrameRender(hdc,
		500,
		700,
		totalPoint,
		totalPoint,
		true);

}
