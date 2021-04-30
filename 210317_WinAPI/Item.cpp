#include "Item.h"
#include "Image.h"

HRESULT Item::Init()
{
    itemImg= ImageManager::GetSingleton()->AddImage("�������̹���",
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
}

void Item::Render(HDC hdc)
{
    //itemImg->Render(hdc,500,500);
    itemImg->FrameRender(hdc, pos.x, pos.y, itemType % 7, 0, true);
}
