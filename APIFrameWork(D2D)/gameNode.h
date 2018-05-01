#pragma once
#include "image.h"
#include "ItemInfo.h"

//캐릭터
#define SPEED 10.0f
//타일
#define TILEX 500
#define TILEY 500
#define TILESIZEX 128
#define TILESIZEY 128
#define MAPMAX_X 128*500
#define MAPMAX_Y 128*500
//UI
#define STATMAX 50
#define REDUCEMENTAL 5
#define REDUCEHUNGER 5
#define STATIMAGE_FRAMEWIDTH 48
#define STATIMAGE_HEIGHT 48
#define MINITILESIZEX 32
#define MINITILESIZEY 32

//인벤토리
#define IVENTORYMAX 21

//맵툴
#define M_TILESIZE 68		//왼쪽 화면 타일 사이즈
#define MINITILESIZE 34 //오른쪽 화면 타일 사이즈
#define MINIMAPTILESIZE 7	//미니맵 타일 사이즈

#define MINITILESIZEX TILEX * MINITILESIZE
#define MINITILESIZEY TILEY * MINITILESIZE

//#define TILESIZEX TILEX *M_TILESIZE
//#define TILESIZEY TILEY * M_TILESIZE

//화면 오른쪽 이미지 타일 갯수
#define SAMPLETILEX 3
#define SAMPLETILEY 9

//타일과 맵툴이 함께쓴다
enum TILESTATE { GRASSTILE, FORESTTILE, STONETILE };	// 맨 위에 깔릴 타일 종류
struct S_TILE {
	int _x, _y;
	int backTileFrameX, backTileFrameY;

	int forestTileFrameX, forestTileFrameY;
	int stoneTileFrameX, stoneTileFrameY;

	bool forestExist, stoneExist;

	RECT rc;

	TILESTATE _state;
	EOBJKIND_ENVIRONMENT _objstate;
};


class gameNode
{
protected:
	tagPos _pos;

private:
	bool _managerInit;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode();
	virtual ~gameNode();

	tagPos* getPos() { return &_pos; }
	void setPos(int x, int y) { _pos.x = x; _pos.y = y; }

	bool compare(gameNode* a, gameNode* b);
};