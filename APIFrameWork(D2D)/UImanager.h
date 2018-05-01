#pragma once
#include "gameNode.h"
#include "Character.h"

class UImanager : public gameNode
{
private:
	//몇 초마다 스탯이 떨어질 것인지를 정하는 변수입니다
	int _timeMental;
	int _timeHunger;
	int _timeHp;

	//테스트용!
	int _hp;
	int _hunger;
	int _mental;

	//스탯에 갖다댈 경우 현재 스탯 잔여량이 뜨게할 것인지의 불값입니다
	bool _hungerPopUp;
	bool _hpPopUp;
	bool _mentalPopUp;

	//버튼에 마우스가 갔는지 검사하는 불값, 버튼을 클릭했는지의 불값
	bool _onDeadPopUp;
	bool _onButton;
	bool _clickButton;

	int* day;

	//클래스 포인터
	Character* _charc;

public:
	UImanager();
	~UImanager();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	//스탯 감소 함수
	void reduceHp(int& timeStat, int reduceValue);
	void reduceHunger(int& timeStat, int reduceValue);
	void reduceMental(int reduceValue, int damage);
	inline int* getTimeStateMental() { return &_timeMental; }

	//마우스가 스탯창에 가있느냐를 판별하는 함수
	void popUpCheck(bool& popUp, int x, int y);

	//마우스가 스탯창에 가있으면 현재 스탯을 뜨게 하는 함수(렌더)
	void popUpNumberRender(bool popUp, int stat, int x, int y);

	//죽었을 때의 팝업에 마우스가 갔는지 확인하는 함수
	void diePopUpMouseCheck(bool onDeadPopUp, int x, int y, bool& onButton);

	//죽었을 때의 팝업의 버튼의 기능을 관리하는 함수
	void diePopUpButtonFunc(bool onDeadPopUp, int x, int y, bool& clickButton);

	inline void setDay(int& _day) { day = &_day; }
	inline void setHunger(int hunger) { _hunger = hunger; }
	inline void setHp(int hp) { _hp = hp; }
	inline void setMental(int mental) { _mental = mental; }

	inline void upHunger() { if (_hunger < 50) { _hunger += 1; SOUNDMANAGER->play("hungerUp", 0.1f); } }
	inline void upHp() { if (_hp < 50) { _hp += 1; SOUNDMANAGER->play("hpUp", 0.1f); } }
	inline void upMental() { if (_mental < 50) { _mental += 1; SOUNDMANAGER->play("mentalUp", 0.1f); } }

	inline void damageHunger(int damage) { _hunger -= damage; SOUNDMANAGER->play("hungerDown", 0.1f); if (_hunger < 0) _hunger = 0; }
	inline void damageHp(int damage) { _hp -= damage;  SOUNDMANAGER->play("hpDown", 0.1f); if (_hp < 0) _hp = 0; IMAGEMANAGER->findImage(L"playerdamage")->setAlpha(1.0f); }
	inline void damageMental(int damage) { _mental -= damage;  SOUNDMANAGER->play("mentalDown", 0.1f); if (_mental < 0) _mental = 0; }

	inline void setCharcMemoryRick(Character* charc) { _charc = charc; }
};