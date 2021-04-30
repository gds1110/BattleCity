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
    temppos = pos;
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
            //Direction();

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
            Rectangle(hdc, hitRc.left, hitRc.top, hitRc.right, hitRc.bottom);
            if (image)  image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
            if (missile)    missile->Render(hdc);
        }
    }
}

void Enemy::Move()
{
    //srand(time(NULL));
    float elapsedTime = TimerManager::GetSingleton()->GetElapsedTime();
    switch (state)
    {
    case UP:
        temppos.y = pos.y - moveSpeed * elapsedTime;
        if (temppos.y < 0 + image->GetFrameHeight() / 2 /*&&*/)
        {
            /*pos.y = 0 + image->GetFrameHeight() / 2;
            pos.x = pos.x;*/
            state = rand() % 2 + 2;

        }
        currFrameX = 1;
        pos.y -= moveSpeed * elapsedTime;
        dir = 90;
        break;
    case DOWN:
        temppos.y = pos.y + moveSpeed * elapsedTime;
        dir = -90;
        if (temppos.y > TILESIZE * TILE_Y - image->GetFrameHeight() / 2 /*&&*/)
        {
            state = rand() % 2 + 2;
        }
        currFrameX = 5;
        pos.y += moveSpeed * elapsedTime;
        
        break;
    case LEFT:
        temppos.x = pos.x - moveSpeed * elapsedTime;
        if (temppos.x < 0 + image->GetFrameWidth() /*&&*/)
        {
            state = rand() % 2;
        }
        currFrameX = 3;
        pos.x -= moveSpeed * elapsedTime;
        dir = 180;
        break;
    case RIGHT:
        temppos.x = pos.x + moveSpeed * elapsedTime;
        if (temppos.x > TILE_X * TILESIZE - image->GetFrameWidth() / 2 /*&&*/)
        {
            state = rand() % 2;
        }
        currFrameX = 7;
        pos.x += moveSpeed * elapsedTime;
        dir = 0;
        break;
    }
    HitBox();
}

//void Enemy::Direction()
//{
//    float elapsedTime = TimerManager::GetSingleton()->GetElapsedTime();
//    srand(time(NULL));
//    switch (state)
//    {
//    case UP:
//        if (temppos.y < 0 + image->GetFrameHeight() / 2 /*&&*/)
//        {
//            state = rand() % 2 + 2;
//        }
//        break;
//    case DOWN:
//        if (temppos.y > TILESIZE * TILE_Y - image->GetFrameHeight() / 2 /*&&*/)
//        {
//            state = rand() % 2 + 2;
//        }
//        break;
//    case LEFT:
//        if (temppos.x < 0 + image->GetFrameWidth() /*&&*/)
//        {
//            state = rand() % 2;
//        }
//        break;
//    case RIGHT:
//        if (temppos.x > TILE_X * TILESIZE - image->GetFrameWidth() / 2 /*&&*/)
//        {
//            state = rand() % 2;
//        }
//        break;
//    }
//
//
//
//}

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

void Enemy::HitBox()
{
    hitRc.left = pos.x - image->GetFrameHeight() / 2;
    hitRc.top = pos.y - image->GetFrameWidth() / 2;
    hitRc.right = pos.x + image->GetFrameHeight() / 2;
    hitRc.bottom = pos.y + image->GetFrameWidth() / 2;
}


