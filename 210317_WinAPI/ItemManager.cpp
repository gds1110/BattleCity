#include "ItemManager.h"
#include "Image.h"
#include "Item.h"

HRESULT ItemManager::Init()
{
    vItems.resize(10);
    vector<Item*>::iterator it;
    for (it = vItems.begin(); it != vItems.end(); it++)
    {
        (*it) = new Item();
        (*it)->Init();

        // 미사일 매니저를 들고 있는 적 객체의 정보를 전달
    }


    return S_OK;
}

void ItemManager::Release()
{

    for (int i = 0; i < vItems.size(); i++)
    {
        vItems[i]->Release();
    }
    vItems.clear();
}

void ItemManager::Update()
{
  

    for (int i = 0; i < vItems.size(); i++)
    {
        vItems[i]->Update();
    }
}

void ItemManager::Render(HDC hdc)
{
    for (int i = 0; i < vItems.size(); i++)
    {
        if (vItems[i]->GetDrop() == true) {
            vItems[i]->Render(hdc);
        }
    }
}

void ItemManager::DropItem(POINT pos,int type)
{
    for (int i = 0; i < vItems.size(); i++)
    {
        if (vItems[i]->GetDrop() == false)
        {
            vItems[i]->SetDrop(true);
            vItems[i]->SetPos(pos);
           // vItems[i]->SetRC(pos);
            vItems[i]->SetType(type);

            break;
        }
      
    }
}
