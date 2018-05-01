#include "stdafx.h"
#include "Clock.h"


Clock::Clock()
{
}


Clock::~Clock()
{
}

HRESULT Clock::init()
{
	if (SOUNDMANAGER->isPlaySound("NightSound")) SOUNDMANAGER->stop("NightSound");
	SOUNDMANAGER->bgmPlay("MorningSound");
	//변수 초기화입니다
	_time = 0;
	_timetmp = 0;
	_state = AFTERNOON;
	_timeFrameX = _countFrame = 0;
	_day = 1;   //1일부터 시작
	IMAGEMANAGER->findImage(L"playerdamage")->setAlpha(0.0f);
	return S_OK;
}

void Clock::release()
{
}

void Clock::update()
{
	gameTimeConv(1, _timetmp, _time, _day);
	whatState(_state, _time);
	clockFrameFunc(_timeFrameX);
	if (_time == 0) {
		if (!SOUNDMANAGER->isPlaySound("MorningSound")) {
			SOUNDMANAGER->bgmPlay("MorningSound");
		}
	}
	if (IMAGEMANAGER->findImage(L"playerdamage")->getAlpha() > 0.0f) {
		IMAGEMANAGER->findImage(L"playerdamage")->setAlpha(IMAGEMANAGER->findImage(L"playerdamage")->getAlpha() - 0.05f);
	}
}

void Clock::render()
{
	filterRender();
	IMAGEMANAGER->render(L"playerdamage", Rt, 0, 0);
	//상태에 따라서 렌더합니다
	if (_state == AFTERNOON) IMAGEMANAGER->frameCenterRender(L"clockRoundAfternoon", Rt, 1219, 46, _timeFrameX, 0);
	if (_state == NIGHT) IMAGEMANAGER->frameCenterRender(L"clockRoundNight", Rt, 1218.5f, 46, _timeFrameX, 0);

	IMAGEMANAGER->render(L"clock", Rt, 1183, 11);

	Rt->SetTransform(D2D1::Matrix3x2F::Rotation(_time, D2D1::Point2F(1218.5f, 46.5f)));
	IMAGEMANAGER->render(L"clockNeedle", Rt, 1209.5f, 3.5f);
	Rt->SetTransform(D2D1::Matrix3x2F::Rotation(0, D2D1::Point2F(1218.5f, 46.5f)));

	IMAGEMANAGER->render(L"clockdaytxt", Rt, 1183, 26);
	dayNumberRender(_day, 1213, 40);
}

void Clock::gameTimeConv(int interval, int& timetmp, int& time, int& day)
{
	//1초마다 timetmp에 getWorldTime()을 저장합니다
	if ((int)TIMEMANAGER->getWorldTime() % interval == 0 && (int)TIMEMANAGER->getWorldTime() != timetmp) {
		timetmp = (int)TIMEMANAGER->getWorldTime();
		time++;
		time++;

		//360초일때 타임 초기화합니다
		if (time == 360) {
			time = 0;
			day++;
		}
	}
}

void Clock::whatState(ECLOCKSTATE& state, int time)
{
	//state값을 업데이트 해줍니다
	if (time >= 0 && time < 180) { state = AFTERNOON; if (SOUNDMANAGER->isPlaySound("NightSound")) SOUNDMANAGER->stop("NightSound"); }
	if (time >= 180 && time < 315) { state = EVENING;}
	if (time >= 315 && time < 360) { state = NIGHT; if (!SOUNDMANAGER->isPlaySound("NightSound")) SOUNDMANAGER->bgmPlay("NightSound"); }
}

void Clock::clockFrameFunc(int& timeFrameX)
{
	//프레임 렌더를 돌립니다
	timeFrameX++;
	if (timeFrameX > 13)
	{
		timeFrameX = 0;
	}
}

void Clock::dayNumberRender(int day, int x, int y)
{
	int tmp = day;
	int count = 0;
	while (tmp != 0) {
		count++;
		IMAGEMANAGER->frameRender(L"clockNumber", Rt, x - 15 * count, y, tmp % 10, 0);
		tmp /= 10;
	}
	if (count == 0) {
		IMAGEMANAGER->frameRender(L"clockNumber", Rt, x, y, 0, 0);
	}
}

void Clock::filterRender()
{
	//낮일 경우
	if (_state == AFTERNOON) {
	}

	//저녁일 경우
	else if (_state == EVENING) {
		Rt->FillRectangle(D2D_RECT_F{ 0, 0, WINSIZEX_NUM, WINSIZEY_NUM }, m_pRadialGradientBrush);
	}

	//밤일 경우
	else if (_state == NIGHT) {
		Rt->FillRectangle(D2D_RECT_F{ 0, 0, WINSIZEX_NUM, WINSIZEY_NUM }, m_pRadialGradientBrush);
		Rt->FillRectangle(D2D_RECT_F{ 0, 0, WINSIZEX_NUM, WINSIZEY_NUM }, m_pRadialGradientBrush);
		Rt->FillRectangle(D2D_RECT_F{ 0, 0, WINSIZEX_NUM, WINSIZEY_NUM }, m_pRadialGradientBrush);
	}
}
