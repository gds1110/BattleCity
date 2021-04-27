#include "PlayerShip.h"
#include "Image.h"

HRESULT PlayerShip::Init()
{
	image = ImageManager::GetSingleton()->AddImage("플레이어 우주선",
		"Image/rocket.bmp", 52, 64, true, RGB(255, 0, 255));

	if (image == nullptr)
	{
		MessageBox(g_hWnd, "플레이어 우주선 이미지 로드 실패", "초기화 실패", MB_OK);
		return E_FAIL;
	}

	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y / 2;

	moveSpeed = 150.0f;

	isAlive = true;
	isDying = false;

	return S_OK;
}

void PlayerShip::Release()
{
}

void PlayerShip::Update()
{
	if (isAlive && KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		isAlive = false;
		isDying = true;
	}

	if (isDying)
	{
		OnDead();
	}
	else
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		}

		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
		{
			pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
		{
			pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		}
	}

}

void PlayerShip::Render(HDC hdc)
{
	if (image)
	{
		image->AlphaRender(hdc, pos.x, pos.y, true);
		//image->Render(hdc, pos.x, pos.y, true);
	}
}

void PlayerShip::OnDead()
{
	if (image)
	{
		BLENDFUNCTION* blendFunc = image->GetBlendFunc();

		if (blendFunc->SourceConstantAlpha > 120)
		//if (blendFunc->SourceConstantAlpha < 255)
		{
			blendFunc->SourceConstantAlpha--;
		}
		else
		{
			isDying = false;
			isAlive = false;
		}
	}
}
