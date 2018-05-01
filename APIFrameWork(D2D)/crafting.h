#pragma once
#include "gameNode.h"
#include "Inventory.h"
#include "ItemInfo.h"

struct tagItemMethod {
	EOBJECT_IN_INVENTORY_KIND _final;         //결과물
	EOBJECT_IN_INVENTORY_KIND _source1;         //준비물1
	int _sourcenum1;                     //준비물1 갯수
	EOBJECT_IN_INVENTORY_KIND _source2;         //준비물2
	int _sourcenum2;                     //준비물2 갯수
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

	//왼쪽 유아이(크래프팅) 버튼의 구조체입니다
	tagButton _fButton[10];      //first
	tagSButton _sButton_kind[10];   //도끼, 곡괭이, 모닥불, 화덕, 횃불, 가방, 상자, 밧줄, 목재, 석재 순서

	tagItemMethod _finalItems[10];

	bool _CanCreate[10];			//재료가 있을때 만들수 있을지 없을지 확인하는 불값
	bool _isCreateClick[10];		//크래프트 최종 팝업의 만들기 버튼을 클릭했는지 검사하는 불값

	bool _isPlayerClickCrafting_first;
	bool _isPlayerClickCrafting_second;
public:
	Crafting();
	~Crafting();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//버튼안에 마우스가 들어왔는지 체크하는 함수입니다
	void firstButtonCheck(bool& isCheck, int x, int y);
	//버튼이 클릭되었는지 확인하는 함수입니다
	void firstButtonClick(bool& isClick, int x, int y);
	//버튼을 렌더하는 함수입니다
	void firstButtonRender();
	void secondButtonRender();

	//도끼, 곡괭이 등(두번째 버튼칸)을 눌렀을때를 체크하는 함수입니다
	void secondButtonClick(bool firstIsClick, int x, int y, bool& secondIsClick);

	//버튼을 렌더하는 함수입니다
	void thirdButtonRender();

	//상호참조를 쓰기위헤 메모리 링크를 사용합니다
	void setInvenMemoryRick(Inventory* invClon) { _invClon = invClon; }

	//만들 가공품의 정보가 들어있는 함수입니다
	void finalItemInit();
	// 생성할 재료들이 있는 것들을 true로 바꿉니다
	void checkCreate();

	//크레이팅 만들기를 클릭했을 경우
	void thirdButtonClick(int x, int y);

	//왼쪽 크래프팅 칸이 눌렸는지 검사하는 함수 => 플레이어가 그 범위를 못지나가게 하기 위해(플레이어에서 범위판단)
	void checkisPlayerClickfirst() {
		for (int i = 0; i < 10; ++i) {
			if (_fButton[i].isClick == true) {
				_isPlayerClickCrafting_first = true;
				return;
			}
			_isPlayerClickCrafting_first = false;
		}
	}

	//왼쪽 크래프팅 두번째 칸이 눌렸는지 검사하는 함수 => 플레이어가 그 범위를 못지나가게 하기 위해(플레이어에서 범위판단)
	void checkisPlayerClicksecond() {
		for (int i = 0; i < 10; ++i) {
			if (_sButton_kind[i].isClick == true) {
				_isPlayerClickCrafting_second = true;
				return;
			}
			_isPlayerClickCrafting_second = false;
		}
	}

	//누를 수 있는 범위를 설정하는 함수입니다(캐릭터의 스위치 케이스문을 사용하기 위하여)
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