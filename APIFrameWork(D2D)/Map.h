#pragma once
#include "gameNode.h"
#include "Objects.h"
#include "Tiles.h"
#include "Character.h"
#include "Inventory.h"
#include "UImanager.h"
#include "Crafting.h"
#include "Clock.h"

struct tagCollision {
	D2D_RECT_F rc;
	POINT mAbsPt;
	EOBJKIND_ENVIRONMENT kindEnvi;
	EOBJKIND_MATERIAL kindMate;
	int index;
};

//클릭한 아이템의 정보
struct tagClickItem {
	bool _isClick;
	OBJECT_IN_INVENTORY _item;
	int previndex;
};

class Map : public gameNode
{
private:

	Character* _character;
	UImanager* _uimanager;
	Inventory* _inventory;
	Crafting* _craft;
	Clock* _clock;

	CHARACTER_ACTION mCharcterAction;
	EOBJ_ENVIRONMENT_STATE stateEnvi;
	EOBJ_ENVIRONMENT_STATE stateMate;

	POINT collisionPt;
	vector<tagCollision> vCollision;
	EOBJKIND_ENVIRONMENT selectObjEnvi;
	EOBJKIND_MATERIAL selectObjMate;
	POINT mouseClickObj;

	vector<OBJECT_FIRE*> mObjFire;
	vector<OBJECT_STORAGE*> mObjStorage;

	tagClickItem _drawItem;

	int zOderY;
	bool _showRect;
public:
	Map();
	~Map();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void isCollisionEnvi();
	void isCollisionMate();
	void collisionRectDraw();

	// 
	void mouseClick();
	// 
	void objUpdate();

	//인벤토리 아이템 사용 그에 따른 효과
	void checkUseItem();

	//멘탈 감소함수
	void CheckDropMental();

	//Z오더 검사 함수
	void zOderCheck();
};