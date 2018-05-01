#include "stdafx.h"
#include "UImanager.h"


UImanager::UImanager()
{
}


UImanager::~UImanager()
{
}

HRESULT UImanager::init(void)
{
	_charc = new Character;

	_timeMental = 0;
	_timeHunger = 0;
	_timeHp = 0;

	_hunger = STATMAX;
	_hp = STATMAX;
	_mental = STATMAX;

	//�Ұ� �ʱ�ȭ
	_hungerPopUp = false;
	_hpPopUp = false;
	_mentalPopUp = false;

	_onDeadPopUp = false;
	_onButton = false;
	_clickButton = false;

	return S_OK;
}

void UImanager::release(void)
{
}

void UImanager::update(void)
{
	reduceHunger(_timeHunger, REDUCEHUNGER);
	reduceHp(_timeHp, REDUCEHUNGER);

	popUpCheck(_hungerPopUp, 1163, 89);
	popUpCheck(_hpPopUp, 1226, 89);
	popUpCheck(_mentalPopUp, 1194, 137);

	if (_hp <= 0) {
		_onDeadPopUp = true;
	}

	if (KEYMANAGER->isOnceKeyDown('O')) {
		damageHp(5);
	}

	diePopUpButtonFunc(_onDeadPopUp, 540, 460, _clickButton);
}

void UImanager::render(void)
{
	//������ �̹��� ����
	IMAGEMANAGER->frameRender(L"hunger", Rt, 1163, 89, 50 - _hunger, 0);
	IMAGEMANAGER->frameRender(L"health", Rt, 1226, 89, 50 - _hp, 0);
	IMAGEMANAGER->frameRender(L"mental", Rt, 1194, 137, 50 - _mental, 0);

	//�ѹ� �߰��� ��ġ�� ���Ƿ� �����߽��ϴ�(���� �����մϴ� �̤�)
	popUpNumberRender(_hungerPopUp, _hunger, 1163 + STATIMAGE_FRAMEWIDTH - 9, 89 + STATIMAGE_HEIGHT / 9);
	popUpNumberRender(_hpPopUp, _hp, 1226 + STATIMAGE_FRAMEWIDTH - 9, 89 + STATIMAGE_HEIGHT / 9);
	popUpNumberRender(_mentalPopUp, _mental, 1194 + STATIMAGE_FRAMEWIDTH - 9, 137 + STATIMAGE_HEIGHT / 9);

	if (_onDeadPopUp) {
		Rt->FillRectangle(D2D1::RectF(0, 0, WINSIZEX_NUM, WINSIZEY_NUM), BlackBrush);
		IMAGEMANAGER->render(L"dead_popup", Rt, 304, 161);
		int tmp = *day;
		int count = 0;
		while (tmp != 0) {
			count++;
			IMAGEMANAGER->frameRender(L"day_number", Rt, 600  - 20 * count, 307, tmp % 10, 0);
			tmp /= 10;
		}
		if (count == 0) {
			IMAGEMANAGER->frameRender(L"day_number", Rt, 600, 307, 0, 0);
		}

		if (!SOUNDMANAGER->isPlaySound("deadSound")) SOUNDMANAGER->bgmPlay("deadSound", 0.6f);
	}

	diePopUpMouseCheck(_onDeadPopUp, 540, 460, _onButton);

	if (_onDeadPopUp) {
		if (!_onButton) IMAGEMANAGER->render(L"dead_quit_button", Rt, 540, 460);
		else IMAGEMANAGER->render(L"dead_quit_button_on", Rt, 540, 460);
	}
}

void UImanager::reduceHp(int & timeStat, int reduceValue)
{
	//�ð��� ������ ĳ������ �������� �پ��ϴ�(�̰��� �ð��� ������ �پ��� �� ���ο���)
	if ((int)TIMEMANAGER->getWorldTime() % reduceValue == 0 && (int)TIMEMANAGER->getWorldTime() != timeStat) {
		timeStat = (int)TIMEMANAGER->getWorldTime();
		if (_mental <= 5) {
			damageHp(10);
		}
		if (_hunger <= 5) {
			damageHp(10);
		}
		if (_mental >= 40 && _hunger >= 40) {
			upHp();
		}
	}
}

void UImanager::reduceMental(int reduceValue, int damage)
{
	//�ð��� ������ ĳ������ �������� �پ��ϴ�(�̰��� �ð��� ������ �پ��� �� ���ο���)
	if ((int)TIMEMANAGER->getWorldTime() % reduceValue == 0 && (int)TIMEMANAGER->getWorldTime() != _timeMental) {
		_timeMental = (int)TIMEMANAGER->getWorldTime();
		damageMental(damage);
	}
}

void UImanager::reduceHunger(int & timeStat, int reduceValue)
{
	//�ð��� ������ ĳ������ �������� �پ��ϴ�(�̰��� �ð��� ������ �پ��� �� ���ο���)
	if ((int)TIMEMANAGER->getWorldTime() % reduceValue == 0 && (int)TIMEMANAGER->getWorldTime() != timeStat) {
		timeStat = (int)TIMEMANAGER->getWorldTime();
		damageHunger(1);
	}
}

void UImanager::popUpCheck(bool& popUp, int x, int y)
{
	//���콺�� ��Ʈ �ȿ� ���ִ���? (STATEIMAGE_FRAMEWIDTH = ���ΰ�, STATEIMAGE_HEIGHT = ���ΰ� �������Դϴ�)
	if (IsInRect(_ptMouse, { x, y, x + STATIMAGE_FRAMEWIDTH, y + STATIMAGE_HEIGHT })) {
		popUp = true;
	}
	else {
		popUp = false;
	}
}

void UImanager::popUpNumberRender(bool popUp, int stat, int x, int y)
{
	//���������� �����ֽ� ����Դϴ�(Ȯ���� �����ϰ� �ּ� �߰��ҰԿ�)
	if (popUp) {
		int tmp = stat;
		int countScore = 0;
		while (tmp != 0) {
			countScore++;
			IMAGEMANAGER->frameRender(L"number", Rt, x - 15 * countScore, y, tmp % 10, 0);
			tmp /= 10;
		}
		if (countScore == 0) {
			IMAGEMANAGER->frameRender(L"number", Rt, x, y, 0, 0);
		}
	}
}

void UImanager::diePopUpMouseCheck(bool onDeadPopUp, int x, int y, bool& onButton)
{
	if (onDeadPopUp) {
		//���콺�� ��Ʈ �ȿ� ���ִ���?
		if (IsInRect(_ptMouse, { x, y, x + 195, y + 61 })) {
			onButton = true;
		}
		else {
			onButton = false;
		}
	}
}

void UImanager::diePopUpButtonFunc(bool onDeadPopUp, int x, int y, bool& clickButton)
{
	if (onDeadPopUp) {
		if (IsInRect(_ptMouse, { x, y, x + 195, y + 61 })) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("click");
				clickButton = !clickButton;
			}
		}

		if (clickButton) SCENEMANAGER->changeScene("menuScene");
	}
}