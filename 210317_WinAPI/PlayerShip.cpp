#include "PlayerShip.h"
#include "Image.h"
#include "Missile.h"

#define SUMMON_MAX_FRAME 4
#define SUMMON_MAX_TIME 1.5
#define SUMMON_FRAME_TIME 0.1
#define DEAD_MAX_FRAME 5
#define DEAD_MAX_TIME 0.6
#define DEAD_FRAME_TIME 0.1
HRESULT PlayerShip::Init()
{
	if (image == nullptr)
	{
		image = ImageManager::GetSingleton()->AddImage("플레이어1탱크",
			"Image/Player/Player.bmp", maxFrame.x * TILESIZE*2, maxFrame.y * TILESIZE*2, maxFrame.x, maxFrame.y, true, RGB(255, 0, 255));
		if (image == nullptr)
		{
			MessageBox(g_hWnd, "플레이어1 탱크 이미지 로드 실패", "초기화 실패", MB_OK);
			return E_FAIL;
		}
	}
	if (summonImg == nullptr)
	{
		summonImg = ImageManager::GetSingleton()->AddImage("summoning",
			"Image/Effect/Spawn_Effect.bmp", SUMMON_MAX_FRAME * TILESIZE*2, TILESIZE*2, SUMMON_MAX_FRAME, 1, true, RGB(255, 0, 255));
		if (summonImg == nullptr)
		{
			MessageBox(g_hWnd, "플레이어1 탱크 소환 이미지 로드 실패", "초기화 실패", MB_OK);
			return E_FAIL;
		}
	}
	if (deadImg1 == nullptr)
	{
		deadImg1 = ImageManager::GetSingleton()->AddImage("PlayerDead1",
			"Image/Effect/Boom_Effect.bmp", 3 * TILESIZE * 2, TILESIZE * 2, 3, 1, true, RGB(255, 0, 255));
		if (deadImg1 == nullptr)
		{
			MessageBox(g_hWnd, "플레이어1 탱크 죽음1 이미지 로드 실패", "초기화 실패", MB_OK);
			return E_FAIL;
		}
	}
	if (deadImg2 == nullptr)
	{
		deadImg2 = ImageManager::GetSingleton()->AddImage("PlayerDead2",
			"Image/Effect/Big_Boom_Effect.bmp",2 * TILESIZE * 2, TILESIZE * 2, 2, 1, true, RGB(255, 0, 255));
		if (deadImg2 == nullptr)
		{
			MessageBox(g_hWnd, "플레이어1 탱크 죽음2 이미지 로드 실패", "초기화 실패", MB_OK);
			return E_FAIL;
		}
	}
	summonTimer = 0;
	summonFrame = 0;
	totalSummonTimer = 0;
	deadTimer = 0;
	deadFrame = 0;
	totalDeadTimer = 0;
	movestat = MoveInfo::STOP;
	renderStat = RenderInfo::TOP;
	isSummon = false;
	shape={};


	

	barrelEnd = { pos.x,pos.y - TILESIZE*2 / 2 };
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
	
	switch (SceneManager::GetSingleton()->currStage)
	{
	case 1:
		summonPos = { TILESIZE * 8,TILESIZE * 24 };
		this->life = 3;
		break;
	case 2:
		summonPos = { TILESIZE * 16,TILESIZE * 10 };
		break;
	case 3:
		summonPos = { TILESIZE * 20,TILESIZE * 24};
		break;
	}
	SetPos(summonPos);
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
	missile = nullptr;
}

