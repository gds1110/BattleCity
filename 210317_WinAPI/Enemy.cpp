#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "Image.h"
#include "MissileManager.h"
#include "Missile.h"

HRESULT Enemy::Init(int posX, int posY)
{
    // 이미지
    image = ImageManager::GetSingleton()->AddImage("Enemy", "Image/Enemy/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
    if (image == nullptr)
    {
        MessageBox(g_hWnd, 
            "Enemy에 해당하는 이미지가 추가되지 않았음!", "경고", MB_OK);
        return E_FAIL;
    }

    regenEffectImg = ImageManager::GetSingleton()->AddImage("RegenEffect", "Image/Effect/Spawn_Effect.bmp",
        64 * 4, 16 * 4, 4, 1, true, RGB(255, 0, 255));
    if (regenEffectImg == nullptr)
    {
        MessageBox(g_hWnd,
            "effect에 해당하는 이미지가 추가되지 않았음!", "경고", MB_OK);
        return E_FAIL;
    }
    currFrameX = 5;

    // 이펙트
    updateCount = 0;
    genEffectCurrFrameX = 0;
    isGenEffect = false;
    effectCount = 0;

    // 기본 정보
    pos.x =  posX;
    pos.y = posY;
    size = 80;
    hitRc = { 0, 0, 0, 0 };
    moveSpeed = 100.0f;
    isAlive = true;

    // 움직임
    state = 1;

    // 미사일
    missile = new Missile();
    missile->Init();
    dir = -90;

    return S_OK;
}

void Enemy::Release()
{
    SAFE_RELEASE(missile);
}

void Enemy::Update()
{
    if (isAlive)
    {
        if (isGenEffect)    EffectFrame();

        else
        {
            Move();
            Direction();

            // 미사일 발사
            if (missile)
            {
                IsFired();
                missile->Update();
            }
        }
    }
}

void Enemy::Render(HDC hdc)
{
    if (isAlive)
    {
        //RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);
        if (isGenEffect)
        {
            if (regenEffectImg)    regenEffectImg->FrameRender(hdc, pos.x, pos.y, genEffectCurrFrameX, 0, true);
        }
        else
        {
            if (image)  image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);

            if (missile)    missile->Render(hdc);
        }
    }
}

void Enemy::Move()
{
    float elapsedTime = TimerManager::GetSingleton()->GetElapsedTime();
    switch (state)
    {
    case UP:
        currFrameX = 1;
        pos.y -= moveSpeed * elapsedTime;
        dir = 90;
        break;
    case DOWN:
        currFrameX = 5;
        pos.y += moveSpeed * elapsedTime;
        dir = -90;
        break;
    case LEFT:
        currFrameX = 3;
        pos.x -= moveSpeed * elapsedTime;
        dir = 180;
        break;
    case RIGHT:
        currFrameX = 7;
        pos.x += moveSpeed * elapsedTime;
        dir = 0;
        break;
    }
}

void Enemy::Direction()
{
    srand(time(NULL));
    switch (state)
    {
    case UP:
        if (pos.y <= 0 /*&&*/)
        {
            state = rand() % 2 + 2;
        }
        break;
    case DOWN:
        if (pos.y >= TILESIZE * TILE_Y /*&&*/)
        {
            state = rand() % 2 + 2;
        }
        break;
    case LEFT:
        if (pos.x <= 0 /*&&*/)
        {
            state = rand() % 2;
        }
        break;
    case RIGHT:
        if (pos.x >= TILE_X * TILESIZE + UISPACE_X /*&&*/)
        {
            state = rand() % 2;
        }
        break;
    }



}

void Enemy::Dead()
{
    isAlive = false;
}

void Enemy::IsFired()
{
    if (missile->GetIsFired() == false)
    {
        missile->SetIsFired(true);
        missile->SetAngle(DegToRad(dir));
        missile->SetPos(pos);
    }
}

void Enemy::EffectFrame()
{
    updateCount++;
    if (updateCount == 20)
    {
        genEffectCurrFrameX++;
        if (genEffectCurrFrameX >= 4)
        {
            effectCount++;
            genEffectCurrFrameX = 0;
            if (effectCount >= 4)   isGenEffect = false;

        }
        updateCount = 0;
    }

}


