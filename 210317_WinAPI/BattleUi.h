#pragma once
#include "GameNode.h"

class BattleUi : public GameNode
{
private:
	Image* uiSpace;
	Image* numImage;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~BattleUi() {};
};
