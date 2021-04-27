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

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void OnDead();
};

