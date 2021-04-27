#include "PlayerShip.h"
#include "Image.h"

HRESULT PlayerShip::Init()
{
	image = ImageManager::GetSingleton()->AddImage("�÷��̾�1��ũ",
		"Image/Player/Player.bmp", maxFrame.x*size, maxFrame.y * size, maxFrame.x, maxFrame.y, true, RGB(255, 0, 255));

	if (image == nullptr)
	{
		MessageBox(g_hWnd, "�÷��̾�1 ��ũ �̹��� �ε� ����", "�ʱ�ȭ ����", MB_OK);
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
		/*image->AlphaRender(hdc, pos.x, pos.y, true);*/
		image->FrameRender(hdc, pos.x, pos.y, frameX, frameY);
		//image->Render(hdc, pos.x, pos.y);
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
