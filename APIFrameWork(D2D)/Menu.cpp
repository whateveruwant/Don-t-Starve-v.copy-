#include "stdafx.h"
#include "Menu.h"


Menu::Menu()
{
}


Menu::~Menu()
{
}

HRESULT Menu::init(void)
{
	SOUNDMANAGER->bgmPlay("mainBGM");
	onWhere = EMENUONMOUSE_NONE;
	return S_OK;
}

void Menu::release(void)
{
}

void Menu::update(void)
{
	checkWhereMouse();
	checkClick();

}

void Menu::render(void)
{
	IMAGEMANAGER->render(L"mainMenu", Rt);
	switch (onWhere)
	{
	case EMENUONMOUSE_NONE:
		IMAGEMANAGER->render(L"mainMenuButton_start", Rt, WINSIZEX_NUM - WINSIZEX_NUM / 4, WINSIZEY_NUM / 4 + 150);
		IMAGEMANAGER->render(L"mainMenuButton_maptool", Rt, WINSIZEX_NUM - WINSIZEX_NUM / 4, WINSIZEY_NUM / 4 + 250);
		IMAGEMANAGER->render(L"mainMenuButton_quit", Rt, WINSIZEX_NUM - WINSIZEX_NUM / 4, WINSIZEY_NUM / 4 + 350);
		break;
	case EMENUONMOUSE_START:
		IMAGEMANAGER->render(L"mainMenuButton_start_on", Rt, WINSIZEX_NUM - WINSIZEX_NUM / 4, WINSIZEY_NUM / 4 + 150);
		IMAGEMANAGER->render(L"mainMenuButton_maptool", Rt, WINSIZEX_NUM - WINSIZEX_NUM / 4, WINSIZEY_NUM / 4 + 250);
		IMAGEMANAGER->render(L"mainMenuButton_quit", Rt, WINSIZEX_NUM - WINSIZEX_NUM / 4, WINSIZEY_NUM / 4 + 350);
		break;
	case EMENUONMOUSE_MAPTOOL:
		IMAGEMANAGER->render(L"mainMenuButton_start", Rt, WINSIZEX_NUM - WINSIZEX_NUM / 4, WINSIZEY_NUM / 4 + 150);
		IMAGEMANAGER->render(L"mainMenuButton_maptool_on", Rt, WINSIZEX_NUM - WINSIZEX_NUM / 4, WINSIZEY_NUM / 4 + 250);
		IMAGEMANAGER->render(L"mainMenuButton_quit", Rt, WINSIZEX_NUM - WINSIZEX_NUM / 4, WINSIZEY_NUM / 4 + 350);
		break;
	case EMENUONMOUSE_EXIT:
		IMAGEMANAGER->render(L"mainMenuButton_start", Rt, WINSIZEX_NUM - WINSIZEX_NUM / 4, WINSIZEY_NUM / 4 + 150);
		IMAGEMANAGER->render(L"mainMenuButton_maptool", Rt, WINSIZEX_NUM - WINSIZEX_NUM / 4, WINSIZEY_NUM / 4 + 250);
		IMAGEMANAGER->render(L"mainMenuButton_quit_on", Rt, WINSIZEX_NUM - WINSIZEX_NUM / 4, WINSIZEY_NUM / 4 + 350);
		break;
	}
}

void Menu::checkWhereMouse()
{
	if (IsInRect(_ptMouse, { (int)(WINSIZEX_NUM - WINSIZEX_NUM / 4), (int)(WINSIZEY_NUM / 4 + 150) ,(int)(WINSIZEX_NUM - WINSIZEX_NUM / 4 + 195), (int)(WINSIZEY_NUM / 4 + 150 + 61) })) {
		onWhere = EMENUONMOUSE_START;
	}
	else if (IsInRect(_ptMouse, { (int)(WINSIZEX_NUM - WINSIZEX_NUM / 4), (int)(WINSIZEY_NUM / 4 + 250) ,(int)(WINSIZEX_NUM - WINSIZEX_NUM / 4 + 195), (int)(WINSIZEY_NUM / 4 + 250 + 61) })) {
		onWhere = EMENUONMOUSE_MAPTOOL;
	}
	else if (IsInRect(_ptMouse, { (int)(WINSIZEX_NUM - WINSIZEX_NUM / 4), (int)(WINSIZEY_NUM / 4 + 350) ,(int)(WINSIZEX_NUM - WINSIZEX_NUM / 4 + 195), (int)(WINSIZEY_NUM / 4 + 350 + 61) })) {
		onWhere = EMENUONMOUSE_EXIT;
	}
	else {
		onWhere = EMENUONMOUSE_NONE;
	}
}

void Menu::checkClick()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		switch (onWhere)
		{
		case EMENUONMOUSE_START:
			tile_init_select = false;
			SOUNDMANAGER->play("click");
			SCENEMANAGER->changeScene("selectScene");
			break;
		case EMENUONMOUSE_MAPTOOL:
			tile_init_select = true;
			SOUNDMANAGER->play("click");
			SCENEMANAGER->changeScene("maptoolScene");
			break;
		case EMENUONMOUSE_EXIT:
			SOUNDMANAGER->play("click");
			PostQuitMessage(0);
			break;
		}
	}
}
