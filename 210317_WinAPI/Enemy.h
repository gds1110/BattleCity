#pragma once
#include "GameNode.h"

class Image;
class Missile;
class Enemy : public GameNode
{
public:
	enum Moving { UP, DOWN, LEFT, RIGHT, END };
	RECT hitRc;
private:
	// 기본 정보
	Image* image;
	int currFrameX;
	FPOINT pos;
	FPOINT tempPos;
	int sizeW;
	int sizeH;
	//RECT hitRc;
	float moveSpeed;
	bool isAlive;
	int index;
	// 미사일 관련 변수
	Missile* missile;
	int dir;

	// 등장 이펙트
	Image* regenEffectImg;
	int updateCount;
	int genEffectCurrFrameX;
	bool isGenEffect;
	int effectCount;

	char szText[128] = "";
	// 움직임 관련 변수
	int state;
	bool isCol;

public:
	HRESULT Init(int posX = 0, int posY = 0);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void Direction();
	void Dead();
	void IsFired();
	void EffectFrame();
	void HitBox();
	void CheckCollision();

	// get, set
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	inline int GetSizeW() { return this->sizeW;  }
	inline int GetSizeH() { return this->sizeH; }
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return this->isAlive; }
	inline void SetIsGenEffect(bool isGenEffect) { this->isGenEffect = isGenEffect; }
	inline RECT GetHitRc() { return this->hitRc; }
	inline int GetState() { return this->state; }
	inline void SetState(int state) { this->state = state; }
	inline void SetIsCol(bool isCol) { this->isCol = isCol; }
	inline void SetTempPos(FPOINT tempPos) { this->tempPos = tempPos; }
	inline FPOINT GetTempPos() { return this->tempPos; }
	
	inline void setindex(int a) { this->index = a; }
};

