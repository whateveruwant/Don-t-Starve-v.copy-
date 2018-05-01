#pragma once
#include "gameNode.h"
#include "Tiles.h"
#include "loading.h"

class CreatingWorldScene : public gameNode
{
private:
	loading* mLoading;
	int frameX_hand;
	int frame_world;
	int frame_text;
	int count;
public:
	CreatingWorldScene();
	~CreatingWorldScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void totalLoading();
};