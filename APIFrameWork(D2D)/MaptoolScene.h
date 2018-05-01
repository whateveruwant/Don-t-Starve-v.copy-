#pragma once
#include "gameNode.h"



enum MOUSESTATE { SELECTTILE, ERESETILE };



struct S_MINIMAPTILE {
	int _x, _y;
	int backTileFrameX, backTileFrameY;

	int forestTileFrameX, forestTileFrameY;
	int stoneTileFrameX, stoneTileFrameY;

	bool forestExist, stoneExist;

	TILESTATE _state;
	RECT rc;
};


//�̹��� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//���� Ÿ�� ����ü
struct tagCurrentTile
{
	int x;
	int y;
};



class MaptoolScene : public gameNode
{
private:

	tagCurrentTile _currentTile;
	S_TILE _tiles[TILEX * TILEY];
	S_MINIMAPTILE _minimaptiles[TILEX * TILEY];
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];

	int _x, _y;

	int _index;

	RECT erese_button;
	RECT reset_button;
	RECT save_button;
	RECT load_button;
	RECT minimap_button;
	RECT exit_button;

	bool show_minimap;

	int mouse_state;

public:

	MaptoolScene();
	~MaptoolScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);




	//���� ����
	void maptoolSetup();
	void setMap();

	//���� ����
	void save();
	void load();


	bool forestCheck(int i);
	bool stoneCheck(int i);

	void objCheck(int i);

	void ereseTile();
	void resetTile();

	void minimapUpdate();
};

