#include "PlayerShip.h"
#include "Image.h"
#include "Missile.h"

#define SUMMON_MAX_FRAME 4
#define SUMMON_MAX_TIME 1.5
#define SUMMON_FRAME_TIME 0.1
HRESULT PlayerShip::Init()
{
	if (image == nullptr)
	{
		image = ImageManager::GetSingleton()->AddImage("플레이어1탱크",
			"Image/Player/Player.bmp", maxFrame.x * size, maxFrame.y * size, maxFrame.x, maxFrame.y, true, RGB(255, 0, 255));
		if (image == nullptr)
		{
			MessageBox(g_hWnd, "플레이어1 탱크 이미지 로드 실패", "초기화 실패", MB_OK);
			return E_FAIL;
		}
	}
	if (summonImg == nullptr)
	{
		summonImg = ImageManager::GetSingleton()->AddImage("summoning",
			"Image/Effect/Spawn_Effect.bmp", SUMMON_MAX_FRAME * size,size, SUMMON_MAX_FRAME, 1, true, RGB(255, 0, 255));
		if (summonImg == nullptr)
		{
			MessageBox(g_hWnd, "플레이어1 탱크 소환 이미지 로드 실패", "초기화 실패", MB_OK);
			return E_FAIL;
		}
	}
	summonTimer = 0;
	summonFrame = 0;
	totalSummonTimer = 0;
	movestat = MoveInfo::STOP;
	renderStat = RenderInfo::TOP;
	isSummon = false;
	
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y / 2;

	barrelEnd = { pos.x,pos.y - size / 2 };
	barrelAngle = PI / 2;
	moveSpeed = 150.0f;

	missileCount = 1;
	if (missile == nullptr)
	{
		missile = new Missile[missileCount];
		for (int i = 0; i < missileCount; i++)
		{
			missile[i].Init();
		}
	}
	

	isAlive = true;
	isDying = false;
	Appear();
	return S_OK;
}

void PlayerShip::Release()
{
	for (int i = 0; i < sizeof(*missile)/sizeof(Missile); i++)
	{
		missile[i].Release();
	}
	delete[] missile;
}

void PlayerShip::Update()
{
	if (isAlive && KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		isAlive = false;
		if (!isDying)
		{
			isDying = true;
		}
		
	}
	if (HP<=0)
	{
		isAlive = false;
		if (!isDying)
		{
			isDying = true;
		}
		
	}
	if (isDying)
	{
		OnDead();
	}
	else if(!isSummon&& isAlive)//실제 작동부
	{
		movestat = MoveInfo::STOP;
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
		{
			if ((movestat == MoveInfo::STOP) || (movestat == MoveInfo::TOP)) 
			{
				movestat = MoveInfo::TOP;
				renderStat = RenderInfo::TOP;
				barrelEnd = { pos.x,pos.y - size / 2 };
				barrelAngle = PI / 2;
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
		{
			if ((movestat == MoveInfo::STOP) || (movestat == MoveInfo::BOTTOM))
			{
				movestat = MoveInfo::BOTTOM;
				renderStat = RenderInfo::BOTTOM;
				barrelEnd = { pos.x,pos.y + size / 2 };
				barrelAngle = -PI / 2;
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			if ((movestat == MoveInfo::STOP) || (movestat == MoveInfo::LEFT))
			{
				movestat = MoveInfo::LEFT;
				renderStat = RenderInfo::LEFT;
				barrelEnd = { pos.x - size / 2,pos.y  };
				barrelAngle = PI;
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			if ((movestat == MoveInfo::STOP) || (movestat == MoveInfo::RIGHT))
			{
				movestat = MoveInfo::RIGHT;
				renderStat = RenderInfo::RIGHT;
				barrelEnd = { pos.x + size / 2,pos.y };
				barrelAngle =0;
			}
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_SPACE))
		{
			Fire();
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
	else //소환중
	{
		summonTimer+= TimerManager::GetSingleton()->GetElapsedTime();
		totalSummonTimer+= TimerManager::GetSingleton()->GetElapsedTime();
		if (summonTimer >= SUMMON_FRAME_TIME)
		{
			summonTimer -= SUMMON_FRAME_TIME;
			++summonFrame;
		}
		if (summonFrame >= SUMMON_MAX_FRAME)
		{
			summonFrame = 0;
		}
		if (totalSummonTimer >= SUMMON_MAX_TIME)
		{
			isSummon = false;
		}

	}
	for (int i = 0; i < sizeof(*missile) / sizeof(Missile); i++)
	{
		missile[i].Update();
	}
}

void PlayerShip::Render(HDC hdc)
{
	if (!isSummon)
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
			image->FrameRender(hdc, pos.x, pos.y, stateFrameX + frameX, frameY, true);
			//image->Render(hdc, pos.x, pos.y);
		}
	}
	else
	{
		summonImg->FrameRender(hdc, pos.x, pos.y, summonFrame, 0, true);
	}
	if (missile) 
	{
		for (int i = 0; i < sizeof(*missile) / sizeof(Missile); i++)
		{
			missile[i].Render(hdc);
		}
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
void PlayerShip::Fire()
{
	// 미사일 발사
	// 상태만 변경
	for (int i = 0; i < missileCount; i++)
	{
		if (missile[i].GetIsFired() == false)
		{
			missile[i].SetType(Missile::TYPE::Normal);
			missile[i].SetPos(barrelEnd);
			missile[i].SetIsFired(true);
			missile[i].SetAngle(barrelAngle);

			break;
		}
	}
}

void PlayerShip::Appear(void)
{
	isSummon = true;
	isAlive = true;
	HP = 1;
	summonFrame = 0;
	summonTimer = 0;
	totalSummonTimer = 0;
}
