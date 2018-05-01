#pragma once
#include "gameNode.h"
#include "Menu.h"
class menuScene : public gameNode
{
private:
	Menu* _menu;

public:
	menuScene();
	~menuScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};