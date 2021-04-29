#pragma once
#include "GameNode.h"

class Image;
class Missile;
class Enemy : public GameNode
{
public:
	enum Moving { UP, DOWN, LEFT, RIGHT, END };
private:
	// �⺻ ����
	Image* image;
	int currFrameX;
	FPOINT pos;
	int size;
	RECT hitRc;
	float moveSpeed;
	bool isAlive;

	// �̻��� ���� ����
	Missile* missile;
	int dir;

	// ���� ����Ʈ
	Image* regenEffectImg;
	int updateCount;
	int genEffectCurrFrameX;
	bool isGenEffect;

	// ������ ���� ����
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

