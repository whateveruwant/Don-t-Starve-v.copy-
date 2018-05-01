#include "stdafx.h"
#include "Inventory.h"


Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

HRESULT Inventory::init()
{
	_isBag = false;

	for (int i = 0; i < IVENTORYMAX; ++i) {
		_Items[i]._kind = EOBJECT_IN_INVENTORY_KIND::EII_NONE;
		_Items[i]._num = NULL;
	}

	for (int i = 0; i < 2; ++i) {
		_usingItems[i]._kind = EOBJECT_IN_INVENTORY_KIND::EII_NONE;
		_usingItems[i]._num = NULL;
	}

	torchTime = 0;
	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	if (KEYMANAGER->isOnceKeyDown('1')) {
		saveObject(EOBJECT_IN_INVENTORY_KIND::EII_FLINT);
	}
	if (KEYMANAGER->isOnceKeyDown('2')) {
		saveObject(EOBJECT_IN_INVENTORY_KIND::EII_HAY);
	}
	if (KEYMANAGER->isOnceKeyDown('3')) {
		saveObject(EOBJECT_IN_INVENTORY_KIND::EII_AXE);
	}
	if (KEYMANAGER->isOnceKeyDown('4')) {
		saveObject(EOBJECT_IN_INVENTORY_KIND::EII_BAG);
	}
	if (KEYMANAGER->isOnceKeyDown('5')) {
		saveObject(EOBJECT_IN_INVENTORY_KIND::EII_LEAF);
	}
	if (KEYMANAGER->isOnceKeyDown('6')) {
		saveObject(EOBJECT_IN_INVENTORY_KIND::EII_BRANCH);
	}
	if (KEYMANAGER->isOnceKeyDown('7')) {
		saveObject(EOBJECT_IN_INVENTORY_KIND::EII_CARROT);
	}
	if (KEYMANAGER->isOnceKeyDown('8')) {
		saveObject(EOBJECT_IN_INVENTORY_KIND::EII_BONFIRE);
	}
	if (KEYMANAGER->isOnceKeyDown('9')) {
		saveObject(EOBJECT_IN_INVENTORY_KIND::EII_STORAGE);
	}
	if (KEYMANAGER->isOnceKeyDown('0')) {
		saveObject(EOBJECT_IN_INVENTORY_KIND::EII_FIREPIT);
	}


	//횃불 내구도 자동감소
	if (_usingItems[0]._kind == EII_TORCH) {
		if ((int)TIMEMANAGER->getWorldTime() % 1 == 0 && (int)TIMEMANAGER->getWorldTime() != torchTime) {
			torchTime = (int)TIMEMANAGER->getWorldTime();
			reduceNum(0, 2);
		}
	}

	if (_usingItems[1]._kind == EII_BAG) {
		_isBag = true;
	}
	else{
		_isBag = false;
	}
}

