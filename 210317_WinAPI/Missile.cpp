#include "Missile.h"
#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"

#define EXPLOSION_MAX_FRAME 3
#define EXPLOSION_MAX_TIME 0.1

HRESULT Missile::Init()
{
	
	ImageManager::GetSingleton()->AddImage("MissileLeft",
		"Image/Bullet/Missile_Left.bmp", 12, 9, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("MissileRight",
		"Image/Bullet/Missile_Right.bmp", 12, 9, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("MissileUp",
		"Image/Bullet/Missile_Up.bmp", 9, 12, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("MissileDown",
		"Image/Bullet/Missile_Down.bmp", 9, 12, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("MissileExplosion",
		"Image/Effect/Boom_Effect.bmp", 64 * EXPLOSION_MAX_FRAME, 64, EXPLOSION_MAX_FRAME, 1, true, RGB(255, 0, 255));

	pos = {-100, -100};
	moveSpeed = 3000.0f;
	moveTime = 10.0f;
	sizeX = 9;
	sizeY = 12;
	shape = { 0, 0, 0, 0 };
	damage = 5000;
	angle = 0.0f;
	isFired = false;
	missileType = TYPE::Normal;
	fireStep = 0;
	isDying = false;
	target = nullptr;
	explosionFrame = 0;
	destAngle = 0.0f;
	imsideltaTime = 0.0f;

	// 이미지
	imgLeft = ImageManager::GetSingleton()->FindImage(	"MissileLeft");
	imgRight = ImageManager::GetSingleton()->FindImage(	"MissileRight");
	imgUp = ImageManager::GetSingleton()->FindImage(	"MissileUp");
	imgDown = ImageManager::GetSingleton()->FindImage	("MissileDown");
	imgExplosion = ImageManager::GetSingleton()->FindImage("MissileExplosion");
	if ((imgLeft == nullptr)|| (imgRight == nullptr) || (imgUp == nullptr) || (imgDown == nullptr) )
	{
		MessageBox(g_hWnd,
			"EnemyMissile에 해당하는 이미지가 추가되지 않았음!", "경고", MB_OK);
		return E_FAIL;
	}

    return S_OK;
}

void Missile::Release()
{

}

void Missile::Update()
{
	imsideltaTime =TimerManager::GetSingleton()->GetElapsedTime();
	
	if (isDying)
	{
		exlposionTimer += imsideltaTime;
		if (exlposionTimer >= EXPLOSION_MAX_TIME)
		{
			exlposionTimer -= EXPLOSION_MAX_TIME;
			++explosionFrame;
		}
	}
	// 위치 이동
	if (isFired)
	{
		switch (missileType)
		{
		case TYPE::Normal:
			MovingNormal();
			break;
		case TYPE::Skill_01:
			MovingSkill_01();
			break;
		case TYPE::FollowTarget:
			MovingFollowTarget();
			break;
		}

		if (pos.x < 0 || pos.y < 0 || pos.x > (26 * 32) || pos.y > (26 * 32))
		{
			
			if (!isDying)
			{
				isDying = true;
				exlposionTimer = 0.0f;
				explosionFrame = 0;
				explosionPos = { (long)pos.x,(long)pos.y };
			}
			isFired = false;

		}
	}
	if (((angle >= -PI / 4) && (angle < PI / 4))|| ((angle >= PI * 3 / 4) || (angle < -PI * 3 / 4)))
	{
		sizeX = 12;
		sizeY = 9;
	}
	if (((angle >= PI / 4) && (angle < PI * 3 / 4))|| ((angle < -PI / 4) && (angle >= -PI * 3 / 4)))
	{
		sizeX = 9;
		sizeY = 12;
	}
	
	

	shape.left = pos.x - sizeX / 2;
	shape.top = pos.y - sizeY / 2;
	shape.right = pos.x + sizeX / 2;
	shape.bottom = pos.y + sizeY / 2;
}

void Missile::Render(HDC hdc)
{
	if (isFired)
	{
		//미사일이 오른쪽을 볼때
		if ((angle>=-PI/4)&& (angle < PI / 4))
		{
			imgRight->Render(hdc, pos.x, pos.y, true);
		}
		//미사일이 위을 볼때
		if ((angle >= PI / 4) && (angle < PI *3/ 4))
		{
			imgUp->Render(hdc, pos.x, pos.y, true);
		}
		//미사일이 왼쪽을 볼때
		if ((angle >= PI *3/ 4) || (angle < -PI *3/ 4))
		{
			imgLeft->Render(hdc, pos.x, pos.y, true);
		}
		//미사일이 아래을 볼때
		if ((angle < -PI / 4) && (angle >= -PI*3 / 4))
		{
			imgDown->Render(hdc, pos.x, pos.y, true);
		}
		
		//Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
	if (isDying)
	{
		
		if (explosionFrame>=EXPLOSION_MAX_FRAME)
		{
			isDying = false;
		}
		else {
			imgExplosion->FrameRender(hdc, explosionPos.x, explosionPos.y, explosionFrame, 0, true);
		}
		
		
	}
}

void Missile::MovingNormal()
{
	float elapsedTime = TimerManager::GetSingleton()->GetElapsedTime();
	pos.x += cosf(angle) * moveSpeed * elapsedTime;
	pos.y -= sinf(angle) * moveSpeed * elapsedTime;
}

void Missile::MovingSkill_01()
{
	if (fireStep == 0 && pos.y < 300.0f)
	{
		angle = fireIndex * 3.14f * 2.0f / 36.0f;
		fireStep++;
	}

	pos.x += cosf(angle) * moveSpeed;
	pos.y -= sinf(angle) * moveSpeed;
}

void Missile::MovingFollowTarget()
{
	if (target)
	{
		destAngle = GetAngle(pos, target->GetPos());
		float ratio = (destAngle - angle) / 50.0f;

		if (-0.01f < ratio && ratio < 0.01f)
		{
			angle = destAngle;
		}
		else
		{
			angle += ratio;
		}
	}

	pos.x += cosf(angle) * moveSpeed;
	pos.y -= sinf(angle) * moveSpeed;
}


void Missile::SetIsFired(bool isFired)
{
	this->isFired = isFired;
}

void Missile::Dead(void)
{
	this->isDying = true;
	isFired = false;
}