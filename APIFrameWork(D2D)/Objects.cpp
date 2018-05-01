#include "stdafx.h"
#include "Objects.h"

// 종류에 따라 스위치 구문으로 나누어 함수를 진행

HRESULT OBJECT_ENVIRONMENT::init(EOBJKIND_ENVIRONMENT kind, POINT pt)
{
	_kind = kind;
	_pt = pt;
	if (_kind == TREE1 || _kind == TREE2) {
		aDropItem[0] = LOG;
		aDropItem[2] = LOG;
		aDropItem[1] = BRANCH;
	}
	if (_kind == ROCK) {
		aDropItem[0] = STONE;
		aDropItem[2] = STONE;
		aDropItem[1] = FLINT;
	}
	Regenerate();
	return S_OK;
}

void OBJECT_ENVIRONMENT::release(void)
{
}


void OBJECT_ENVIRONMENT::update(void)
{
	switch (_kind)
	{
	case FLOWER:
		if (_state == EOBJ_ENVIRONMENT_STATE::EES_DEAD) {
			if (TIMEMANAGER->getWorldTime() - _inactivateTime >= _regenerateTime) {
				Regenerate();
			}
		}
		else {
			ifZeroHP();
		}
		break;
	case PLANTCARROT:
		if (_state == EOBJ_ENVIRONMENT_STATE::EES_DEAD) {
			if (TIMEMANAGER->getWorldTime() - _inactivateTime >= _regenerateTime) {
				Regenerate();
			}
		}
		else {
			ifZeroHP();
		}
		break;
	case TREE1:
	case TREE2:
		if (_state == EOBJ_ENVIRONMENT_STATE::EES_DEAD) {
			if (TIMEMANAGER->getWorldTime() - _inactivateTime >= _regenerateTime) {
				Regenerate();
			}
		}
		else {
			switch (_state)
			{
			case EES_IDLE:
				_count++;
				_frame = _count / 2 % 21;
				if (_frame == 20) {
					_count = 0;
				}
				break;
			case EES_LEFTDYING:
				_count++;
				_frame = _count / 2 % 12;
				if (_frame == 11) {
					_count = 0;
				}
				break;
			case EES_RIGHTDYING:
				_count++;
				_frame = _count / 2 % 12;
				if (_frame == 11) {
					_count = 0;
				}
				break;
			case EES_CHOPPED:
				_count++;
				_frame = _count / 4 % 4;
				if (_frame == 3) {
					_count = 0;
					_state = EES_IDLE;
				}
				break;
			}
			ifZeroHP();
		}
		break;
	case RASPBERRYSTACK:
		if (_state == EOBJ_ENVIRONMENT_STATE::EES_DEAD) {
			if (TIMEMANAGER->getWorldTime() - _inactivateTime >= _regenerateTime) {
				Regenerate();
			}
		}
		else {
			ifZeroHP();
		}
		break;
	case ROCK:
		if (_state == EOBJ_ENVIRONMENT_STATE::EES_DEAD) {
			if (TIMEMANAGER->getWorldTime() - _inactivateTime >= _regenerateTime) {
				Regenerate();
			}
		}
		else {
			ifZeroHP();
		}
		break;
	case HAYSTACK:
		if (_state == EOBJ_ENVIRONMENT_STATE::EES_DEAD) {
			if (TIMEMANAGER->getWorldTime() - _inactivateTime >= _regenerateTime) {
				Regenerate();
			}
		}
		else {
			switch (_state)
			{
			case EES_IDLE:
				_count++;
				_frame = _count / 2 % 28;
				if (_frame == 27) {
					_count = 0;
				}
				break;
			case EES_DEAD:
				break;
			}
			ifZeroHP();
		}
		break;
	}
}

////////////////////////////////////////////////////
////						변경								////
////////////////////////////////////////////////////

//렌더 바텀렌더로

