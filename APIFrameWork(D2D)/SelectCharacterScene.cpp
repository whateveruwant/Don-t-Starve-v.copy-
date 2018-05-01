#include "stdafx.h"
#include "SelectCharacterScene.h"


SelectCharacterScene::SelectCharacterScene()
{
}


SelectCharacterScene::~SelectCharacterScene()
{
}

HRESULT SelectCharacterScene::init()
{
	if (!SOUNDMANAGER->isPlaySound("mainBGM")) SOUNDMANAGER->bgmPlay("mainBGM");

	_onSelectWilson = false;

	_onSelectNoButton = false;
	_onSelectYesButton = false;

	_clickSelectNoButton = false;
	_clickSelectYesButton = false;

	return S_OK;
}

void SelectCharacterScene::release()
{
}

void SelectCharacterScene::update()
{
	selectWilsonCheck(_onSelectWilson, 540, 103);
	buttonCheck(_onSelectNoButton, _onSelectYesButton, 665, 620, 940, 620);
	buttonClick(_clickSelectNoButton, _clickSelectYesButton, 665, 620, 940, 620);

	//���� no��ư�� Ŭ������ ��� �޴� ������ ���ư���
	if (_clickSelectNoButton) {
		SOUNDMANAGER->play("click");
		if (SOUNDMANAGER->isPlaySound("mainBGM")) SOUNDMANAGER->stop("mainBGM");

		SCENEMANAGER->changeScene("menuScene");
	}

	//���� yes��ư�� Ŭ������ ��� ���� ������ ���ư���
	if (_clickSelectYesButton) {
		SOUNDMANAGER->play("click");
		if (SOUNDMANAGER->isPlaySound("mainBGM")) SOUNDMANAGER->stop("mainBGM");
		SCENEMANAGER->changeScene("createWorld");
	}
}

void SelectCharacterScene::render()
{
	//���� ���ù�ư(���� ������ �׷��� ���� �ʻ�ȭ)�� Ŭ������ �������� ���� 
	if (!_onSelectWilson) {
		IMAGEMANAGER->render(L"characterSelect", Rt);
	}

	else {
		IMAGEMANAGER->render(L"characterSelect_on", Rt);

		if (!_onSelectNoButton) {
			IMAGEMANAGER->render(L"selectButton_no", Rt, 665, 620);
		}

		else {
			IMAGEMANAGER->render(L"selectButton_no_on", Rt, 665, 620);
		}

		if (!_onSelectYesButton) {
			IMAGEMANAGER->render(L"selectButton_yes", Rt, 940, 620);
		}

		else {
			IMAGEMANAGER->render(L"selectButton_yes_on", Rt, 940, 620);
		}
	}
}

void SelectCharacterScene::selectWilsonCheck(bool& onSelectWilson, int x, int y)
{
	//���콺�� ��Ʈ �ȿ� ���ִ���?
	if (IsInRect(_ptMouse, { x, y, x + 94, y + 129 })) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->play("click");
			onSelectWilson = !onSelectWilson;
		}
	}
}

void SelectCharacterScene::buttonCheck(bool& onSelectNoButton, bool& onSelectYesButton, int x1, int y1, int x2, int y2)
{
	//���콺�� ��Ʈ �ȿ� ���ִ���?
	if (IsInRect(_ptMouse, { x1, y1, x1 + 195, y1 + 61 })) {
		onSelectNoButton = true;
	}
	else {
		onSelectNoButton = false;
	}

	//���콺�� ��Ʈ �ȿ� ���ִ���?
	if (IsInRect(_ptMouse, { x2, y2, x2 + 195, y2 + 61 })) {
		onSelectYesButton = true;
	}
	else {
		onSelectYesButton = false;
	}
}

void SelectCharacterScene::buttonClick(bool& clickSelectNoButton, bool& clickSelectYesButton, int x1, int y1, int x2, int y2)
{
	if (_onSelectWilson) {
		//���콺�� ��Ʈ �ȿ� ���ִ���?
		if (IsInRect(_ptMouse, { x1, y1, x1 + 195, y1 + 61 })) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				clickSelectNoButton = true;
			}
			else {
				clickSelectNoButton = false;
			}
		}

		//���콺�� ��Ʈ �ȿ� ���ִ���?
		if (IsInRect(_ptMouse, { x2, y2, x2 + 195, y2 + 61 })) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				clickSelectYesButton = true;
			}
			else {
				clickSelectYesButton = false;
			}
		}
	}
}
