#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::Init()
{
    enemyCount = 20;
    // 적 생성 20마리
    vEnemys.resize(enemyCount);
    for (int i = 0; i < enemyCount; i++)
    {
        vEnemys[i] = new Enemy();
        vEnemys[i]->Init(-100, -100);
    }

    vEnemyGenPos.push_back({ 50, 50 });
    vEnemyGenPos.push_back({ 32 * 26 / 2, 50 });
    vEnemyGenPos.push_back({ 32 * 26 - 50, 50 });

    ememyRegenCount = 0;
    posIndex = 0;
    regenTimer = 0.0f;
    iIndex = 0;
    regenEnemy = true;
    return S_OK;
}

void EnemyManager::Release()
{
    vector<Enemy*>::iterator it;
    for (it = vEnemys.begin(); it != vEnemys.end(); it++)
    {
        (*it)->Release(); 
        delete (*it);
        (*it) = nullptr;
    }

    vEnemyGenPos.clear();
}

void EnemyManager::Update()
{
    RegenEnemy();

    vector<Enemy*>::iterator it;
    for (it = vEnemys.begin(); it != vEnemys.end(); it++)
    {
        if((*it)->GetIsAlive() == true)
            (*it)->Update();
    }
}

void EnemyManager::Render(HDC hdc)
{
    vector<Enemy*>::iterator it;
    for (it = vEnemys.begin(); it != vEnemys.end(); it++)
    {
        (*it)->Render(hdc);
    }
}

void EnemyManager::RegenEnemy()
{
    if (ememyRegenCount >= 4)
    {
        regenEnemy = false;
    }
    else if (ememyRegenCount <= 3)
    {
        regenTimer += TimerManager::GetSingleton()->GetElapsedTime();
        if (regenTimer >= 2.0f)
        {
            vEnemys[iIndex]->SetPos(vEnemyGenPos[posIndex]);
            vEnemys[iIndex]->SetIsGenEffect(true);
            vEnemys[iIndex]->SetIsAlive(true);
            vEnemys[iIndex]->HitBox();
            // 히트박스 저장
            //vHitRc[ememyRegenCount] = vEnemys[iIndex]->GetHitRc();
            ememyRegenCount++;
            posIndex++;
            iIndex++;
            regenTimer = 0.0f;
            if (posIndex == 3)
            {
                posIndex = 0;
            }
        }
    }

    if (0 >= enemyCount)
    {
        regenEnemy = false;
    }
}

void EnemyManager::Dead()
{
    enemyCount -= 1;
    ememyRegenCount -= 1;
}

void EnemyManager::EnemyCollision()
{
    RECT dummyRc = { };
    for (int i = 0; i < enemyCount; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == j) continue;
            else
            {
                if (vEnemys[i]->GetIsAlive())
                {
                    if (IntersectRect(&dummyRc, &vEnemys[i]->hitRc, &vEnemys[j]->hitRc))
                    {
                        switch (vEnemys[i]->GetState())
                        {
                            // 위로 이동
                        case 0:
                            vEnemys[i]->SetPos({ vEnemys[i]->GetPos().x,float(vEnemys[j]->hitRc.bottom + vEnemys[i]->GetSizeH() / 2) });
                            vEnemys[i]->SetState(1);
                            break;
                        case 1:
                            vEnemys[i]->SetPos({ vEnemys[i]->GetPos().x ,float(vEnemys[j]->hitRc.top - vEnemys[i]->GetSizeH() / 2) });
                            vEnemys[i]->SetState(0);
                            break;
                        case 2:
                            vEnemys[i]->SetPos({ float(vEnemys[j]->hitRc.right + vEnemys[i]->GetSizeW() / 2),vEnemys[i]->GetPos().y });
                            vEnemys[i]->SetState(3);
                            break;
                        case 3:
                            vEnemys[i]->SetPos({ float(vEnemys[j]->hitRc.left - vEnemys[i]->GetSizeW() / 2),vEnemys[i]->GetPos().y });
                            vEnemys[i]->SetState(2);
                            break;
                        default:
                            break;
                        }
                        //vEnemys[i]->SetIsCol(true);
                    }
                }
            }
        }
    }
}

//RECT EnemyManager::GetHitRc(int count)
//{
//    for (int i = 0; i < 4; i++)
//    {
//        if (i == count) return vHitRc[i];
//    }
//}