void OBJECT_ENVIRONMENT::render(void)
{
	POINT _tmp = CAMERAMANAGER->getAbsPosition(_pt);
	switch (_kind)
	{
	case FLOWER: {
		switch (_state)
		{
		case EES_IDLE:
			IMAGEMANAGER->bottomrender(L"object_flower", Rt, _tmp.x, _tmp.y);
			break;
		}
	}break;
	case PLANTCARROT:
		switch (_state)
		{
		case EES_IDLE:
			IMAGEMANAGER->bottomrender(L"object_planted_carrot", Rt, _tmp.x, _tmp.y);
			break;
		}
		break;
	case TREE1: {
		switch (_state)
		{
		case EES_IDLE:
			IMAGEMANAGER->frameBottomRender(L"object_tree1_idle", Rt, _tmp.x, _tmp.y, _frame, 0);
			break;
		case EES_DEAD:
			IMAGEMANAGER->bottomrender(L"object_tree1_die", Rt, _tmp.x, _tmp.y);
			break;
		case EES_LEFTDYING:
			IMAGEMANAGER->frameBottomRender(L"object_tree1_dyingLeft", Rt, _tmp.x, _tmp.y, _frame, 0);
			break;
		case EES_RIGHTDYING:
			IMAGEMANAGER->frameBottomRender(L"object_tree1_dyingRight", Rt, _tmp.x, _tmp.y, _frame, 0);
			break;
		case EES_CHOPPED:
			IMAGEMANAGER->frameBottomRender(L"object_tree1_chop", Rt, _tmp.x, _tmp.y, _frame, 0);
			break;
		}
	}break;
	case TREE2: {
		switch (_state)
		{
		case EES_IDLE:
			IMAGEMANAGER->frameBottomRender(L"object_tree2_idle", Rt, _tmp.x, _tmp.y, _frame, 0);
			break;
		case EES_DEAD:
			IMAGEMANAGER->bottomrender(L"object_tree2_die", Rt, _tmp.x, _tmp.y);
			break;
		case EES_LEFTDYING:
			IMAGEMANAGER->frameBottomRender(L"object_tree2_dyingLeft", Rt, _tmp.x, _tmp.y, _frame, 0);
			break;
		case EES_RIGHTDYING:
			IMAGEMANAGER->frameBottomRender(L"object_tree2_dyingRight", Rt, _tmp.x, _tmp.y, _frame, 0);
			break;
		case EES_CHOPPED:
			IMAGEMANAGER->frameBottomRender(L"object_tree2_chop", Rt, _tmp.x, _tmp.y, _frame, 0);
			break;
		}
	}break;
	case RASPBERRYSTACK:
		switch (_state)
		{
		case EES_IDLE:
			IMAGEMANAGER->bottomrender(L"object_berrybush_idle", Rt, _tmp.x, _tmp.y);
			break;
		case EES_DEAD:
			IMAGEMANAGER->bottomrender(L"object_berrybush_die", Rt, _tmp.x, _tmp.y);
			break;
		}
		break;
	case ROCK:
		if (_hp > 8)
			IMAGEMANAGER->bottomrender(L"object_rock1", Rt, _tmp.x, _tmp.y);
		if (4 < _hp && _hp <= 8)
			IMAGEMANAGER->bottomrender(L"object_rock2", Rt, _tmp.x, _tmp.y);
		if (0 < _hp && _hp <= 4)
			IMAGEMANAGER->bottomrender(L"object_rock3", Rt, _tmp.x, _tmp.y);
		break;
	case HAYSTACK:
		switch (_state)
		{
		case EES_IDLE:
			IMAGEMANAGER->frameBottomRender(L"object_hay_idle", Rt, _tmp.x, _tmp.y, _frame, 0);
			break;
		case EES_DEAD:
			IMAGEMANAGER->bottomrender(L"object_hay_pick", Rt, _tmp.x, _tmp.y);
			break;
		}
		break;
	}
}

void OBJECT_ENVIRONMENT::Regenerate()
{
	_state = EOBJ_ENVIRONMENT_STATE::EES_IDLE;
	_inactivateTime = NULL;
	switch (_kind)
	{
	case FLOWER: {
		_inactivateTime = NULL;
		_regenerateTime = 360.0f * 8;
		_hp = 1;
	}break;
	case PLANTCARROT:
		_inactivateTime = NULL;
		_regenerateTime = 360.0f * 8;
		_hp = 1;
		break;
	case TREE1: {
		_inactivateTime = NULL;
		_regenerateTime = 360.0f * 8;
		_hp = 6;
		_count = 0;
		_frame = 0;
	}break;
	case TREE2: {
		_inactivateTime = NULL;
		_regenerateTime = 360.0f * 8;
		_hp = 6;
		_count = 0;
		_frame = 0;
	}break;
	case RASPBERRYSTACK:
		_inactivateTime = NULL;
		_regenerateTime = 360.0f * 8;
		_hp = 1;
		break;
	case ROCK:
		_inactivateTime = NULL;
		_regenerateTime = 360.0f * 8;
		_hp = 12;
		_frame = 0;
		break;
	case HAYSTACK:
		_inactivateTime = NULL;
		_regenerateTime = 360.0f * 8;
		_hp = 1;
		_count = 0;
		_frame = 0;
		break;
	}
}

