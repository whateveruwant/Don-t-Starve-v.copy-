#pragma once
#include "gameNode.h"

class SelectCharacterScene : public gameNode
{
private:
	//윌슨 버튼이 눌렸는지 검사하는 불값입니다
	bool _onSelectWilson;
	//마우스가 yesbutton 안에 있는지 확인하는 불값입니다
	bool _onSelectYesButton;
	//마우스가 nobutton 안에 있는지 확인하는 불값입니다
	bool _onSelectNoButton;
	//yesbutton을 클릭했는지 확인하는 불값입니다
	bool _clickSelectYesButton;
	//nobutton을 클릭했는지 확인하는 불값입니다
	bool _clickSelectNoButton;

public:
	SelectCharacterScene();
	~SelectCharacterScene();

	HRESULT init();
	void release();
	void update();
	void render();

	//윌슨 이미지에 클릭이 되었는지를 체크하는 함수입니다
	void selectWilsonCheck(bool& onSelectWilson, int x, int y);

	//yes버튼, no버튼에 마우스가 갔는지 체크하는 함수입니다
	void buttonCheck(bool& onSelectNoButton, bool& onSelectYesButton, int x1, int y1, int x2, int y2);

	//yes버튼, no버튼을 눌렀는지 체크하는 함수입니다
	void buttonClick(bool& clickSelectNoButton, bool& clickSelectYesButton, int x1, int y1, int x2, int y2);
};

