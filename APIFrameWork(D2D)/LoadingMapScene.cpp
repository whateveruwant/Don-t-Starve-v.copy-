#include "stdafx.h"
#include "LoadingMapScene.h"


LoadingMapScene::LoadingMapScene()
{
}


LoadingMapScene::~LoadingMapScene()
{
}

HRESULT LoadingMapScene::init(void)
{
	_loading = new loading;
	_loading->init();

	this->totalLoading();
	// 파일 위치 인덱스
	/*wcscat(directory, L"image/player/");

	wcscat(directoryName[NONE_DOWN], L"_down.png");
	wcscat(directoryName[NONE_SIDE], L"_side.png");
	wcscat(directoryName[NONE_UP], L"_up.png");
	wcscat(directoryName[PRE_DOWN], L"_pre_down.png");
	wcscat(directoryName[PRE_SIDE], L"_pre_side.png");
	wcscat(directoryName[PRE_UP], L"_pre_down.png");
	wcscat(directoryName[LOOP_DOWN], L"_loop_down.png");
	wcscat(directoryName[LOOP_SIDE], L"_loop_side.png");
	wcscat(directoryName[LOOP_UP], L"_loop_up.png");
	wcscat(directoryName[PST_DOWN], L"_pst_down.png");
	wcscat(directoryName[PST_SIDE], L"_pst_side.png");
	wcscat(directoryName[PST_UP], L"_pst_up.png");*/
	return S_OK;
}

void LoadingMapScene::release(void)
{
}

void LoadingMapScene::update(void)
{
	_loading->update();
	if (_loading->loadingDone()) {
		SCENEMANAGER->changeScene("gameScene");
	}
}

void LoadingMapScene::render(void)
{
	_loading->render();
}

void LoadingMapScene::totalLoading()
{
	// Because the CreateWindow function takes its size in pixels,
	// obtain the system DPI and use it to scale the window size.
	FLOAT dpiX, dpiY;

	// The factory returns the current system DPI. This is also the value it will use
	// to create its own windows.
	Factory->GetDesktopDpi(&dpiX, &dpiY);

	// UI - 장비창 이미지 init 
	_loading->loadFrameImage(L"health", L"image/ui_health.png", 2400, 50, 50, 1);
	_loading->loadFrameImage(L"hunger", L"image/ui_hunger.png", 2400, 50, 50, 1);
	_loading->loadFrameImage(L"mental", L"image/ui_mental.png", 2400, 50, 50, 1);
	// UI - 크래프팅 창 이미지
	_loading->loadImage(L"craftingKind_1", L"image/ui_1_1.png", 29, 38);
	_loading->loadImage(L"craftingKind_2", L"image/ui_1_2.png", 29, 38);
	_loading->loadImage(L"craftingKind_3", L"image/ui_1_3.png", 29, 38);
	_loading->loadImage(L"craftingKind_4", L"image/ui_1_4.png", 29, 38);
	_loading->loadImage(L"craftingKind_5", L"image/ui_1_5.png", 29, 38);
	_loading->loadImage(L"craftingKind_6", L"image/ui_1_6.png", 29, 38);
	_loading->loadImage(L"craftingKind_7", L"image/ui_1_7.png", 29, 38);
	_loading->loadImage(L"craftingKind_8", L"image/ui_1_8.png", 29, 38);
	_loading->loadImage(L"craftingKind_9", L"image/ui_1_9.png", 29, 38);
	_loading->loadImage(L"craftingKind_10", L"image/ui_1_10.png", 29, 38);

	// 배경
	_loading->loadImage(L"ground", L"image/ground.png", WINSIZEX_NUM, WINSIZEY_NUM);

	// wake up
	_loading->loadFrameImage(L"player_wakeup", L"image/player/player_wakeup_f45.png", 4950, 100, 45, 1);

	// idle
	_loading->loadFrameImage(L"player_idle_down", L"image/player/idle/player_idle_down.png", 630, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_up", L"image/player/idle/player_idle_up.png", 630, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_left", L"image/player/idle/player_idle_left.png", 630, 100, 10, 1);
	_loading->loadFrameImage(L"player_idle_right", L"image/player/idle/player_idle_right.png", 630, 100, 10, 1);

	// run
	_loading->loadFrameImage(L"player_run_pre_down", L"image/player/run/player_run_pre_down.png", 630, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pre_right", L"image/player/run/player_run_pre_right.png", 730, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pre_left", L"image/player/run/player_run_pre_left.png", 730, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pre_up", L"image/player/run/player_run_pre_up.png", 630, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_loop_down", L"image/player/run/player_run_loop_down.png", 630, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_loop_right", L"image/player/run/player_run_loop_right.png", 780, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_loop_left", L"image/player/run/player_run_loop_left.png", 780, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_loop_up", L"image/player/run/player_run_loop_up.png", 630, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pst_down", L"image/player/run/player_run_pst_down.png", 630, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pst_right", L"image/player/run/player_run_pst_right.png", 730, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pst_left", L"image/player/run/player_run_pst_left.png", 730, 100, 10, 1);
	_loading->loadFrameImage(L"player_run_pst_up", L"image/player/run/player_run_pst_up.png", 630, 100, 10, 1);
	// item
	//IMAGEMANAGER->addFrameImage(Rt, L"player_idle_down", L"image/player/idle/player_idle_down", 630, 100, 10, 1);
	//IMAGEMANAGER->addFrameImage(Rt, L"player_idle_down", L"image/player/idle/player_idle_down", 630, 100, 10, 1);
	//IMAGEMANAGER->addFrameImage(Rt, L"player_idle_down", L"image/player/idle/player_idle_down", 630, 100, 10, 1);
}
