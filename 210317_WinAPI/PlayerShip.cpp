#include "PlayerShip.h"
#include "Image.h"

HRESULT PlayerShip::Init()
{
	image = ImageManager::GetSingleton()->AddImage("플레이어1탱크",
		"Image/Player/Player.bmp", maxFrame.x*size, maxFrame.y * size, maxFrame.x, maxFrame.y, true, RGB(255, 0, 255));
	movestat = MoveInfo::STOP;
	renderStat = RenderInfo::TOP;
	if (image == nullptr)
	{
		MessageBox(g_hWnd, "플레이어1 탱크 이미지 로드 실패", "초기화 실패", MB_OK);
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
		movestat = MoveInfo::STOP;
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
		{
			if ((movestat == MoveInfo::STOP) || (movestat == MoveInfo::TOP)) 
			{
				movestat = MoveInfo::TOP;
				renderStat = RenderInfo::TOP;
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
		{
			if ((movestat == MoveInfo::STOP) || (movestat == MoveInfo::BOTTOM))
			{
				movestat = MoveInfo::BOTTOM;
				renderStat = RenderInfo::BOTTOM;
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			if ((movestat == MoveInfo::STOP) || (movestat == MoveInfo::LEFT))
			{
				movestat = MoveInfo::LEFT;
				renderStat = RenderInfo::LEFT;
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			if ((movestat == MoveInfo::STOP) || (movestat == MoveInfo::RIGHT))
			{
				movestat = MoveInfo::RIGHT;
				renderStat = RenderInfo::RIGHT;
			}
		}
		
		switch (movestat)
		{
		case MoveInfo::STOP:
			break;
		case MoveInfo::LEFT:
			pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
			break;
		case MoveInfo::RIGHT:
			pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
			break;
		case MoveInfo::TOP:
			pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
			break;
		case MoveInfo::BOTTOM:
			pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
			break;
		case MoveInfo::NONE:
			break;
		default:
			break;
		}
		
	}

}

void PlayerShip::Render(HDC hdc)
{
	if (image)
	{
		if (movestat != MoveInfo::STOP) 
		{
			++frameX;
			if (frameX >= 2)
			{
				frameX = 0;
			}
		}
		
		/*image->AlphaRender(hdc, pos.x, pos.y, true);*/
		switch (renderStat)
		{
		case RenderInfo::LEFT:
			stateFrameX = 2;
			break;
		case RenderInfo::RIGHT:
			stateFrameX = 6;
			break;
		case RenderInfo::TOP:
			stateFrameX = 0;
			break;
		case RenderInfo::BOTTOM:
			stateFrameX = 4;
			break;
		case RenderInfo::DEAD:
			break;
		case RenderInfo::NONE:
			break;
		default:
			break;
		}
		image->FrameRender(hdc, pos.x, pos.y, stateFrameX+ frameX, frameY);
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
