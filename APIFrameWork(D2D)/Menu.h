#pragma once
#include "gameNode.h"
enum EMENUONMOUSE { EMENUONMOUSE_NONE, EMENUONMOUSE_START, EMENUONMOUSE_MAPTOOL, EMENUONMOUSE_EXIT };
class Menu : public gameNode
{
private:
	EMENUONMOUSE onWhere;

public:
	Menu();
	~Menu();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void checkWhereMouse();
	void checkClick();
};