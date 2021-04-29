#include "TitleScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "config.h"

HRESULT TitleScene::Init()
{

	SetClientRect(g_hWnd, TILE_X * TILESIZE + UISPACE_X, TILESIZE * TILE_Y);
	titleImg= ImageManager::GetSingleton()->AddImage(
		"타이틀이미지", "Image/Title.bmp", TILE_X * TILESIZE + UISPACE_X, TILESIZE * TILE_Y);
	selIcon = ImageManager::GetSingleton()->AddImage(
		"선택아이콘", "Image/SelectIcon2.bmp", 66, 60,true,RGB(255,0,255));

	selIconPos = { 250,490 };
	SetRect(&selRc, selIconPos.x - 33,
		selIconPos.y - 30,
		selIconPos.x + 33,
		selIconPos.y + 30);

	return S_OK;
}

void TitleScene::Release()
{
}

void TitleScene::Update()
{

	SetRect(&selRc, selIconPos.x - 33,
		selIconPos.y - 30,
		selIconPos.x + 33,
		selIconPos.y + 30);


	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP)&&selIconPos.y-60>=490) 
	{
		selIconPos.y -= 60;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN) && selIconPos.y + 60 <= 550)
	{
		selIconPos.y += 60;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN) && selIconPos.y == 490) {

		SceneManager::GetSingleton()->ChangeScene("전투_1");
		//p1만
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN) && selIconPos.y == 550)
	{
		//p2도
	}
}

void TitleScene::Render(HDC hdc)
{
	titleImg->Render(hdc);
	selIcon->Render(hdc, 250, selIconPos.y, true);
	
	//Rectangle(hdc, selRc.left, selRc.top, selRc.right, selRc.bottom);
}
