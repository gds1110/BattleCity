// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include <map>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"

#define WINSIZE_X	1080
#define WINSIZE_Y	720
#define TILEMAPTOOLSIZE_X	1620
#define TILEMAPTOOLSIZE_Y	900

#define PI			3.141592f
#define DegToRad(x)	((x) * PI / 180.0f)
#define SAFE_DELETE(p) { if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p) { if (p) { p->Release(); delete p; p = nullptr; } }

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

//typedef tagFPoint FPOINT2;
//typedef tagFPoint* PFPOINT2;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

enum class TileType
{
	NORMAL,IRON,BUSH,RIVER,ICE,EAGLE,BLACK,NONE
};

typedef struct tagTile
{
	RECT rcTile;
	int frameX;
	int frameY;
	TileType tileType;
} TILE_INFO;

// 샘플 타일 정보
#define SAMPLE_TILE_X	11
#define SAMPLE_TILE_Y	14
#define TILESIZE		32


// 메인 그리기 공간 정보
#define	TILE_X			26
#define	TILE_Y			26

#define UISPACE_X		150