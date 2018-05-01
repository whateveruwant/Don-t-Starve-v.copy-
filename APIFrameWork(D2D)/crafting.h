#pragma once
#include "gameNode.h"
#include "Inventory.h"
#include "ItemInfo.h"

struct tagItemMethod {
	EOBJECT_IN_INVENTORY_KIND _final;         //�����
	EOBJECT_IN_INVENTORY_KIND _source1;         //�غ�1
	int _sourcenum1;                     //�غ�1 ����
	EOBJECT_IN_INVENTORY_KIND _source2;         //�غ�2
	int _sourcenum2;                     //�غ�2 ����
};

struct tagButton {
	bool isCheck;
	bool isClick;
	int x, y;
};

struct tagSButton {
	bool isClick;
	int x, y;
};

class Crafting : public gameNode
{
private:
	bool _isOpen;

	Inventory* _invClon;

	//���� ������(ũ������) ��ư�� ����ü�Դϴ�
	tagButton _fButton[10];      //first
	tagSButton _sButton_kind[10];   //����, ���, ��ں�, ȭ��, ȶ��, ����, ����, ����, ����, ���� ����

	tagItemMethod _finalItems[10];

	bool _CanCreate[10];			//��ᰡ ������ ����� ������ ������ Ȯ���ϴ� �Ұ�
	bool _isCreateClick[10];		//ũ����Ʈ ���� �˾��� ����� ��ư�� Ŭ���ߴ��� �˻��ϴ� �Ұ�

	bool _isPlayerClickCrafting_first;
	bool _isPlayerClickCrafting_second;
public:
	Crafting();
	~Crafting();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//��ư�ȿ� ���콺�� ���Դ��� üũ�ϴ� �Լ��Դϴ�
	void firstButtonCheck(bool& isCheck, int x, int y);
	//��ư�� Ŭ���Ǿ����� Ȯ���ϴ� �Լ��Դϴ�
	void firstButtonClick(bool& isClick, int x, int y);
	//��ư�� �����ϴ� �Լ��Դϴ�
	void firstButtonRender();
	void secondButtonRender();

	//����, ��� ��(�ι�° ��ưĭ)�� ���������� üũ�ϴ� �Լ��Դϴ�
	void secondButtonClick(bool firstIsClick, int x, int y, bool& secondIsClick);

	//��ư�� �����ϴ� �Լ��Դϴ�
	void thirdButtonRender();

	//��ȣ������ �������� �޸� ��ũ�� ����մϴ�
	void setInvenMemoryRick(Inventory* invClon) { _invClon = invClon; }

	//���� ����ǰ�� ������ ����ִ� �Լ��Դϴ�
	void finalItemInit();
	// ������ ������ �ִ� �͵��� true�� �ٲߴϴ�
	void checkCreate();

	//ũ������ ����⸦ Ŭ������ ���
	void thirdButtonClick(int x, int y);

	//���� ũ������ ĭ�� ���ȴ��� �˻��ϴ� �Լ� => �÷��̾ �� ������ ���������� �ϱ� ����(�÷��̾�� �����Ǵ�)
	void checkisPlayerClickfirst() {
		for (int i = 0; i < 10; ++i) {
			if (_fButton[i].isClick == true) {
				_isPlayerClickCrafting_first = true;
				return;
			}
			_isPlayerClickCrafting_first = false;
		}
	}

	//���� ũ������ �ι�° ĭ�� ���ȴ��� �˻��ϴ� �Լ� => �÷��̾ �� ������ ���������� �ϱ� ����(�÷��̾�� �����Ǵ�)
	void checkisPlayerClicksecond() {
		for (int i = 0; i < 10; ++i) {
			if (_sButton_kind[i].isClick == true) {
				_isPlayerClickCrafting_second = true;
				return;
			}
			_isPlayerClickCrafting_second = false;
		}
	}

	//���� �� �ִ� ������ �����ϴ� �Լ��Դϴ�(ĳ������ ����ġ ���̽����� ����ϱ� ���Ͽ�)
	int getRange() {
		if (_isPlayerClickCrafting_first && !_isPlayerClickCrafting_second) {
			return 1;
		}
		else if (_isPlayerClickCrafting_second) {
			return 2;
		}
		else {
			return 0;
		}
	}
};