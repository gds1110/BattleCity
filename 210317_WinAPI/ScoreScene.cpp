#include "ScoreScene.h"
#include "Image.h"
HRESULT ScoreScene::Init()
{

	ScoreImg = ImageManager::GetSingleton()->AddImage(
		"½ºÄÚ¾î", "Image/ScoreSceneImage.bmp", TILE_X * TILESIZE + UISPACE_X,
		TILESIZE * TILE_Y, true, RGB(255, 0, 255));


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
}
