#pragma once
#include "gameNode.h"
#include "Map.h"

class gameScene : public gameNode
{
private:
	Map* _map;

	//�޴� ��ư �Դϴ� (�̹��� Ŭ���� ������ ���)
	image* _stopMenuButton;
	//��ž �޴���ư�� ���� ��� â�� �߰� �� �������� �Ұ��Դϴ�
	bool _stopMenuPopUp;
	//���� �׸� ��ư, ���� �簳 ��ư�� ������ ���� �Ұ��Դϴ�
	bool _stopMenuGameBreak;
	bool _stopMenuGameResume;

public:
	gameScene();
	~gameScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//��ž �޴��� �߰� �ϴ� �Լ�(����) 

	//�ϴ��� �Ͻ����� ��ư�� �������� �Ǻ��ϴ� �Լ�
	void stopMenuUpCheck(bool& popUp, int x, int y);

	// (�޴� ��ư �̹��� ��ǥ�� ���⼭ �����ϱ� ������ �����ڸ� ����մϴ�)
	void stopMenuRender(bool popUp, int x, int y);

	//��ž �޴����� ��ư�� �������� �Ǻ��ϴ� �Լ�
	void stopMenuButtonClickCheck(bool& popUpGameStop, bool& popUpGameResume, int x1, int y1, int x2, int y2);

	//��ž �޴��� ��ư�� ����� �ϵ��� �ϴ� �Լ�
	void stopMenuButtonFunc(bool& popUpGameStop, bool& popUpGameResume, bool& popUp);
};