#include "Item.h"
#include "Image.h"

HRESULT Item::Init()
{
    itemImg= ImageManager::GetSingleton()->AddImage("아이템이미지",
        "Image/ItemImage.bmp", 462,66,7,1, true, RGB(255, 0, 255));

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
    itemImg->FrameRender(hdc, 500, 500, 6 % 7, 0, true);
}
