#pragma once
#include "GameNode.h"

enum class ButtonState
{
	NONE, DOWN, UP
};

class Image;
class Button:public GameNode
{
private:
	ButtonState state;
	Image* image;
	RECT rc;
	POINT pos;
	void (*func_t)(void);
public:
	virtual HRESULT Init(const char* fileName,int posX,int posY);
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetFunc(void (*func_t)(void)) {this->func_t= func_t;}

	virtual ~Button() {};
};

