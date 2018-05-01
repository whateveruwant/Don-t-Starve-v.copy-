#pragma once
#include "gameNode.h"

struct S_MINITILE {

	int _x, _y;

	TILESTATE _state;

};

struct S_WAVE
{
	float x, y;
	int wave_count;
};

class Tiles : public gameNode
{
private:
	S_TILE _tile[TILEX][TILEY];
	S_MINITILE _minitile[TILEX][TILEY];

	S_WAVE _wave[10];

	POINT _standard;			//현재 player의 좌표를 저장할 변수
	int count;

public:
	Tiles();
	~Tiles();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void objFrontRender(void);
	void objMateRender(void);


	inline S_TILE getTile(int _indexX, int _indexY) { return _tile[_indexX][_indexY]; }
	bool generatorDone();
	void calulateStandard();

	bool backTileInit();
	bool forestTileInit();
	bool stoneTileInit();

	bool objEnviInit();
	bool objMateInit();

	bool maptool_objEnviInit();
	void waveMotion(int i);


	void miniTileInit();
	void showMinimap();
	void mapLoad();

	void objInit();
};