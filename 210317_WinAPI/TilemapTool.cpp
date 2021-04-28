#include "TilemapTool.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Button.h"
/*
    ���� 1. ������ ���� Ÿ���� ����Ÿ�� �ؿ� ��� (3�� ũ���)
    ���� 2. ������ ���� Ÿ�Ϸ� ���� ���� ������ ���õ� ��ǥ �̹��� ����
    ���� 3. �巡�׷� Ÿ���� ���� ���� & ���� 2�� �����ϰ� �̹��� ����
*/

TILE_INFO TilemapTool::tileInfo[TILE_X * TILE_Y];
int TilemapTool::gStageNum=1;

HRESULT TilemapTool::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);
    
    sampleTile = ImageManager::GetSingleton()->AddImage(
        "����Ÿ��", "Image/SamlpTile_2.bmp", SAMPLE_TILE_X*TILESIZE, SAMPLE_TILE_Y * TILESIZE ,
        SAMPLE_TILE_X, SAMPLE_TILE_Y,true,RGB(255,0,255));

    hSelectedBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

    // ���� ���� ��Ʈ ����
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            tileInfo[i * TILE_X + j].frameX = 3;
            tileInfo[i * TILE_X + j].frameY = 0;

            tileInfo[i * TILE_X + j].rcTile.left = TILESIZE * j;
            tileInfo[i * TILE_X + j].rcTile.top = TILESIZE * i;
            tileInfo[i * TILE_X + j].rcTile.right = 
                tileInfo[i * TILE_X + j].rcTile.left + TILESIZE;
            tileInfo[i * TILE_X + j].rcTile.bottom = 
                tileInfo[i * TILE_X + j].rcTile.top + TILESIZE;
        }
    }

    // ���� ���� ��Ʈ ����
    for (int i = 0; i < SAMPLE_TILE_Y; i++)
    {
        for (int j = 0; j < SAMPLE_TILE_X; j++)
        {
            SetRect(&sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile,
                TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j),
                (TILESIZE * i),
                TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j) + TILESIZE,
                (TILESIZE * i) + TILESIZE);

            sampleTileInfo[i * SAMPLE_TILE_X + j].frameX = j;
            sampleTileInfo[i * SAMPLE_TILE_X + j].frameY = i;

            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.left =
            //    TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j);
            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.top = (TILESIZE * i);
            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.right =
            //    sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.left + TILESIZE;
            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.bottom =
            //    sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.top + TILESIZE;
        }
    }
    ImageManager::GetSingleton()->AddImage("�����ư", "Image/Button_Save.bmp", 100, 100, 1, 2, false);
    ImageManager::GetSingleton()->AddImage("�ε��ư", "Image/Button_Load.bmp", 100, 100, 1, 2, false);
    ImageManager::GetSingleton()->AddImage("�ʴ��ϱ��ư", "Image/Button_PlusStage.bmp", 100, 100, 1, 2, false);
    ImageManager::GetSingleton()->AddImage("�ʻ����ư", "Image/Button_MinusStage.bmp", 100, 100, 1, 2, false);
    btnsave = new Button;
    btnload = new Button;
    btnplus = new Button;
    btnminu = new Button;
    btnsave->Init("�����ư", TILEMAPTOOLSIZE_X-sampleTile->GetWidth(), TILEMAPTOOLSIZE_Y-200);
    btnsave->SetFunc(Save);
    btnload->Init("�ε��ư", TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + 120 , TILEMAPTOOLSIZE_Y - 200);
    btnload->SetFunc(Load);
    btnplus->Init("�ʴ��ϱ��ư", TILEMAPTOOLSIZE_X - sampleTile->GetWidth()+240, TILEMAPTOOLSIZE_Y - 300);
    btnplus->SetFunc(PlusStage);
    btnminu->Init("�ʻ����ư", TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + 240, TILEMAPTOOLSIZE_Y - 200);
    btnminu->SetFunc(MinusStage);
    
    return S_OK;
}

void TilemapTool::Release()
{
    SAFE_RELEASE(btnsave);
    SAFE_RELEASE(btnload);
    SAFE_RELEASE(btnplus);
    SAFE_RELEASE(btnminu);
}

