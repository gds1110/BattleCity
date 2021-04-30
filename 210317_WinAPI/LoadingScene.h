#pragma once
#include "GameNode.h"
class Image;
class LoadingScene : public GameNode
{
private:

	Image* stageScene;
	Image* blackScene;
	Image* balckNum;

	float posy_1;
	float posy_2;
	float time = 0;
	bool onStage;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

};