void PlayerShip::Update()
{
	if (HP<=0)
	{
		isAlive = false;
		if (!isDying)
		{
			isDying = true;
			isAlive = false;
		}
		
	}
	if(isAlive)//실제 작동부
	{
		if (!isSummon)
		{
			movestat = MoveInfo::STOP;
			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
			{
				if ((movestat == MoveInfo::STOP) || (movestat == MoveInfo::TOP))
				{
					movestat = MoveInfo::TOP;
					outputMove = 1;
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
					outputMove = 3;
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
					outputMove = 0;
					renderStat = RenderInfo::LEFT;
					barrelEnd = { pos.x - size / 2,pos.y };
					barrelAngle = PI;
				}
			}
			else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
			{
				if ((movestat == MoveInfo::STOP) || (movestat == MoveInfo::RIGHT))
				{
					movestat = MoveInfo::RIGHT;
					renderStat = RenderInfo::RIGHT;
					outputMove = 2;
					barrelEnd = { pos.x + size / 2,pos.y };
					barrelAngle = 0;
				}
			}
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
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
			if (shape.left < 0)
			{
				pos.x = 0 + size / 2;
			}
			if (shape.top < 0)
			{
				pos.y = 0 + size / 2;
			}
			if (shape.right > TILE_X*TILESIZE)
			{
				pos.x = TILE_X * TILESIZE - size / 2;
			}
			if (shape.bottom > TILE_Y * TILESIZE)
			{
				pos.y = TILE_Y * TILESIZE - size / 2;
			}
		}
		else //소환중
		{
			summonTimer += TimerManager::GetSingleton()->GetElapsedTime();
			totalSummonTimer += TimerManager::GetSingleton()->GetElapsedTime();
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
		shape = { (long)pos.x - size / 2,(long)pos.y - size / 2 ,(long)pos.x + size / 2 ,(long)pos.y + size / 2 };
	}
	if (isDying)
	{
		deadTimer += TimerManager::GetSingleton()->GetElapsedTime();
		totalDeadTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (deadTimer >= DEAD_FRAME_TIME)
		{
			deadTimer -= DEAD_FRAME_TIME;
			++deadFrame;
		}
		if (deadFrame >= DEAD_MAX_FRAME)
		{
			deadFrame = 0;
		}
		if (totalDeadTimer >= DEAD_MAX_TIME)
		{
			isDying = false;
		}

	}
	for (int i = 0; i < sizeof(*missile) / sizeof(Missile); i++)
	{
		missile[i].Update();
	}
}

void PlayerShip::Render(HDC hdc)
{
	Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
	if (!isSummon&&isAlive)
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
	else if(isSummon)
	{
		summonImg->FrameRender(hdc, pos.x, pos.y, summonFrame, 0, true);
	}
	if (isDying)
	{
		if (deadFrame < 3) 
		{
			deadImg1->FrameRender(hdc, deadPos.x, deadPos.y, deadFrame, 0, true);
		}
		else
		{
			deadImg2->FrameRender(hdc, deadPos.x, deadPos.y, deadFrame-3, 0, true);
		}
	}
	if (missile) 
	{
		
		for (int i = 0; i < sizeof(*missile) / sizeof(Missile); i++)
		{
			if(missile[i].GetIsInited())
			missile[i].Render(hdc);
		}
	}
	
}

void PlayerShip::OnDead()
{
	isDying = true;
	isAlive = false;
	deadFrame = 0;
	deadTimer = 0;
	totalDeadTimer = 0;
	deadPos = pos;
	--life;
	if (life >= 0)
	{
		SetPos(summonPos);
		Appear();
	}
}
void PlayerShip::MissileDead(int index)
{
	if (missile)
	{
		missile[index].Dead();
	}
}
RECT PlayerShip::GetMissileShape(int index)
{
	if (missile)
	{
		if (missile[index].GetIsFired()) 
		{
			return missile[index].GetShape();
		}
	}
	return {NULL,NULL ,NULL ,NULL };
}
void PlayerShip::PlayerSave()
{
	string fileName = "Player/playerData";
	fileName += ".Player";
	DWORD writtenBytes;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, &life, sizeof(int), &writtenBytes, NULL);
	CloseHandle(hFile);
}
void PlayerShip::PlayerLoad()
{
	string fileName = "Player/playerData";
	fileName += ".Player";
	DWORD readBytes;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (ReadFile(hFile, &life, sizeof(int), &readBytes, NULL))
	{
		SetLife(life);
	}
	else
	{
		MessageBox(g_hWnd, "세이브로드실패", "error", MB_OK);
	}
	CloseHandle(hFile);
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
