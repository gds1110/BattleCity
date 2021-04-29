#pragma once
#include "GameNode.h"
class Image;
class Button;
class TitleScene : public GameNode
{
private:
	Image* titleImg;
	Image* selIcon;

	RECT selRc;
	POINT selIconPos;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

};
