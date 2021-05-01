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
	inline void SetRegenEnemyCount(int ememyRegenCount) { this->ememyRegenCount = ememyRegenCount; }
	inline int GetRegenEnemyCount() { return this->ememyRegenCount; }
	inline vector<Enemy*> GetEnemys() { return this->vEnemys; }
	//RECT GetHitRc(int count);
};

