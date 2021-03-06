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
	
	
	
	//상태
	bool isDying;
	bool isAlive;
	bool isSummon;

	//스탯
	int HP = 1;
	int life =3;
	int size = 48;
	int missileCount;
	float moveSpeed;	// 초당 이동거리
	FPOINT pos;

	//좌표
	FPOINT	barrelEnd;
	float	barrelAngle;
	RECT shape;
	int outputMove=10;
	FPOINT deadPos;
	FPOINT summonPos;

	//프레임+시간
	int stateFrameX = 0;
	int stateFrameY = 0;
	int frameX = 0;
	int frameY = 0;
	float	summonTimer;
	float	totalSummonTimer;
	int		summonFrame;
	float	deadTimer;
	float	totalDeadTimer;
	int		deadFrame;
	POINT maxFrame = { 8,4 };
	
	//선언
	Missile* missile;
	MoveInfo movestat;
	RenderInfo renderStat;

	//이미지
	Image* image;
	Image* summonImg;
	Image* deadImg1;
	Image* deadImg2;

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
	inline FPOINT GetPos(void) { return this->pos; }
	inline RECT GetShape(void) { return this->shape; }
	inline bool GetIsAlive(void) { return this->isAlive; }
	inline int GetMoveStat(void) { return this->outputMove; }
	inline int GetSize(void) { return this->size; }
	inline int GetLife(void) { return this->life; }
	inline void SetLife(int life) { this->life = life; }
	void MissileDead(int index);
	RECT GetMissileShape(int index);

	inline void SetHp(int hp) { this->life = hp; }
	inline int GetHp() { return this->life; }

	void PlayerSave();
	void PlayerLoad();
};

