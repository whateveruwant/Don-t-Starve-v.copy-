#pragma once
#include "gameNode.h"
#include "Map.h"

class gameScene : public gameNode
{
private:
	Map* _map;

	//메뉴 버튼 입니다 (이미지 클래스 포인터 사용)
	image* _stopMenuButton;
	//스탑 메뉴버튼을 누를 경우 창이 뜨게 할 것인지의 불값입니다
	bool _stopMenuPopUp;
	//게임 그만 버튼, 게임 재개 버튼을 눌렀을 때의 불값입니다
	bool _stopMenuGameBreak;
	bool _stopMenuGameResume;

public:
	gameScene();
	~gameScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//스탑 메뉴를 뜨게 하는 함수(렌더) 

	//하단의 일시정지 버튼을 눌렀는지 판별하는 함수
	void stopMenuUpCheck(bool& popUp, int x, int y);

	// (메뉴 버튼 이미지 좌표를 여기서 설정하기 때문에 참조자를 사용합니다)
	void stopMenuRender(bool popUp, int x, int y);

	//스탑 메뉴안의 버튼을 눌렀는지 판별하는 함수
	void stopMenuButtonClickCheck(bool& popUpGameStop, bool& popUpGameResume, int x1, int y1, int x2, int y2);

	//스탑 메뉴의 버튼이 기능을 하도록 하는 함수
	void stopMenuButtonFunc(bool& popUpGameStop, bool& popUpGameResume, bool& popUp);
};