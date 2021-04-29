#pragma once
#include "GameNode.h"
class Image;
class Button;
class ScoreScene : public GameNode
{
private:
	Image* ScoreImg;
	Image* numImage;


public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

};
