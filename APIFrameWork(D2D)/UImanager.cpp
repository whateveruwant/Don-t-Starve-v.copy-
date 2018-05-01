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

	//불값 초기화
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
	//프레임 이미지 렌더
	IMAGEMANAGER->frameRender(L"hunger", Rt, 1163, 89, 50 - _hunger, 0);
	IMAGEMANAGER->frameRender(L"health", Rt, 1226, 89, 50 - _hp, 0);
	IMAGEMANAGER->frameRender(L"mental", Rt, 1194, 137, 50 - _mental, 0);

	//넘버 뜨게할 위치는 임의로 설정했습니다(조금 복잡합니다 ㅜㅜ)
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
	//시간이 지나면 캐릭터의 포만감이 줄어듭니다(이것은 시간이 지나면 줄어드는 게 전부에요)
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
	//시간이 지나면 캐릭터의 포만감이 줄어듭니다(이것은 시간이 지나면 줄어드는 게 전부에요)
	if ((int)TIMEMANAGER->getWorldTime() % reduceValue == 0 && (int)TIMEMANAGER->getWorldTime() != _timeMental) {
		_timeMental = (int)TIMEMANAGER->getWorldTime();
		damageMental(damage);
	}
}

void UImanager::reduceHunger(int & timeStat, int reduceValue)
{
	//시간이 지나면 캐릭터의 포만감이 줄어듭니다(이것은 시간이 지나면 줄어드는 게 전부에요)
	if ((int)TIMEMANAGER->getWorldTime() % reduceValue == 0 && (int)TIMEMANAGER->getWorldTime() != timeStat) {
		timeStat = (int)TIMEMANAGER->getWorldTime();
		damageHunger(1);
	}
}

void UImanager::popUpCheck(bool& popUp, int x, int y)
{
	//마우스가 렉트 안에 가있는지? (STATEIMAGE_FRAMEWIDTH = 가로값, STATEIMAGE_HEIGHT = 세로값 디파인입니다)
	if (IsInRect(_ptMouse, { x, y, x + STATIMAGE_FRAMEWIDTH, y + STATIMAGE_HEIGHT })) {
		popUp = true;
	}
	else {
		popUp = false;
	}
}

void UImanager::popUpNumberRender(bool popUp, int stat, int x, int y)
{
	//유민형님이 보여주신 기능입니다(확실히 이해하고 주석 추가할게요)
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
		//마우스가 렉트 안에 가있는지?
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