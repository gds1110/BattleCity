#pragma once
#include "GameNode.h"

class Image;
class PlayerShip : public GameNode
{
private:
	Image* image;
	FPOINT pos;
	float moveSpeed;	// 초당 이동거리
	bool isDying;
	bool isAlive;
	int size = 64;
	int frameX = 1;
	int frameY = 1;
	POINT maxFrame = {8,4};

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void OnDead();
};

