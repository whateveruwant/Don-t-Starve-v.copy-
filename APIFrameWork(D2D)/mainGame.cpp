#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

HRESULT mainGame::init(void)
{
	gameNode::init(true);
	SCENEMANAGER->addScene("loadingMain", new LoadingMainScene);
	SCENEMANAGER->addScene("loadingGame", new LoadingGameScene);
	SCENEMANAGER->addScene("createWorld", new CreatingWorldScene);
	SCENEMANAGER->addScene("menuScene", new menuScene);
	SCENEMANAGER->addScene("maptoolScene", new MaptoolScene);
	SCENEMANAGER->addScene("selectScene", new SelectCharacterScene);
	SCENEMANAGER->addScene("gameScene", new gameScene);
	SCENEMANAGER->changeScene("loadingMain");
	return S_OK;
}

void mainGame::release(void)
{
	gameNode::release();
}

void mainGame::update(void)
{
	gameNode::update();
	SOUNDMANAGER->update();
	SCENEMANAGER->update();
}

void mainGame::render(void)
{

	Rt->BeginDraw();
	Rt->SetTransform(D2D1::Matrix3x2F::Identity());
	Rt->Clear();

	D2D1_RECT_F rect = D2D1::RectF(0, 0, WINSIZEX_NUM, WINSIZEY_NUM);
	//==================================================================
	SCENEMANAGER->render();
	
	//TCHAR _point[20];
	//wsprintf(_point, L"%d,%d", (int)_ptMouse.x, (int)_ptMouse.y);
	//D2TextOut(Rt, _point, TextFormat, D2D1::RectF(0, 15, 500, 15), Brush);
	//==================================================================
	Rt->EndDraw();

	gameNode::render();
}