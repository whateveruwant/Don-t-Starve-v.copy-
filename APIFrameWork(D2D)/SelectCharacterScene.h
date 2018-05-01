#pragma once
#include "gameNode.h"

class SelectCharacterScene : public gameNode
{
private:
	//���� ��ư�� ���ȴ��� �˻��ϴ� �Ұ��Դϴ�
	bool _onSelectWilson;
	//���콺�� yesbutton �ȿ� �ִ��� Ȯ���ϴ� �Ұ��Դϴ�
	bool _onSelectYesButton;
	//���콺�� nobutton �ȿ� �ִ��� Ȯ���ϴ� �Ұ��Դϴ�
	bool _onSelectNoButton;
	//yesbutton�� Ŭ���ߴ��� Ȯ���ϴ� �Ұ��Դϴ�
	bool _clickSelectYesButton;
	//nobutton�� Ŭ���ߴ��� Ȯ���ϴ� �Ұ��Դϴ�
	bool _clickSelectNoButton;

public:
	SelectCharacterScene();
	~SelectCharacterScene();

	HRESULT init();
	void release();
	void update();
	void render();

	//���� �̹����� Ŭ���� �Ǿ������� üũ�ϴ� �Լ��Դϴ�
	void selectWilsonCheck(bool& onSelectWilson, int x, int y);

	//yes��ư, no��ư�� ���콺�� ������ üũ�ϴ� �Լ��Դϴ�
	void buttonCheck(bool& onSelectNoButton, bool& onSelectYesButton, int x1, int y1, int x2, int y2);

	//yes��ư, no��ư�� �������� üũ�ϴ� �Լ��Դϴ�
	void buttonClick(bool& clickSelectNoButton, bool& clickSelectYesButton, int x1, int y1, int x2, int y2);
};

