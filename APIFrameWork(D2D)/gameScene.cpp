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
	//��ž �޴� ��Ʈ�ȿ� ���콺�� �ְ� LBUTTON�� �������� 
	if (IsInRect(_ptMouse, { x, y, x + 23, y + 22 })) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			//���� popUp ������ �Ұ��� �ٲ��ݴϴ�
			//�̷��ԵǸ� ó�� ��ư�� ���������� true�� �ǰ� �ٽ� ��ư�� ������ false�� �˴ϴ�(������)
			SOUNDMANAGER->play("click");
			popUp = !popUp;
		}
	}
}

void gameScene::stopMenuRender(bool popUp, int x, int y)
{
	//popUp�� true�� ��쿡 stopMenu�� Ű������ ������ �̹����� ����
	if (popUp) {
		IMAGEMANAGER->render(L"stopMenu", Rt, x, y);
		IMAGEMANAGER->render(L"stopMenuButton_yes", Rt, x + 123, y + 220);
		IMAGEMANAGER->render(L"stopMenuButton_no", Rt, x + 123, y + 310);
	}
}

void gameScene::stopMenuButtonClickCheck(bool & popUpGameStop, bool & popUpGameResume, int x1, int y1, int x2, int y2)
{
	if (_stopMenuPopUp) {
		//��ž �޴� ù��° ��ư �ȿ� ���콺�� �ְ� LBUTTON�� �������� 
		if (IsInRect(_ptMouse, { x1, y1, x1 + 165, y1 + 53 })) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				//popUpGameStop�� true �ƴϸ� false
				popUpGameStop = true;
			}
			else {
				popUpGameStop = false;
			}
		}

		else if (IsInRect(_ptMouse, { x2, y2, x2 + 165, y2 + 53 })) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				//popUpGameResume�� true �ƴϸ� false
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
	//���� ���� �Ǻ� �Ұ�, ���� �簳 �Ǻ� �Ұ�, �޴� â �Ұ��� �޾Ƽ�
	if (popUpGameStop) {
		//���� ���� �Ǻ� �Ұ��� true�̸� ������ ����(�ӽ�)�մϴ�
		SOUNDMANAGER->play("click");
		popUpGameStop = !popUpGameStop;
		if (SOUNDMANAGER->isPlaySound("MorningSound")) SOUNDMANAGER->stop("MorningSound");
		SCENEMANAGER->changeScene("menuScene");
	}

	//���� �簳 �Ǻ� �Ұ��� true�̸� �޴� â�� �Ұ��� �������մϴ�
	//�޴� â�� �����ִ� �����̴� true�� false�� �ٲ�ϴ�(�޴� â ����)
	else if (popUpGameResume) {
		SOUNDMANAGER->play("click");
		popUpGameResume = !popUpGameResume;
		popUp = !popUp;
	}
}