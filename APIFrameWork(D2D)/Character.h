#pragma once
#include "gameNode.h"
//#include "Map.h"

#define CHARACTER_SPEED 2

// 캐릭터 이동 방향
enum CHARACTER_DIR {
	DOWN,
	UP,
	LEFT,
	RIGHT
};

// 캐릭터 움직임 상태
enum CHARACTER_ACTION {
	// ACTION
	WAKEUP,
	EAT,
	HUNGRY,
	DEATH,
	ITEM_IN,
	ITEM_OUT,
	ACTION_BUILD,
	ACTION_FX,
	ACTION_PICKUP,
	//IDLE
	IDLE,
	IDLE_SANITY,
	IDLE_TORCH,
	// RUN
	RUN,
	RUN_TORCH,
	//USE ITEM
	ACTION_AXE,
	ACTION_PICKAXE,
};
// 캐릭터 움직임 순서
enum CHARACTER_ORDER {
	NONE_ORDER,
	NONE_DOWN,
	NONE_RIGHT,
	NONE_LEFT,
	NONE_UP,
	PRE_DOWN,
	PRE_RIGHT,
	PRE_LEFT,
	PRE_UP,
	LOOP_DOWN,
	LOOP_RIGHT,
	LOOP_LEFT,
	LOOP_UP,
	PST_DOWN,
	PST_RIGHT,
	PST_LEFT,
	PST_UP
};

class Character : public gameNode
{
private:
	CHARACTER_DIR _dir;
	tstring character_action[16];
	tstring character_order[17];
	tstring tmp;

	CHARACTER_ORDER eOrder;
	CHARACTER_ACTION eAction;

	bool isWalk;
	bool isOpening;
	bool isKeyUp;
	bool isKeyDown;
	bool isKeyLeft;
	bool isKeyRight;
	bool isActionWork;
	bool isTorch;
	int triCount;

	int count;
	POINT _position;				// int characterX, characterY;
	POINT mousePt;
	int frameX, frameY;

public:
	Character();
	~Character();

	HRESULT init(void);
	void release(void);
	void update(CHARACTER_ACTION mCharcterAction);
	void update();
	void render(void);

	void setIsTorch(bool _isTorch) { isTorch = _isTorch; }
	POINT* getPointerPosition() { return &_position; }
	CHARACTER_ACTION getCharacterAction() { return eAction; }
	bool getIsActionWork() { return isActionWork; }

	void keyInput();

	void move();
	//void selectAction(CHARACTER_ACTION mCharcterAction);
	void selectAction();
};