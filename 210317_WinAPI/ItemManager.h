#pragma once
#include "GameNode.h"
#include <vector>

class Item;
class ItemManager : public GameNode
{
private:
	vector<Item*> vItems;
	vector<Item*>::iterator itItem;



public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void DropItem(POINT pos,int type);
};

