#pragma once
#include "gameNode.h"

enum ECLOCKSTATE { AFTERNOON, EVENING, NIGHT };

class Clock : public gameNode
{
private:
	//세계 날짜를 저장하는 변수
	int _day;

	//getWorldTime()을 int값으로 받아 저장하는 변수, 현재 시간 변수
	int _timetmp;
	int _time;

	int _timeFrameX;
	int _countFrame;

	//현재 맵의 상태를 나타내는 enum 구조체
	ECLOCKSTATE _state;

public:
	Clock();
	~Clock();

	HRESULT init();
	void release();
	void update();
	void render();

	//실제 시간->게임 시간으로 변환하는 함수입니다(interval : 실제시간 몇 초마다 게임시간으로 변환할지)
	// (timetmp, time, day는 값이 바뀌므로 참조자 사용)
	void gameTimeConv(int interval, int& timetmp, int& time, int& day);

	//낮, 저녁, 밤을 판별해주는 함수입니다(state값을 바꾸기때문에 참조자 사용)
	void whatState(ECLOCKSTATE& state, int time);

	//시계의 뒷면을 프레임 렌더하기 위한 함수입니다
	// (timeFrameX의 값이 바뀌므로 참조자 사용)
	void clockFrameFunc(int& timeFrameX);

	//숫자가 현재 day값에 따라 렌더하기 위한 함수입니다
	void dayNumberRender(int day, int x, int y);

	ECLOCKSTATE getClockState() { return _state; }
	int& getDay() { return _day; }
	//현재 state(낮, 저녁, 밤)에 따른 현상을 관리하는 함수입니다
	void filterRender();
};
