#include "stdafx.h"
#include "gameScene.h"


gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}

HRESULT gameScene::init(void)
{
	if (SOUNDMANAGER->isPlaySound("mainBGM")) SOUNDMANAGER->stop("mainBGM");

	_map = new Map;
	_map->init();

	_stopMenuPopUp = false;
	_stopMenuGameBreak = false;
	_stopMenuGameResume = false;

	return S_OK;
}

void gameScene::release(void)
{
	_map->release();
}

void gameScene::update(void)
{
	stopMenuUpCheck(_stopMenuPopUp, 1222, 693);
	stopMenuButtonClickCheck(_stopMenuGameBreak, _stopMenuGameResume, 564, 355, 564, 445);
	stopMenuButtonFunc(_stopMenuGameBreak, _stopMenuGameResume, _stopMenuPopUp);
	if (!_stopMenuPopUp) {
		_map->update();
	}
}

void gameScene::render(void)
{
	_map->render();
	if (_stopMenuPopUp) {
		Rt->FillRectangle(D2D1::RectF(0, 0, WINSIZEX_NUM, WINSIZEY_NUM), BlackBrush);
	}
	IMAGEMANAGER->render(L"stopMenuButton", Rt, 1222, 693);
	stopMenuRender(_stopMenuPopUp, WINSIZEX_NUM / 2 - 199, WINSIZEY_NUM / 2 - 225);
}

void gameScene::stopMenuUpCheck(bool & popUp, int x, int y)
{
	//스탑 메뉴 렉트안에 마우스가 있고 LBUTTON이 눌렸을때 
	if (IsInRect(_ptMouse, { x, y, x + 23, y + 22 })) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			//현재 popUp 인자의 불값을 바꿔줍니다
			//이렇게되면 처음 버튼을 눌렀을때는 true가 되고 다시 버튼을 누르면 false가 됩니다(논리반전)
			SOUNDMANAGER->play("click");
			popUp = !popUp;
		}
	}
}

void gameScene::stopMenuRender(bool popUp, int x, int y)
{
	//popUp이 true일 경우에 stopMenu를 키값으로 가지는 이미지를 띄운다
	if (popUp) {
		IMAGEMANAGER->render(L"stopMenu", Rt, x, y);
		IMAGEMANAGER->render(L"stopMenuButton_yes", Rt, x + 123, y + 220);
		IMAGEMANAGER->render(L"stopMenuButton_no", Rt, x + 123, y + 310);
	}
}

void gameScene::stopMenuButtonClickCheck(bool & popUpGameStop, bool & popUpGameResume, int x1, int y1, int x2, int y2)
{
	if (_stopMenuPopUp) {
		//스탑 메뉴 첫번째 버튼 안에 마우스가 있고 LBUTTON이 눌렸을때 
		if (IsInRect(_ptMouse, { x1, y1, x1 + 165, y1 + 53 })) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				//popUpGameStop이 true 아니면 false
				popUpGameStop = true;
			}
			else {
				popUpGameStop = false;
			}
		}

		else if (IsInRect(_ptMouse, { x2, y2, x2 + 165, y2 + 53 })) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				//popUpGameResume이 true 아니면 false
				popUpGameResume = true;
			}
			else {
				popUpGameResume = false;
			}
		}
	}
}

void gameScene::stopMenuButtonFunc(bool& popUpGameStop, bool& popUpGameResume, bool & popUp)
{
	//게임 종료 판별 불값, 게임 재개 판별 불값, 메뉴 창 불값을 받아서
	if (popUpGameStop) {
		//게임 종료 판별 불값이 true이면 게임을 종료(임시)합니다
		SOUNDMANAGER->play("click");
		popUpGameStop = !popUpGameStop;
		if (SOUNDMANAGER->isPlaySound("MorningSound")) SOUNDMANAGER->stop("MorningSound");
		SCENEMANAGER->changeScene("menuScene");
	}

	//게임 재개 판별 불값이 true이면 메뉴 창의 불값을 논리반전합니다
	//메뉴 창이 켜져있는 상태이니 true가 false로 바뀝니다(메뉴 창 닫힘)
	else if (popUpGameResume) {
		SOUNDMANAGER->play("click");
		popUpGameResume = !popUpGameResume;
		popUp = !popUp;
	}
}