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

class PlayerShip : public GameNode
{
private:
	Image* image;
	FPOINT pos;
	float moveSpeed;	// 초당 이동거리
	bool isDying;
	bool isAlive;
	int size = 64;
	int stateFrameX = 0;
	int stateFrameY = 0;
	int frameX = 0;
	int frameY = 0;
	POINT maxFrame = {8,4};
	MoveInfo movestat;
	RenderInfo renderStat;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void OnDead();
};