void OBJECT_ENVIRONMENT::ifZeroHP()
{
	if (_hp == 0) {
		_state = EOBJ_ENVIRONMENT_STATE::EES_DELETE;
		_inactivateTime = TIMEMANAGER->getWorldTime();
	}
}

HRESULT OBJECT_MATERIAL::init(EOBJKIND_MATERIAL kind, POINT pt)
{
	_kind = kind;
	_pt = pt;
	_state = EES_IDLE;
	return S_OK;
}

void OBJECT_MATERIAL::release(void)
{
}

void OBJECT_MATERIAL::update(void)
{
}


////////////////////////////////////////////////////
////						추가								////
////////////////////////////////////////////////////

void OBJECT_MATERIAL::render(void)
{
	POINT tmp = CAMERAMANAGER->getAbsPosition(_pt);
	switch (_kind)
	{
	case FLINT:
		IMAGEMANAGER->bottomrender(L"object_flint", Rt, tmp.x, tmp.y);
		break;
	case STONE:
		IMAGEMANAGER->bottomrender(L"object_stone", Rt, tmp.x, tmp.y);
		break;
	case BRANCH:
		IMAGEMANAGER->bottomrender(L"object_twigs", Rt, tmp.x, tmp.y);
		break;
	case HAY:
		IMAGEMANAGER->bottomrender(L"object_cutgrass", Rt, tmp.x, tmp.y);
		break;
	case LOG:
		IMAGEMANAGER->bottomrender(L"object_log", Rt, tmp.x, tmp.y);
		break;
	case BOARD:
		IMAGEMANAGER->bottomrender(L"object_board", Rt, tmp.x, tmp.y);
		break;
	}
}

////////////////////////////////////////////////////
////	화덕, 모닥불, 상자 추가					////
////////////////////////////////////////////////////

HRESULT OBJECT_FIRE::init(bool kind, POINT pt)
{
	_kind = kind;
	_pt.x = pt.x - 100;
	_pt.y = pt.y;
	_state = EFS_PLACE;
	if (_kind) {  // 화덕
		firePowerX = 400;
		firePowerY = 350;
	}
	else {		 // 모닥불
		firePowerX = 300;
		firePowerY = 250;
	}
	frame = count = 0;
	return S_OK;
}

void OBJECT_FIRE::release()
{
}

void OBJECT_FIRE::update()
{
	count++;
	switch (_state)
	{
	case EFS_PLACE:
		if (count % 4 == 0) {
			frame++;
			if (frame == 8) {
					frame = 0;
					_state = EFS_IDLE;
			}
		}
		break;
	case EFS_IDLE:
		if (count % 4 == 0) {
			frame++;
			if (frame == 4) {
				frame = 0;
			}
		}
		D2D1_POINT_2F tmp = { CAMERAMANAGER->getAbsPosition(_pt).x, CAMERAMANAGER->getAbsPosition(_pt).y };
		m_pRadialGradientBrush->SetCenter(tmp);
		m_pRadialGradientBrush->SetRadiusX(firePowerX);
		m_pRadialGradientBrush->SetRadiusY(firePowerY);
		lightDown();
		break;
	}
}

