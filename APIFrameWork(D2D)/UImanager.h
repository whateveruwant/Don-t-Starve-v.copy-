#pragma once
#include "gameNode.h"
#include "Character.h"

class UImanager : public gameNode
{
private:
	//�� �ʸ��� ������ ������ �������� ���ϴ� �����Դϴ�
	int _timeMental;
	int _timeHunger;
	int _timeHp;

	//�׽�Ʈ��!
	int _hp;
	int _hunger;
	int _mental;

	//���ȿ� ���ٴ� ��� ���� ���� �ܿ����� �߰��� �������� �Ұ��Դϴ�
	bool _hungerPopUp;
	bool _hpPopUp;
	bool _mentalPopUp;

	//��ư�� ���콺�� ������ �˻��ϴ� �Ұ�, ��ư�� Ŭ���ߴ����� �Ұ�
	bool _onDeadPopUp;
	bool _onButton;
	bool _clickButton;

	int* day;

	//Ŭ���� ������
	Character* _charc;

public:
	UImanager();
	~UImanager();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	//���� ���� �Լ�
	void reduceHp(int& timeStat, int reduceValue);
	void reduceHunger(int& timeStat, int reduceValue);
	void reduceMental(int reduceValue, int damage);
	inline int* getTimeStateMental() { return &_timeMental; }

	//���콺�� ����â�� ���ִ��ĸ� �Ǻ��ϴ� �Լ�
	void popUpCheck(bool& popUp, int x, int y);

	//���콺�� ����â�� �������� ���� ������ �߰� �ϴ� �Լ�(����)
	void popUpNumberRender(bool popUp, int stat, int x, int y);

	//�׾��� ���� �˾��� ���콺�� ������ Ȯ���ϴ� �Լ�
	void diePopUpMouseCheck(bool onDeadPopUp, int x, int y, bool& onButton);

	//�׾��� ���� �˾��� ��ư�� ����� �����ϴ� �Լ�
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