void Inventory::render()
{
	IMAGEMANAGER->render(L"invenMenu", Rt, 259, 673);

	for (int i = 0; i < 5; i++)
	{
		IMAGEMANAGER->render(L"invenBox", Rt, 290 + i * 38, 689);   // 가로 32 + 간격 6
	}

	for (int i = 0; i < 5; i++)
	{
		IMAGEMANAGER->render(L"invenBox", Rt, 489 + i * 38, 689);   // 가로 32 + 간격 6
	}

	for (int i = 0; i < 5; i++)
	{
		IMAGEMANAGER->render(L"invenBox", Rt, 684 + i * 38, 689);   // 가로 32 + 간격 6
	}

	IMAGEMANAGER->render(L"invenHandBox", Rt, 881, 689);
	IMAGEMANAGER->render(L"invenArmorBox", Rt, 919, 689);
	IMAGEMANAGER->render(L"invenHelmetBox", Rt, 957, 689);


	//인벤토리 아이템 렌더
	for (int i = 0; i < 15; ++i) {
		if (i < 5) {
			IMAGEMANAGER->frameRender(L"ui_items", Rt, 290 + i * 38, 689, _Items[i]._kind - 1, 0);
			if (_Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_NONE || _Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BAG || _Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_STORAGE || _Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_FIREPIT || _Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BONFIRE) continue;
			int tmp = _Items[i]._num;
			int count = 0;
			while (tmp != 0) {
				count++;
				IMAGEMANAGER->frameRender(L"inventory_number", Rt, 307 + i * 38 - 9 * count, 690, tmp % 10, 0);
				tmp /= 10;
			}
			if (count == 0) {
				IMAGEMANAGER->frameRender(L"inventory_number", Rt, 307 + i * 38, 690, 0, 0);
			}
		}
		else if (i < 10) {
			IMAGEMANAGER->frameRender(L"ui_items", Rt, 489 + (i - 5) * 38, 689, _Items[i]._kind - 1, 0);
			if (_Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_NONE || _Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BAG || _Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_STORAGE || _Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_FIREPIT || _Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BONFIRE) continue;
			int tmp = _Items[i]._num;
			int count = 0;
			while (tmp != 0) {
				count++;
				IMAGEMANAGER->frameRender(L"inventory_number", Rt, 506 + (i - 5) * 38 - 9 * count, 690, tmp % 10, 0);
				tmp /= 10;
			}
			if (count == 0) {
				IMAGEMANAGER->frameRender(L"inventory_number", Rt, 506 + (i - 5) * 38, 690, 0, 0);
			}
		}
		else {
			IMAGEMANAGER->frameRender(L"ui_items", Rt, 684 + (i - 10) * 38, 689, _Items[i]._kind - 1, 0);
			if (_Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_NONE || _Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BAG || _Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_STORAGE || _Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_FIREPIT || _Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BONFIRE) continue;
			int tmp = _Items[i]._num;
			int count = 0;
			while (tmp != 0) {
				count++;
				IMAGEMANAGER->frameRender(L"inventory_number", Rt, 701 + (i - 10) * 38 - 9 * count, 690, tmp % 10, 0);
				tmp /= 10;
			}
			if (count == 0) {
				IMAGEMANAGER->frameRender(L"inventory_number", Rt, 701 + (i - 10) * 38, 690, 0, 0);
			}
		}
	}

	if (_isBag) {
		//이미지 띄우기
		IMAGEMANAGER->render(L"backpack_on", Rt, 1153, 478);
		for (int i = 0; i < 3; ++i) {
			IMAGEMANAGER->frameRender(L"ui_items", Rt, 1200 - 34, 488 + i * 34, _Items[i + 15]._kind - 1, 0);
			if (_Items[i + 15]._kind == EOBJECT_IN_INVENTORY_KIND::EII_NONE || _Items[i + 15]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BAG || _Items[i + 15]._kind == EOBJECT_IN_INVENTORY_KIND::EII_STORAGE || _Items[i + 15]._kind == EOBJECT_IN_INVENTORY_KIND::EII_FIREPIT || _Items[i + 15]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BONFIRE) continue;
			int tmp = _Items[i + 15]._num;
			int count = 0;
			while (tmp != 0) {
				count++;
				IMAGEMANAGER->frameRender(L"inventory_number", Rt, 1217 - 34 - 9 * count, 489 + i * 34, tmp % 10, 0);
				tmp /= 10;
			}
			if (count == 0) {
				IMAGEMANAGER->frameRender(L"inventory_number", Rt, 1217 - 34, 489 + i * 34, 0, 0);
			}
		}
		for (int i = 0; i < 3; ++i) {
			IMAGEMANAGER->frameRender(L"ui_items", Rt, 1200, 488 + i * 34, _Items[i + 18]._kind - 1, 0);
			if (_Items[i + 18]._kind == EOBJECT_IN_INVENTORY_KIND::EII_NONE || _Items[i + 18]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BAG || _Items[i + 18]._kind == EOBJECT_IN_INVENTORY_KIND::EII_STORAGE || _Items[i + 18]._kind == EOBJECT_IN_INVENTORY_KIND::EII_FIREPIT || _Items[i + 18]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BONFIRE) continue;
			int tmp = _Items[i + 18]._num;
			int count = 0;
			while (tmp != 0) {
				count++;
				IMAGEMANAGER->frameRender(L"inventory_number", Rt, 1217 - 9 * count, 489 + i * 34, tmp % 10, 0);
				tmp /= 10;
			}
			if (count == 0) {
				IMAGEMANAGER->frameRender(L"inventory_number", Rt, 1217, 489 + i * 34, 0, 0);
			}
		}
	}

	for (int i = 0; i < 2; ++i) {
		IMAGEMANAGER->frameRender(L"ui_items", Rt, 879 + i * 38, 689, _usingItems[i]._kind - 1, 0);
		if (_usingItems[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_NONE || _usingItems[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BAG || _usingItems[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_STORAGE || _usingItems[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_FIREPIT || _usingItems[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BONFIRE) continue;
		int tmp = _usingItems[i]._num;
		int count = 0;
		while (tmp != 0) {
			count++;
			IMAGEMANAGER->frameRender(L"inventory_number", Rt, 896 + i * 38 - 9 * count, 690, tmp % 10, 0);
			tmp /= 10;
		}
		if (count == 0) {
			IMAGEMANAGER->frameRender(L"inventory_number", Rt, 896 + i * 38, 690, 0, 0);
		}
	}
}

bool Inventory::saveObject(EOBJECT_IN_INVENTORY_KIND _obj)
{
	int _inventorySize;
	if (_isBag) {
		_inventorySize = IVENTORYMAX;
	}
	else _inventorySize = 15;

	for (int i = 0; i < _inventorySize; ++i) { // 추가시킬 아이템이 내 인벤토리 안에 존재하냐?
		if (_Items[i]._kind == _obj && _Items[i]._kind != EII_AXE && _Items[i]._kind != EII_PICKAX/*곡괭이*/&& _Items[i]._kind != EII_TORCH/*횃불*/ && _Items[i]._kind != EII_BAG && _Items[i]._kind != EII_STORAGE && _Items[i]._kind != EII_FIREPIT && _Items[i]._kind != EII_BONFIRE) {
			_Items[i]._num++;
			SOUNDMANAGER->play("getItem", 0.5f);
			return true;
		}
	}

	for (int i = 0; i < _inventorySize; ++i) {
		if (_Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_NONE) {
			_Items[i]._kind = _obj;
			if (_Items[i]._kind == EII_AXE || _Items[i]._kind == EII_PICKAX/*곡괭이*/ || _Items[i]._kind == EII_TORCH/*횃불*/) {
				_Items[i]._num = 100;
			}
			else {
				_Items[i]._num = 1;
			}
			SOUNDMANAGER->play("getItem", 0.5f);
			return true;
		}
	}
	return false;
}

bool Inventory::resaveObject(OBJECT_IN_INVENTORY _obj)
{
	int _inventorySize;
	if (_isBag) {
		_inventorySize = IVENTORYMAX;
	}
	else _inventorySize = 15;

	for (int i = 0; i < _inventorySize; ++i) {
		if (_Items[i]._kind == EOBJECT_IN_INVENTORY_KIND::EII_NONE) {
			_Items[i]._kind = _obj._kind;
			_Items[i]._num = _obj._num;
			return true;
		}
		else if (_Items[i]._kind == _obj._kind && _Items[i]._kind != EII_AXE && _Items[i]._kind != EII_PICKAX/*곡괭이*/&& _Items[i]._kind != EII_TORCH/*횃불*/ && _Items[i]._kind != EII_BAG && _Items[i]._kind != EII_STORAGE && _Items[i]._kind != EII_FIREPIT && _Items[i]._kind != EII_BONFIRE) {
			_Items[i]._num++;
			return true;
		}
	}
	return false;
}

void Inventory::useItem(OBJECT_IN_INVENTORY _item)
{
	switch (_item._kind)
	{
	case EII_AXE:
		if (_usingItems[0]._kind == EOBJECT_IN_INVENTORY_KIND::EII_NONE || resaveObject(_usingItems[0])) {
			_usingItems[0]._kind = EII_AXE;
			_usingItems[0]._num = _item._num;
		}
		break;
	case EII_PICKAX:
		if (_usingItems[0]._kind == EOBJECT_IN_INVENTORY_KIND::EII_NONE || resaveObject(_usingItems[0])) {
			_usingItems[0]._kind = EII_PICKAX;
			_usingItems[0]._num = _item._num;
		}
		break;
	case EII_TORCH:
		if (_usingItems[0]._kind == EOBJECT_IN_INVENTORY_KIND::EII_NONE || resaveObject(_usingItems[0])) {
			_usingItems[0]._kind = EII_TORCH;
			_usingItems[0]._num = _item._num;
			m_pRadialGradientBrush->SetCenter({WINSIZEX_NUM / 2, WINSIZEY_NUM / 2});
			m_pRadialGradientBrush->SetRadiusX(200);
			m_pRadialGradientBrush->SetRadiusY(150);
		}
		break;
	case EII_BAG:
		if (_usingItems[1]._kind == EOBJECT_IN_INVENTORY_KIND::EII_NONE || resaveObject(_usingItems[1])) {
			_usingItems[1]._kind = EII_BAG;
			_usingItems[1]._num = _item._num;
		}
		break;
	}
}

void Inventory::deleteObjects(EOBJECT_IN_INVENTORY_KIND _obj, int num)
{
	int _inventorySize;
	if (_isBag) {
		_inventorySize = IVENTORYMAX;
	}
	else _inventorySize = 15;

	for (int i = 0; i < _inventorySize; ++i) {
		if (_Items[i]._kind == _obj) {
			_Items[i]._num -= num;
			if (_Items[i]._num <= 0) {
				_Items[i]._kind = EOBJECT_IN_INVENTORY_KIND::EII_NONE;
				_Items[i]._num = NULL;
			}
			break;
		}
	}
}

void Inventory::reduceNum(int index, int damage)
{
	_usingItems[index]._num -= damage;
	if (_usingItems[index]._num <= 0) {
		if (_usingItems[index]._kind == EII_TORCH) {
			m_pRadialGradientBrush->SetRadiusX(0);
			m_pRadialGradientBrush->SetRadiusY(0);
		}
		SOUNDMANAGER->play("toolbreak");
		_usingItems[index]._kind = EII_NONE;
		_usingItems[index]._num = NULL;
	}
}
