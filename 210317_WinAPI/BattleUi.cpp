#include "BattleUi.h"
#include "CommonFunction.h"
#include "Image.h"

HRESULT BattleUi::Init()
{

	uiSpace = ImageManager::GetSingleton()->AddImage(
		"유아이", "Image/UIspace2.bmp", UISPACE_X,
		TILESIZE * TILE_Y, true, RGB(255, 0, 255));
	enemyIcon = ImageManager::GetSingleton()->AddImage(
		"적아이콘", "Image/Icon_Enemy.bmp", 30,
		30, true, RGB(255, 0, 255));

	numImage = ImageManager::GetSingleton()->AddImage(
		"숫자이미지", "Image/Number_w.bmp", 160,
		56, 5, 2, true, RGB(255, 0, 255));

	return S_OK;
}

void BattleUi::Release()
{

}

void BattleUi::Update()
{
}

void BattleUi::Render(HDC hdc)
{
	if (uiSpace)
	{
		uiSpace->Render(hdc, TILE_X * TILESIZE, 0);
	}

	//남은 생성될 에너미 수만큼의 아이콘
	for (int i = 0; i < 20; i++)
	{
		enemyIcon->Render(hdc, (TILE_X * TILESIZE + 60) + (30 * (i % 2)), 50 + 30 * (i / 2),true);
		/*RenderRectToCenter(hdc, (TILE_X * TILESIZE + 65) + (30 * (i % 2)), 100 + 30 * (i / 2), 30, 30);*/
	}
	//numImage->Render(hdc, 500, 500);

	//1p life
	numImage->FrameRender(hdc,
		(TILE_X * TILESIZE + 80),
		500,
		1%5,
		1/5,
		false);

	//2p life 
	numImage->FrameRender(hdc,
		(TILE_X * TILESIZE + 80),
		585,
		1 % 5,
		1 / 5,
		false);
	//Stage
	numImage->FrameRender(hdc,
		(TILE_X * TILESIZE + 60),
		760,
		SceneManager::GetSingleton()->currStage % 5,
		SceneManager::GetSingleton()->currStage / 5,
		false);
}

void BattleUi::Render2(HDC hdc, int hp, int eCount)
{
	if (uiSpace)
	{
		uiSpace->Render(hdc, TILE_X * TILESIZE, 0);
	}

	//남은 생성될 에너미 수만큼의 아이콘
	for (int i = 0; i < eCount; i++)
	{
		enemyIcon->Render(hdc, (TILE_X * TILESIZE + 60) + (30 * (i % 2)), 50 + 30 * (i / 2), true);
		/*RenderRectToCenter(hdc, (TILE_X * TILESIZE + 65) + (30 * (i % 2)), 100 + 30 * (i / 2), 30, 30);*/
	}
	//numImage->Render(hdc, 500, 500);

	//1p life
	numImage->FrameRender(hdc,
		(TILE_X * TILESIZE + 80),
		500,
		hp % 5,
		hp / 5,
		false);

	//2p life 
	numImage->FrameRender(hdc,
		(TILE_X * TILESIZE + 80),
		585,
		1 % 5,
		1 / 5,
		false);
	//Stage
	numImage->FrameRender(hdc,
		(TILE_X * TILESIZE + 60),
		760,
		SceneManager::GetSingleton()->currStage % 5,
		SceneManager::GetSingleton()->currStage / 5,
		false);
}