void TilemapTool::Update()
{
    if (btnsave)btnsave->Update();
    if (btnload)btnload->Update();
    if (btnplus)btnplus->Update();
    if (btnminu)btnminu->Update();
    //���̺�ε�
   
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_CONTROL))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
        {
            Load();
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
        {
            Load();
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
        {
            Load();
        }
    }
    else {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
        {
            Save();
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
        {
            Save();
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
        {
            Save();
        }
    }


    // ���� ���� ���
    rcMain.left = 0;
    rcMain.top = 0;
    rcMain.right = rcMain.left + (TILESIZE * TILE_X);
    rcMain.bottom = rcMain.top + (TILESIZE * TILE_Y);

    // ���� ���� ���
    rcSample.left = TILEMAPTOOLSIZE_X - sampleTile->GetWidth();
    rcSample.top = 0;
    rcSample.right = TILEMAPTOOLSIZE_X;
    rcSample.bottom = sampleTile->GetHeight();

    if (PtInRect(&rcMain, g_ptMouse))
    {
        // ���콺 ���� ��ư Ŭ���� ��ǥ ���
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON)
            || KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            for (int i = 0; i < TILE_X * TILE_Y; i++)
            {
                if (PtInRect(&(tileInfo[i].rcTile), g_ptMouse))
                {
                    //selectedFrameX = i % TILE_X;
                    //selectedFrameY = i / TILE_X;

                    tileInfo[i].frameX = ptStartSelectedFrame.x;
                    tileInfo[i].frameY = ptStartSelectedFrame.y;

                    for (int j = 0; j <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; j++)
                    {
                        for (int k = 0; k <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; k++)
                        {
                            if ((i % TILE_X) + k >= TILE_X) continue;
                            if ((i / TILE_X) + j >= TILE_Y) continue;

                            tileInfo[i + j * TILE_X + k].frameX = ptStartSelectedFrame.x + k;
                            tileInfo[i + j * TILE_X + k].frameY = ptStartSelectedFrame.y + j;
                        }
                    }

                    break;
                }
            }
        }
    }
    else if (PtInRect(&rcSample, g_ptMouse))
    {
        // ���콺 ���� ��ư Ŭ���� ��ǥ ���
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
            // 2) ���콺 ��ǥ�� �ε��� ���
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            ptStartSelectedFrame.x = posX / TILESIZE;
            ptStartSelectedFrame.y = posY / TILESIZE;

            ptSelected[0] = g_ptMouse;

            //// 1) ��� Ÿ���� �ݺ��ϸ鼭 ��Ʈ�浹 Ȯ��
            //for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
            //{
            //    if (PtInRect(&(sampleTileInfo[i].rcTile), g_ptMouse))
            //    {
            //        ptStartSelectedFrame.x = i % SAMPLE_TILE_X;
            //        ptStartSelectedFrame.y = i / SAMPLE_TILE_X;

            //        break;
            //    }
            //}
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
        {
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            ptEndSelectedFrame.x = posX / TILESIZE;
            ptEndSelectedFrame.y = posY / TILESIZE;

            // ���ÿ��� �ʱ�ȭ
            ptSelected[0].x = -1;
            ptSelected[0].y = -1;
            ptSelected[1].x = -1;
            ptSelected[1].y = -1;
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            ptSelected[1] = g_ptMouse;
        }
    }

}

void TilemapTool::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0,
        TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);

    // ����Ÿ�� ��ü
    sampleTile->Render(hdc, TILEMAPTOOLSIZE_X - sampleTile->GetWidth(), 0);

    // ���� ���� ǥ��
    hOldSelectedBrush = (HBRUSH)SelectObject(hdc, hSelectedBrush);
    Rectangle(hdc, ptSelected[0].x, ptSelected[0].y, ptSelected[1].x, ptSelected[1].y);
    SelectObject(hdc, hOldSelectedBrush);

    if (btnsave)btnsave->Render(hdc);
    if (btnload)btnload->Render(hdc);
    if (btnplus)btnplus->Render(hdc); 
    if (btnminu)btnminu->Render(hdc);
    // ���ο��� ��ü
    for (int i = 0; i < TILE_X * TILE_Y; i++)
    {
        sampleTile->FrameRender(hdc,
            tileInfo[i].rcTile.left,
            tileInfo[i].rcTile.top,
            tileInfo[i].frameX,
            tileInfo[i].frameY);
    }

    // ���õ� Ÿ��
    if (ptStartSelectedFrame.x == ptEndSelectedFrame.x &&
        ptStartSelectedFrame.y == ptEndSelectedFrame.y)
    {
        sampleTile->FrameRender(hdc, 
            TILEMAPTOOLSIZE_X - sampleTile->GetWidth(),
            sampleTile->GetHeight() + 50, 
            ptStartSelectedFrame.x, ptStartSelectedFrame.y, false, 3);
    }
    else
    {
        for (int i = 0; i <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; i++)
        {
            for (int j = 0; j <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; j++)
            {
                sampleTile->FrameRender(hdc,
                    TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (j * TILESIZE),
                    sampleTile->GetHeight() + 50 + (i * TILESIZE),
                    ptStartSelectedFrame.x + j, ptStartSelectedFrame.y + i, false, 1);

            }
        }
    }
    char szText[30]={};
    wsprintf(szText, "stageNum: %d", gStageNum);
    TextOut(hdc, 1460, 750, szText, strlen(szText));
}

void TilemapTool::Save(void)
{
    string fileName = "Save/saveMapData";
     fileName += to_string(gStageNum) + ".map";
    DWORD writtenBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(hFile, tileInfo,sizeof(TILE_INFO)*TILE_X* TILE_Y,&writtenBytes,NULL);
    CloseHandle(hFile);
}

void TilemapTool::Load(void)
{
    string fileName = "Save/saveMapData";
    fileName += to_string(gStageNum) + ".map";
    DWORD readBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readBytes, NULL))
    {

    }
    else
    {
        MessageBox(g_hWnd, "���̺�ε����", "error", MB_OK);
    }
    CloseHandle(hFile);
}
void TilemapTool::PlusStage(void)
{
    ++gStageNum;
    if (gStageNum > 3) 
    {
        gStageNum = 1;
    }
}
void TilemapTool::MinusStage(void)
{
    --gStageNum;
    if (gStageNum <= 0)
    {
        gStageNum = 3;
    }
}