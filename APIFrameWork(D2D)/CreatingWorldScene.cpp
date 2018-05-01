#include "stdafx.h"
#include "CreatingWorldScene.h"


CreatingWorldScene::CreatingWorldScene()
{
}


CreatingWorldScene::~CreatingWorldScene()
{
}

HRESULT CreatingWorldScene::init(void)
{
	//크리에이팅 월드 이미지
	IMAGEMANAGER->addImage(Rt, L"pureBackground", L"image/pureBackground.png", WINSIZEX_NUM, WINSIZEY_NUM);
	IMAGEMANAGER->addFrameImage(Rt, L"handRight", L"image/handRight.png", 4040, 209, 20, 1);
	IMAGEMANAGER->addFrameImage(Rt, L"handLeft", L"image/handLeft.png", 4040, 209, 20, 1);
	IMAGEMANAGER->addFrameImage(Rt, L"world", L"image/world.png", 12440, 3155, 20, 5);
	IMAGEMANAGER->addFrameImage(Rt, L"creatingText", L"image/createtext.png", 1800, 80, 3, 1);
	//크리에이팅 월드 사운드
	SOUNDMANAGER->addSound("GenWorldSound", "sounds/GenWorld_LP.mp3", false, true);
	SOUNDMANAGER->bgmPlay("GenWorldSound", 0.4f);
	

	m_tiles->init();
	
	mLoading = new loading;
	mLoading->init();

	this->totalLoading();

	count = frameX_hand = frame_world = frame_text = 0;
	return S_OK;
}

void CreatingWorldScene::release(void)
{
}

void CreatingWorldScene::update(void)
{
	count++;
	if (count % 2 == 0) {
		frameX_hand++;
		if (frameX_hand == 20) {
			frameX_hand = 0;
		}
	}
	if (count % 2 == 0) {
		frame_world++;
		if (frame_world == 100) {
			frame_world = 0;
		}
	}
	if (count % 50 == 0) {
		frame_text++;
		if (frame_world == 1000) {
			frame_text = 0;
		}
	}
	mLoading->update();
	if(mLoading->loadingDone())
	if (m_tiles->generatorDone() ) {
		SOUNDMANAGER->stop("GenWorldSound");
		SCENEMANAGER->changeScene("loadingGame");
	}
}

void CreatingWorldScene::render(void)
{
	IMAGEMANAGER->render(L"pureBackground", Rt);
	IMAGEMANAGER->frameRender(L"handRight", Rt, WINSIZEX_NUM - 435, WINSIZEY_NUM - 200, frameX_hand, 0);
	IMAGEMANAGER->frameRender(L"handLeft", Rt, 265, WINSIZEY_NUM - 200, frameX_hand, 0);
	IMAGEMANAGER->frameRender(L"world", Rt, 400, WINSIZEY_NUM - 400, frame_world % 20, frame_world / 20);
	IMAGEMANAGER->frameRender(L"creatingText", Rt, WINSIZEX_NUM / 2 - 220, WINSIZEY_NUM / 4 - 40, frame_text, 0);
}
void CreatingWorldScene::totalLoading() {
	for (int i = 0; i < 200; i++) {
		mLoading->loadImage(L"test", L"image/block.png", 0, 0);
	}
}