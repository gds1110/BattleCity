#include "Item.h"
#include "Image.h"
#include "config.h"

HRESULT Item::Init()
{
    itemImg= ImageManager::GetSingleton()->AddImage("아이템이미지",
        "Image/ItemImage.bmp", 462,66,7,1, true, RGB(255, 0, 255));
    itemType = ITEMTYPE::SHILED;
    pos = { 0 };
    isDrop = false;
    return S_OK;
}

void Item::Release()
{

}

void Item::Update()
{
    if (isDrop == true) {
        SetRC(pos);
    }

}

void Item::Render(HDC hdc)
{
    //itemImg->Render(hdc,500,500);
   //  Rectangle(hdc, itemRc.left, itemRc.top, itemRc.right, itemRc.bottom);
     itemImg->FrameRender(hdc, pos.x, pos.y, itemType % 7, 0, true);
}

 void Item::SetRC(POINT pos)
{
    SetRect(&itemRc,  pos.x - itemImg->GetFrameWidth()/2+10,
        pos.y - itemImg->GetFrameHeight()/2+10,
        pos.x + itemImg->GetFrameWidth()/2-10,
        pos.y + itemImg->GetFrameHeight()/2-10);

}
