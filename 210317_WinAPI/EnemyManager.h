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

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void RegenEnemy();
	void Dead();

	// get, set
	inline void SetIsEnemyCount(int enemyCount) { this->enemyCount = enemyCount; }
	inline int GetIsEnemyCount() { return this->enemyCount; }
};

