#pragma once
#include "GameNode.h"
#include <vector>

class Item;
class ItemManager : public GameNode
{
private:



public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

