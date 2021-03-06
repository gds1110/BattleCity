#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;
class EnemyManager : public GameNode
{
private:
	vector<Enemy*> vEnemys;
	vector<FPOINT> vEnemyGenPos;
	int posIndex;
	int enemyCount;
	int ememyRegenCount;
	float regenTimer;
	int iIndex;
	bool regenEnemy;
	int maxFieldCount;
	//vector<RECT> vHitRc;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void RegenEnemy();
	void Dead(int index);
	void EnemyCollision();
	// get, set
	inline void SetIsEnemyCount(int enemyCount) { this->enemyCount = enemyCount; }
	inline int GetIsEnemyCount() { return this->enemyCount; }
	inline vector<Enemy*> GetEnemys() { return this->vEnemys; }
	//RECT GetHitRc(int count);
	inline int GetRegenEnemyCount() { return this->ememyRegenCount; }
	inline void miE1() { if (enemyCount > 0)enemyCount -= 1; }
	inline void miE2() { if (ememyRegenCount > 0)ememyRegenCount-=1; }
};

