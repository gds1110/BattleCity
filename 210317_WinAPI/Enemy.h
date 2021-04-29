#pragma once
#include "GameNode.h"

class Image;
class Missile;
class Enemy : public GameNode
{
public:
	enum Moving { UP, DOWN, LEFT, RIGHT, END };
private:
	// 기본 정보
	Image* image;
	int currFrameX;
	FPOINT pos;
	int size;
	RECT hitRc;
	float moveSpeed;
	bool isAlive;

	// 미사일 관련 변수
	Missile* missile;
	int dir;

	// 등장 이펙트
	Image* regenEffectImg;
	int updateCount;
	int genEffectCurrFrameX;
	bool isGenEffect;

	// 움직임 관련 변수
	int state;

public:
	HRESULT Init(int posX = 0, int posY = 0);		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void Move();
	void Dead();
	void IsFired();
	void EffectFrame();

	// get, set
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	inline int GetSize() { return this->size; }
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return this->isAlive; }

};

