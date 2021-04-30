#pragma once
#include "GameNode.h"
class Image;
class Item: public GameNode
{
private:
	Image* itemImg;


public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