void OBJECT_FIRE::render()
{
	if (_kind) {
		switch (_state)
		{
		case EFS_PLACE:
			IMAGEMANAGER->frameBottomRender(L"object_firepit_place", Rt, CAMERAMANAGER->getAbsPosition(_pt).x, CAMERAMANAGER->getAbsPosition(_pt).y, frame, 0);
			break;
		case EFS_IDLE:
			IMAGEMANAGER->bottomrender(L"object_firepit", Rt, CAMERAMANAGER->getAbsPosition(_pt).x, CAMERAMANAGER->getAbsPosition(_pt).y);
			IMAGEMANAGER->frameBottomRender(L"object_campfire_fire_1", Rt, CAMERAMANAGER->getAbsPosition(_pt).x, CAMERAMANAGER->getAbsPosition(_pt).y - 30, frame, 0);
			break;
		case EFS_DEAD:
			IMAGEMANAGER->bottomrender(L"object_firepit", Rt, CAMERAMANAGER->getAbsPosition(_pt).x, CAMERAMANAGER->getAbsPosition(_pt).y);
			break;
		}
	}
	else {
		switch (_state)
		{
		case EFS_PLACE:
			IMAGEMANAGER->frameBottomRender(L"object_camfire_place", Rt, CAMERAMANAGER->getAbsPosition(_pt).x + 5, CAMERAMANAGER->getAbsPosition(_pt).y, frame, 0);
			break;
		case EFS_IDLE:
			IMAGEMANAGER->bottomrender(L"object_campfire", Rt, CAMERAMANAGER->getAbsPosition(_pt).x + 5, CAMERAMANAGER->getAbsPosition(_pt).y);
			IMAGEMANAGER->frameBottomRender(L"object_campfire_fire_1", Rt, CAMERAMANAGER->getAbsPosition(_pt).x, CAMERAMANAGER->getAbsPosition(_pt).y - 30, frame, 0);
			break;
		case EFS_DEAD:
			IMAGEMANAGER->bottomrender(L"object_campfire_dead", Rt, CAMERAMANAGER->getAbsPosition(_pt).x + 5, CAMERAMANAGER->getAbsPosition(_pt).y);
			break;
		}
	}
}

void OBJECT_FIRE::lightDown()
{
	if ((int)TIMEMANAGER->getWorldTime() % 1 == 0 && (int)TIMEMANAGER->getWorldTime() != lightDownTime) {
		lightDownTime = (int)TIMEMANAGER->getWorldTime();
		firePowerX -= 5;
		firePowerY -= 5;
		if (firePowerX <= 100 || firePowerY <= 100) {
			m_pRadialGradientBrush->SetRadiusX(0);
			m_pRadialGradientBrush->SetRadiusY(0);
			_state = EFS_DEAD;
		}
	}
}

HRESULT OBJECT_STORAGE::init(POINT pt)
{
	for (int i = 0; i < 9; ++i) {
		_Items[i]._kind = EII_NONE;
		_Items[i]._num = NULL;
	}
	_pt.x = pt.x - 100;
	_pt.y = pt.y;
	_isOpen = true;
	frame = count = 0;
	return S_OK;
}

void OBJECT_STORAGE::release()
{
}

void OBJECT_STORAGE::update()
{
	checkOpenRange();
	count++;
	if (count % 5 == 0) {
		if (_isOpen) {
			if (frame > 0) {
				frame--;
			}
		}
		else {
			if (frame < 7) {
				frame++;
			}
		}
	}
}

void OBJECT_STORAGE::render()
{
	IMAGEMANAGER->frameBottomRender(L"object_chest_close", Rt, CAMERAMANAGER->getAbsPosition(_pt).x, CAMERAMANAGER->getAbsPosition(_pt).y, frame, 0);
	
	if (_isOpen) {
		IMAGEMANAGER->render(L"chest_on", Rt, 1095, 250);
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				IMAGEMANAGER->frameRender(L"ui_items", Rt, 1115 + i * 42, 275 + j * 44, _Items[i * 3 + j]._kind - 1, 0);
				if (_Items[i * 3 + j]._kind == EOBJECT_IN_INVENTORY_KIND::EII_NONE || _Items[i * 3 + j]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BAG || _Items[i * 3 + j]._kind == EOBJECT_IN_INVENTORY_KIND::EII_STORAGE || _Items[i * 3 + j]._kind == EOBJECT_IN_INVENTORY_KIND::EII_FIREPIT || _Items[i * 3 + j]._kind == EOBJECT_IN_INVENTORY_KIND::EII_BONFIRE) continue;
				int tmp = _Items[i * 3 + j]._num;
				int count = 0;
				while (tmp != 0) {
					count++;
					IMAGEMANAGER->frameRender(L"inventory_number", Rt, 1130 + i * 42 - 9 * count, 276 + j * 44, tmp % 10, 0);
					tmp /= 10;
				}
				if (count == 0) {
					IMAGEMANAGER->frameRender(L"inventory_number", Rt, 1130 + i * 42, 276 + j * 44, 0, 0);
				}
			}
		}
	}
}

void OBJECT_STORAGE::checkOpenRange()
{
	if (abs(CAMERAMANAGER->getAbsPosition(_pt).x - WINSIZEX_NUM / 2) <= 100 && abs(CAMERAMANAGER->getAbsPosition(_pt).y - WINSIZEY_NUM / 2) <= 100) {
		_isOpen = true;
	}
	else {
		_isOpen = false;
	}
}