#pragma once
#include "gameNode.h"
#include "Objects.h"

class Inventory : public gameNode
{
private:
	OBJECT_IN_INVENTORY _Items[IVENTORYMAX];
	bool _isBag;

	OBJECT_IN_INVENTORY _usingItems[2];


	int torchTime;
public:
	Inventory();
	~Inventory();

	HRESULT init();
	void release();
	void update();
	void render();

	bool saveObject(EOBJECT_IN_INVENTORY_KIND _obj);
	bool resaveObject(OBJECT_IN_INVENTORY _obj);

	inline OBJECT_IN_INVENTORY* loadObject() { return _Items; }
	void useItem(OBJECT_IN_INVENTORY _item);
	void deleteObjects(EOBJECT_IN_INVENTORY_KIND _obj, int num);

	inline void setIsBag(bool isBag) { _isBag = isBag; }
	inline bool getIsBag() { return _isBag; }

	inline OBJECT_IN_INVENTORY getHandItem() { return _usingItems[0]; }
	void reduceNum(int index, int damage); // 내구도 줄여주는것

	void deleteByindex(int index) {
		_Items[index]._kind = EII_NONE;
		_Items[index]._num = NULL;
	}
	void reduceByindexandNum(int index, int num) {
		_Items[index]._num -= num;
		if (_Items[index]._num <= 0) {
			_Items[index]._kind = EII_NONE;
			_Items[index]._num = NULL;
		}
	}
	void saveByindex(int index, OBJECT_IN_INVENTORY obj) {
		SOUNDMANAGER->play("getItem");
		_Items[index]._kind = obj._kind;
		_Items[index]._num = obj._num;
	}
};