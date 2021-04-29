#pragma once
#include "GameNode.h"
class Image;
class Button;
class ScoreScene : public GameNode
{
private:
	Image* ScoreImg;
	Image* numImage;
	
	int enemyType_1p[4] = { 0 };
	int enemyType_2p[4] = { 0 };

	int totalPoint=0;

	int point_1p[4] = { 0 };
	int point_2p[4] = { 0 };

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

};
