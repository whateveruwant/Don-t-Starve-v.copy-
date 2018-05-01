#pragma once
#include "gameNode.h"
#include "LoadingMainScene.h"
#include "LoadingGameScene.h"
#include "CreatingWorldScene.h"
#include "MaptoolScene.h"
#include "gameScene.h"
#include "menuScene.h"
#include "SelectCharacterScene.h"

class mainGame : public gameNode
{
public:
	mainGame();
	~mainGame();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};