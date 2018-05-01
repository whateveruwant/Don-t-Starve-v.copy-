#include "stdafx.h"
#include "menuScene.h"


menuScene::menuScene()
{
}


menuScene::~menuScene()
{
}

HRESULT menuScene::init(void)
{
	_menu = new Menu;
	_menu->init();

	return S_OK;
}

void menuScene::release(void)
{
	_menu->release();
}

void menuScene::update(void)
{
	_menu->update();
}

void menuScene::render(void)
{
	_menu->render();
}