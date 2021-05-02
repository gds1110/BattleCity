#pragma once
#include "GameNode.h"
class Image;
class Item: public GameNode
{
public:
	enum ITEMTYPE
	{
		SHILED,
		TIME,
		IRONWALL,
		STAR,
		BOOM,
		TANK,
		MISSILE,
		NONE
	};

private:
	Image* itemImg;
	int itemType;
	POINT pos;
	bool isDrop;
	RECT itemRc;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetRC(POINT pos);
	RECT GetRc() { return this->itemRc; }

	inline void SetType(int type) { this->itemType = type; }
	inline int GetType() { return this->itemType; }

	inline void SetPos(POINT pos) { this->pos = pos; }
	inline POINT getPos() { return this->pos; }

	inline void SetDrop(bool drop) { this->isDrop = drop; }
	inline bool GetDrop() { return this->isDrop; }
};

