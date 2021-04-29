#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::Init()
{
    enemyCount = 20;
    // 利 积己 20付府
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
}

void EnemyManager::Update()
{
    RegenEnemy();

    vector<Enemy*>::iterator it;
    for (it = vEnemys.begin(); it != vEnemys.end(); it++)
    {
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
        if (regenTimer >= 3.0f)
        {
            vEnemys[iIndex]->SetPos(vEnemyGenPos[posIndex]);
            vEnemys[iIndex]->SetIsGenEffect(true);
            ememyRegenCount++;
            posIndex++;
            iIndex++;
            regenTimer = 0.0f;
            if (posIndex > 2)
            {
                posIndex = 0;
            }
        }
    }

    if (iIndex < enemyCount)
    {
        regenEnemy = false;
    }
   /* for (int i = 0; i < enemyCount; i++)
    {
        regenTimer += TimerManager::GetSingleton()->GetElapsedTime();
        if (ememyRegenCount >= 4)
        {
            break;
        }

        else
        {
            if (regenTimer >= 20.0f)
            {
                vEnemys[i]->SetPos(vEnemyGenPos[posIndex]);

                ememyRegenCount++;
                posIndex++;
                if (posIndex > 2)
                {
                    posIndex = 0;
                }
                regenTimer = 0.0f;
            }
        }       
    }*/
}
