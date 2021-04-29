#pragma once
#include "GameNode.h"

class Image;
enum class MoveInfo
{
	STOP,LEFT,RIGHT,TOP,BOTTOM,NONE
};
enum class RenderInfo
{
	LEFT, RIGHT, TOP, BOTTOM, DEAD,NONE
};
class Missile;
class PlayerShip : public GameNode
{
private:
	
	
	
	//����
	bool isDying;
	bool isAlive;
	bool isSummon;

	//����
	int HP = 1;
	int size = 64;
	int missileCount;
	float moveSpeed;	// �ʴ� �̵��Ÿ�
	FPOINT pos;

	//��ǥ
	FPOINT	barrelEnd;
	float	barrelAngle;

	//������+�ð�
	int stateFrameX = 0;
	int stateFrameY = 0;
	int frameX = 0;
	int frameY = 0;
	POINT maxFrame = { 8,4 };
	
	//����
	Missile* missile;
	MoveInfo movestat;
	RenderInfo renderStat;

	//�̹���
	Image* image;
	Image* summonImg;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire();
	void Appear(void);

	void OnDead();

	//Set, Get
	inline void SetPos(FPOINT pos) { this->pos = pos; }
};

