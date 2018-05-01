#pragma once
#include "image.h"
#include "ItemInfo.h"

//ĳ����
#define SPEED 10.0f
//Ÿ��
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

//�κ��丮
#define IVENTORYMAX 21

//����
#define M_TILESIZE 68		//���� ȭ�� Ÿ�� ������
#define MINITILESIZE 34 //������ ȭ�� Ÿ�� ������
#define MINIMAPTILESIZE 7	//�̴ϸ� Ÿ�� ������

#define MINITILESIZEX TILEX * MINITILESIZE
#define MINITILESIZEY TILEY * MINITILESIZE

//#define TILESIZEX TILEX *M_TILESIZE
//#define TILESIZEY TILEY * M_TILESIZE

//ȭ�� ������ �̹��� Ÿ�� ����
#define SAMPLETILEX 3
#define SAMPLETILEY 9

//Ÿ�ϰ� ������ �Բ�����
enum TILESTATE { GRASSTILE, FORESTTILE, STONETILE };	// �� ���� �� Ÿ�� ����
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

	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode();
	virtual ~gameNode();

	tagPos* getPos() { return &_pos; }
	void setPos(int x, int y) { _pos.x = x; _pos.y = y; }

	bool compare(gameNode* a, gameNode* b);
};