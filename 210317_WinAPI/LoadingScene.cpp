#include "LoadingScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "config.h"

HRESULT LoadingScene::Init()
{
	SetClientRect(g_hWnd, TILE_X * TILESIZE + UISPACE_X, TILESIZE * TILE_Y);

	stageScene = ImageManager::GetSingleton()->AddImage(
		"스테이지씬", "Image/StageScene2.bmp", TILE_X * TILESIZE + UISPACE_X, TILESIZE * TILE_Y,
		SAMPLE_TILE_X, SAMPLE_TILE_Y, true, RGB(0, 0, 0));

	blackScene = ImageManager::GetSingleton()->AddImage(
		"검은화면", "Image/mapImage.bmp", TILE_X * TILESIZE + UISPACE_X, SAMPLE_TILE_Y * TILESIZE,
		SAMPLE_TILE_X, SAMPLE_TILE_Y, true, RGB(0, 0, 0));

	balckNum= ImageManager::GetSingleton()->AddImage(
		"검은숫자이미지", "Image/Number_b.bmp", 160,
		56, 5, 2, true, RGB(99, 99, 99));

	posy_1=-TILESIZE * TILE_Y/2;
	posy_2= TILESIZE * TILE_Y;

	onStage = false;

	return S_OK;
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
	float ElapsedT = TimerManager::GetSingleton()->GetElapsedTime();
	
	if (posy_1 <= TILESIZE * TILE_Y/2)
	{
		posy_1 +=ElapsedT * 800;

	}
	if (posy_2 >= TILESIZE * TILE_Y/2)
	{
		posy_2 -= ElapsedT * 800;
	}

	if (posy_1+20>= TILESIZE * TILE_Y / 2&& posy_2-20 <= TILESIZE * TILE_Y / 2)
	{
		onStage = true;

	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		onStage = true;
	}

	if (onStage)
	{
		time += ElapsedT;
		if (time > 1.5f) {
			SceneManager::GetSingleton()->ChangeScene("전투_1");
		}
	}
}

void LoadingScene::Render(HDC hdc)
{
	blackScene->Render(hdc, 0, posy_1);
	blackScene->Render(hdc, 0, posy_2);

	if (onStage == true)
	{
		stageScene->Render(hdc, 0, 0);
		balckNum->FrameRender(hdc,
			605,
			410,
			1 % 5,
			1 / 5,
			true);
	}

}
