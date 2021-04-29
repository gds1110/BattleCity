#include "BattleUi.h"
#include "CommonFunction.h"
#include "Image.h"

HRESULT BattleUi::Init()
{

	uiSpace = ImageManager::GetSingleton()->AddImage(
		"유아이", "Image/UIspace2.bmp", UISPACE_X,
		TILESIZE * TILE_Y, true, RGB(255, 0, 255));

	numImage = ImageManager::GetSingleton()->AddImage(
		"숫자이미지", "Image/Number_w.bmp", 240,
		84, 5, 2, true, RGB(255, 0, 255));

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
	for (int i = 0; i < 19; i++)
	{
		RenderRectToCenter(hdc, (TILE_X * TILESIZE + 65) + (30 * (i % 2)), 100 + 30 * (i / 2), 30, 30);
	}
	//numImage->Render(hdc, 500, 500);
	numImage->FrameRender(hdc,
		500,
		500,
		8%5,
		8/5,
		false);
}
