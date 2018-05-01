#include "stdafx.h"
#include "Map.h"

extern  OBJECT_ENVIRONMENT vObjEnvi[TILEY][TILEX];
extern vector<OBJECT_MATERIAL> vObjMate[TILEY][TILEX];

Map::Map()
{
}


Map::~Map()
{
}

HRESULT Map::init(void)
{
	_uimanager = new UImanager;
	_uimanager->init();

	_inventory = new Inventory;
	_inventory->init();

	_character = new Character;
	_character->init();

	_clock = new Clock;
	_clock->init();

	_uimanager->setDay(_clock->getDay());

	_craft = new Crafting;
	_craft->init();
	_craft->setInvenMemoryRick(_inventory);

	_drawItem._isClick = false;
	_drawItem.previndex = NULL;
	zOderY = 0;
	_showRect = false;
	return S_OK;
}

void Map::release(void)
{
	_uimanager->release();
	_inventory->release();
	_character->release();
	_clock->release();
	_craft->release();
}

void Map::update(void)
{
	checkUseItem();
	m_tiles->update();
	_uimanager->update();
	_inventory->update();
	_clock->update();
	_craft->update();

	vCollision.clear();
	isCollisionEnvi();
	isCollisionMate();


	CheckDropMental();
	// 불요소 업데이트
	for (int i = 0; i < mObjFire.size(); ++i) {
		mObjFire.at(i)->update();
	}
	// 저장소 업데이트
	for (int i = 0; i < mObjStorage.size(); ++i) {
		mObjStorage.at(i)->update();
	}

	mouseClick();
	objUpdate();
	//z오더 체크 업데이트
	zOderCheck();
	if (KEYMANAGER->isOnceKeyDown('P')) {
		_showRect = !_showRect;
	}
}

void Map::render(void)
{
	m_tiles->render();


	for (int x = _character->getPointerPosition()->y / TILESIZEY - 5; x < _character->getPointerPosition()->y / TILESIZEY + 5; ++x) {
		for (int y = _character->getPointerPosition()->x / TILESIZEX - 7; y < _character->getPointerPosition()->x / TILESIZEX + 7; ++y) {
			if (x < 0 || y < 0) continue;
			if (x >= TILEX || y >= TILEY) continue;
			if (!vObjMate[x][y].empty()) {
				for (int i = 0; i < vObjMate[x][y].size(); i++) {
					vObjMate[x][y].at(i).render();
				}
			}
		}
	}

	if (zOderY <= _character->getPointerPosition()->y)
	{
		m_tiles->objFrontRender();
		_character->render();
	}
	else
	{
		_character->render();
		m_tiles->objFrontRender();
	}
	
	if(_showRect){
		collisionRectDraw();
	}

	// 불요소 렌더
	for (int i = 0; i < mObjFire.size(); ++i) {
		mObjFire.at(i)->render();
	}

	_clock->render();
	_uimanager->render();
	// 저장소 렌더
	for (int i = 0; i < mObjStorage.size(); ++i) {
		mObjStorage.at(i)->render();
	}
	_inventory->render();
	_craft->render();

	//drawitem render
	if (_drawItem._isClick) {
		IMAGEMANAGER->frameRender(L"ui_items", Rt, _ptMouse.x - 16, _ptMouse.y - 16, (int)_drawItem._item._kind - 1, 0);
	}

	TIMEMANAGER->render(Rt);
}

void Map::isCollisionEnvi()
{
	for (int x = _character->getPointerPosition()->y / TILESIZEY - 5; x < _character->getPointerPosition()->y / TILESIZEY + 5; ++x) {
		for (int y = _character->getPointerPosition()->x / TILESIZEX - 7; y < _character->getPointerPosition()->x / TILESIZEX + 7; ++y) {
			//for (int i = 0; i < vObjEnvi[x][y].size(); i++)
			if (vObjEnvi[y][x].getKind() != NONE_ENVIRONMENT && vObjEnvi[y][x].getState() == EES_IDLE) {
				POINT winPt = CAMERAMANAGER->getAbsPosition(vObjEnvi[y][x].getPosition());
				int width, height;
				tagCollision tmp;
				switch (vObjEnvi[y][x].getKind())
				{
				case FLOWER:
				case PLANTCARROT:
					width = 20;
					height = 20;
					break;
				case TREE1:
				case TREE2:
					width = 70;
					height = 100;
					break;
				case RASPBERRYSTACK:
				case ROCK:
					width = 50;
					height = 50;
					break;
				case HAYSTACK:
					width = 30;
					height = 70;
					break;
				}
				tmp.rc = RectFMake(winPt.x - (width) / 2, winPt.y - height, width, height);
				tmp.mAbsPt = vObjEnvi[y][x].getPosition();
				tmp.kindEnvi = vObjEnvi[y][x].getKind();
				vCollision.push_back(tmp);
			}
		}
	}
}

void Map::isCollisionMate() {
	for (int y = _character->getPointerPosition()->y / TILESIZEY - 5; y < _character->getPointerPosition()->y / TILESIZEY + 5; ++y) {
		for (int x = _character->getPointerPosition()->x / TILESIZEX - 7; x < _character->getPointerPosition()->x / TILESIZEX + 7; ++x) {
			for (int i = 0; i < vObjMate[y][x].size(); i++) {
				POINT winPt = CAMERAMANAGER->getAbsPosition(vObjMate[y][x].at(i).getPosition());
				int width = 20, height = 20;
				tagCollision tmp;
				tmp.rc = RectFMake(winPt.x - (width) / 2, winPt.y - height, width, height);
				tmp.mAbsPt = vObjMate[y][x].at(i).getPosition();
				tmp.kindMate = vObjMate[y][x].at(i).getKind();
				tmp.index = i;
				vCollision.push_back(tmp);
			}
		}
	}
}

void Map::collisionRectDraw()
{
	vector<tagCollision>::iterator iter;
	for (iter = vCollision.begin(); iter != vCollision.end(); ++iter) {
		D2Rectangle(Rt, iter->rc, Brush);
	}

	TCHAR _point[20];
	wsprintf(_point, L"%d", selectObjEnvi);
	D2TextOut(Rt, _point, TextFormat, D2D1::RectF(0, 50, 500, 70), Brush);
}

void Map::mouseClick()
{
	if (_character->getCharacterAction() == IDLE || _character->getCharacterAction() == IDLE_TORCH) {
		selectObjEnvi = NONE_ENVIRONMENT;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		vector<tagCollision>::iterator iter;
		for (iter = vCollision.begin(); iter != vCollision.end(); ++iter) {
			RECT rc = { iter->rc.left, iter->rc.top, iter->rc.right, iter->rc.bottom };
			if (getDistance(iter->mAbsPt.x, iter->mAbsPt.y, _character->getPointerPosition()->x, _character->getPointerPosition()->y) > 100) continue;

			if (PtInRect(&rc, _ptMouse)) {
				selectObjEnvi = iter->kindEnvi;
				POINT click = iter->mAbsPt;
				// Enviornment
				stateEnvi = vObjEnvi[click.x / TILESIZEX][click.y / TILESIZEY].getState();
				if (stateEnvi == EES_IDLE) {
					switch (iter->kindEnvi)
					{
					case FLOWER:
						mCharcterAction = ACTION_PICKUP;
						vObjEnvi[click.x / TILESIZEX][click.y / TILESIZEY].damage();
						_inventory->saveObject(EII_LEAF);
						break;
					case PLANTCARROT:
						mCharcterAction = ACTION_PICKUP;
						vObjEnvi[click.x / TILESIZEX][click.y / TILESIZEY].damage();
						_inventory->saveObject(EII_CARROT);
						break;
					case TREE1:
					case TREE2:
						if (_inventory->getHandItem()._kind == EII_AXE) {
							mCharcterAction = ACTION_AXE;
							vObjEnvi[click.x / TILESIZEX][click.y / TILESIZEY].changeState(EES_CHOPPED);
							vObjEnvi[click.x / TILESIZEX][click.y / TILESIZEY].damage();
							_inventory->reduceNum(0, 5);
							SOUNDMANAGER->play("hitTree");
						}
						else {
							if (_inventory->getHandItem()._kind == EII_TORCH)
								mCharcterAction = IDLE_TORCH;
							else
								mCharcterAction = IDLE;
						}
						break;
					case ROCK:
						if (_inventory->getHandItem()._kind == EII_PICKAX) {
							mCharcterAction = ACTION_PICKAXE;
							vObjEnvi[click.x / TILESIZEX][click.y / TILESIZEY].damage();
							_inventory->reduceNum(0, 5);
							SOUNDMANAGER->play("hitStone");
						}
						else {
							if (_inventory->getHandItem()._kind == EII_TORCH)
								mCharcterAction = IDLE_TORCH;
							else
								mCharcterAction = IDLE;
						}
						break;
					case RASPBERRYSTACK:
						mCharcterAction = ACTION_BUILD;
						vObjEnvi[click.x / TILESIZEX][click.y / TILESIZEY].damage();
						_inventory->saveObject(EII_RASPBERRY);
						break;
					case HAYSTACK:
						mCharcterAction = ACTION_BUILD;
						vObjEnvi[click.x / TILESIZEX][click.y / TILESIZEY].damage();
						_inventory->saveObject(EII_HAY);
						break;
					}
				}

				// Material
				if (iter->index > -1) {
					switch (iter->kindMate)
					{
					case FLINT:
						mCharcterAction = ACTION_PICKUP;
						_inventory->saveObject(EII_FLINT);
						vObjMate[click.y / TILESIZEY][click.x / TILESIZEX].erase(vObjMate[click.y / TILESIZEY][click.x / TILESIZEX].begin() + iter->index);
						iter->index = -1;
						break;
					case STONE:
						mCharcterAction = ACTION_PICKUP;
						_inventory->saveObject(EII_STONE);
						vObjMate[click.y / TILESIZEY][click.x / TILESIZEX].erase(vObjMate[click.y / TILESIZEY][click.x / TILESIZEX].begin() + iter->index);
						iter->index = -1;
						break;
					case BRANCH:
						mCharcterAction = ACTION_PICKUP;
						_inventory->saveObject(EII_BRANCH);
						vObjMate[click.y / TILESIZEY][click.x / TILESIZEX].erase(vObjMate[click.y / TILESIZEY][click.x / TILESIZEX].begin() + iter->index);
						iter->index = -1;
						break;
					case HAY:
						mCharcterAction = ACTION_PICKUP;
						_inventory->saveObject(EII_HAY);
						vObjMate[click.y / TILESIZEY][click.x / TILESIZEX].erase(vObjMate[click.y / TILESIZEY][click.x / TILESIZEX].begin() + iter->index);
						iter->index = -1;
						break;
					case LOG:
						mCharcterAction = ACTION_PICKUP;
						_inventory->saveObject(EII_LOG);
						vObjMate[click.y / TILESIZEY][click.x / TILESIZEX].erase(vObjMate[click.y / TILESIZEY][click.x / TILESIZEX].begin() + iter->index);
						iter->index = -1;
						break;
					case BOARD:
						mCharcterAction = ACTION_PICKUP;
						_inventory->saveObject(EII_BOARD);
						vObjMate[click.y / TILESIZEY][click.x / TILESIZEX].erase(vObjMate[click.y / TILESIZEY][click.x / TILESIZEX].begin() + iter->index);
						iter->index = -1;
						break;
					}
				}
			}

		}
	}

}

void Map::objUpdate()
{
	// Environment
	if (selectObjEnvi == NONE_ENVIRONMENT) {
		if (_inventory->getHandItem()._kind == EII_TORCH)
			_character->setIsTorch(true);
		else _character->setIsTorch(false);
		_character->update();

	}
	else {
		_character->update(mCharcterAction);
	}


	for (int x = _character->getPointerPosition()->y / TILESIZEY - 5; x < _character->getPointerPosition()->y / TILESIZEY + 5; ++x) {
		for (int y = _character->getPointerPosition()->x / TILESIZEX - 7; y < _character->getPointerPosition()->x / TILESIZEX + 7; ++y) {
			vObjEnvi[y][x].update();
			if (vObjEnvi[y][x].getState() == EES_DELETE) {
				switch (vObjEnvi[y][x].getKind())
				{
				case TREE1:
					for (int i = 0; i < 3; i++) {
						OBJECT_MATERIAL tmp;
						tmp.init(vObjEnvi[y][x].getDropItem()[i], { y*TILESIZEX + i * 40,x*TILESIZEY });
						vObjMate[x][y].push_back(tmp);
					}
					vObjEnvi[y][x].changeState(EES_DEAD);
					break;
				case TREE2:
					for (int i = 0; i < 3; i++) {
						OBJECT_MATERIAL tmp;
						tmp.init(vObjEnvi[y][x].getDropItem()[i], { y*TILESIZEX + i * 40,x*TILESIZEY });
						vObjMate[x][y].push_back(tmp);
					}
					vObjEnvi[y][x].changeState(EES_DEAD);
					break;
				case ROCK:
					for (int i = 0; i < 3; i++) {
						OBJECT_MATERIAL tmp;
						tmp.init(vObjEnvi[y][x].getDropItem()[i], { y*TILESIZEX + i * 40,x*TILESIZEY });
						vObjMate[x][y].push_back(tmp);
					}
					vObjEnvi[y][x].changeState(EES_DEAD);
					break;
				}
			}
			if (vObjEnvi[y][x].getState() == EES_DELETE) {
				switch (vObjEnvi[y][x].getKind())
				{
				case FLOWER:
					_inventory->saveObject(EII_LEAF);
					break;
				case PLANTCARROT:
					_inventory->saveObject(EII_CARROT);
					break;
				case RASPBERRYSTACK:
					_inventory->saveObject(EII_RASPBERRY);
					break;
				case HAYSTACK:
					_inventory->saveObject(EII_HAY);
					break;
				}
				vObjEnvi[y][x].changeState(EES_DEAD);
			}
		}
	}
}

void Map::checkUseItem()
{
	for (int i = 0; i < 5; i++)
	{
		if (IsInRect(_ptMouse, { 290 + i * 38, 689 , 290 + i * 38 + 32, 689 + 32 })) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				if (!_drawItem._isClick) {
					if (_inventory->loadObject()[i]._kind != EII_NONE) {
						_drawItem._item = _inventory->loadObject()[i];
						_inventory->deleteByindex(i);
						_drawItem.previndex = i;
						_drawItem._isClick = true;
					}
				}
				else {
					if (_inventory->loadObject()[i]._kind == EII_NONE) {
						_inventory->saveByindex(i, _drawItem._item);
					}
					else {
						_inventory->saveByindex(_drawItem.previndex, _inventory->loadObject()[i]);
						_inventory->saveByindex(i, _drawItem._item);
					}
					_drawItem.previndex = NULL;
					_drawItem._isClick = false;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
				switch (_inventory->loadObject()[i]._kind)
				{
				case EII_CARROT:
					_inventory->reduceByindexandNum(i, 1);
					_uimanager->upHunger();
					break;
				case EII_RASPBERRY:
					_inventory->reduceByindexandNum(i, 1);
					_uimanager->upHunger();
					break;
				case EII_AXE:
					_inventory->useItem(_inventory->loadObject()[i]);
					_inventory->deleteByindex(i);
					break;
				case EII_PICKAX:
					_inventory->useItem(_inventory->loadObject()[i]);
					_inventory->deleteByindex(i);
					break;
				case EII_TORCH:
					_inventory->useItem(_inventory->loadObject()[i]);
					_inventory->deleteByindex(i);
					break;
				case EII_BAG:
					_inventory->useItem(_inventory->loadObject()[i]);
					_inventory->deleteByindex(i);
					break;
				case EII_LEAF:
					_inventory->reduceByindexandNum(i, 1);
					_uimanager->upMental();
					break;
				case EII_BONFIRE:
					mObjFire.push_back(new OBJECT_FIRE);
					mObjFire.back()->init(false, { CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
					_inventory->deleteObjects(_inventory->loadObject()[i]._kind, 1);
					break;
				case EII_FIREPIT:
					mObjFire.push_back(new OBJECT_FIRE);
					mObjFire.back()->init(true, { CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
					_inventory->deleteObjects(_inventory->loadObject()[i]._kind, 1);
					break;
				case EII_STORAGE:
					mObjStorage.push_back(new OBJECT_STORAGE);
					mObjStorage.back()->init({ CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
					_inventory->deleteObjects(_inventory->loadObject()[i]._kind, 1);
					break;
				}
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (IsInRect(_ptMouse, { 489 + i * 38, 689 , 489 + i * 38 + 32, 689 + 32 })) {
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
				switch (_inventory->loadObject()[i + 5]._kind)
				{
				case EII_CARROT:
					_inventory->reduceByindexandNum(i + 5, 1);
					_uimanager->upHunger();
					break;
				case EII_RASPBERRY:
					_inventory->reduceByindexandNum(i + 5, 1);
					_uimanager->upHunger();
					break;
				case EII_AXE:
					_inventory->useItem(_inventory->loadObject()[i + 5]);
					_inventory->deleteByindex(i + 5);
					break;
				case EII_PICKAX:
					_inventory->useItem(_inventory->loadObject()[i + 5]);
					_inventory->deleteByindex(i + 5);
					break;
				case EII_TORCH:
					_inventory->useItem(_inventory->loadObject()[i + 5]);
					_inventory->deleteByindex(i + 5);
					break;
				case EII_BAG:
					_inventory->useItem(_inventory->loadObject()[i + 5]);
					_inventory->deleteByindex(i + 5);
					break;
				case EII_LEAF:
					_inventory->reduceByindexandNum(i + 5, 1);
					_uimanager->upMental();
					break;
				case EII_BONFIRE:
					mObjFire.push_back(new OBJECT_FIRE);
					mObjFire.back()->init(false, { CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
					_inventory->deleteObjects(_inventory->loadObject()[i + 5]._kind, 1);
					break;
				case EII_FIREPIT:
					mObjFire.push_back(new OBJECT_FIRE);
					mObjFire.back()->init(true, { CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
					_inventory->deleteObjects(_inventory->loadObject()[i + 5]._kind, 1);
					break;
				case EII_STORAGE:
					mObjStorage.push_back(new OBJECT_STORAGE);
					mObjStorage.back()->init({ CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
					_inventory->deleteObjects(_inventory->loadObject()[i + 5]._kind, 1);
					break;
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				if (!_drawItem._isClick) {
					if (_inventory->loadObject()[i + 5]._kind != EII_NONE) {
						_drawItem._item = _inventory->loadObject()[i + 5];
						_inventory->deleteByindex(i + 5);
						_drawItem.previndex = i + 5;
						_drawItem._isClick = true;
					}
				}
				else {
					if (_inventory->loadObject()[i + 5]._kind == EII_NONE) {
						_inventory->saveByindex(i + 5, _drawItem._item);
					}
					else {
						_inventory->saveByindex(_drawItem.previndex, _inventory->loadObject()[i + 5]);
						_inventory->saveByindex(i + 5, _drawItem._item);
					}
					_drawItem.previndex = NULL;
					_drawItem._isClick = false;
				}
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (IsInRect(_ptMouse, { 684 + i * 38, 689 , 684 + i * 38 + 32, 689 + 32 })) {
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
				switch (_inventory->loadObject()[i + 10]._kind)
				{
				case EII_CARROT:
					_inventory->reduceByindexandNum(i + 10, 1);
					_uimanager->upHunger();
					break;
				case EII_RASPBERRY:
					_inventory->reduceByindexandNum(i + 10, 1);
					_uimanager->upHunger();
					break;
				case EII_AXE:
					_inventory->useItem(_inventory->loadObject()[i + 10]);
					_inventory->deleteByindex(i + 10);
					break;
				case EII_PICKAX:
					_inventory->useItem(_inventory->loadObject()[i + 10]);
					_inventory->deleteByindex(i + 10);
					break;
				case EII_TORCH:
					_inventory->useItem(_inventory->loadObject()[i + 10]);
					_inventory->deleteByindex(i + 10);
					break;
				case EII_BAG:
					_inventory->useItem(_inventory->loadObject()[i + 10]);
					_inventory->deleteByindex(i + 10);
					break;
				case EII_LEAF:
					_inventory->reduceByindexandNum(i + 10, 1);
					_uimanager->upMental();
					break;
				case EII_BONFIRE:
					mObjFire.push_back(new OBJECT_FIRE);
					mObjFire.back()->init(false, { CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
					_inventory->deleteObjects(_inventory->loadObject()[i + 10]._kind, 1);
					break;
				case EII_FIREPIT:
					mObjFire.push_back(new OBJECT_FIRE);
					mObjFire.back()->init(true, { CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
					_inventory->deleteObjects(_inventory->loadObject()[i + 10]._kind, 1);
					break;
				case EII_STORAGE:
					mObjStorage.push_back(new OBJECT_STORAGE);
					mObjStorage.back()->init({ CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
					_inventory->deleteObjects(_inventory->loadObject()[i + 10]._kind, 1);
					break;
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				if (!_drawItem._isClick) {
					if (_inventory->loadObject()[i + 10]._kind != EII_NONE) {
						_drawItem._item = _inventory->loadObject()[i + 10];
						_inventory->deleteByindex(i + 10);
						_drawItem.previndex = i + 10;
						_drawItem._isClick = true;
					}
				}
				else {
					if (_inventory->loadObject()[i + 10]._kind == EII_NONE) {
						_inventory->saveByindex(i + 10, _drawItem._item);
					}
					else {
						_inventory->saveByindex(_drawItem.previndex, _inventory->loadObject()[i + 10]);
						_inventory->saveByindex(i + 10, _drawItem._item);
					}
					_drawItem.previndex = NULL;
					_drawItem._isClick = false;
				}
			}
		}
	}

	if (_inventory->getIsBag()) {
		for (int i = 0; i < 3; ++i) {
			if (IsInRect(_ptMouse, { 1200 - 34, 488 + i * 34,1200 - 34 + 32, 488 + i * 34 + 32 })) {
				if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
					switch (_inventory->loadObject()[i + 15]._kind)
					{
					case EII_CARROT:
						_inventory->reduceByindexandNum(i + 15, 1);
						_uimanager->upHunger();
						break;
					case EII_RASPBERRY:
						_inventory->reduceByindexandNum(i + 15, 1);
						_uimanager->upHunger();
						break;
					case EII_AXE:
						_inventory->useItem(_inventory->loadObject()[i + 15]);
						_inventory->deleteByindex(i + 15);
						break;
					case EII_PICKAX:
						_inventory->useItem(_inventory->loadObject()[i + 15]);
						_inventory->deleteByindex(i + 15);
						break;
					case EII_TORCH:
						_inventory->useItem(_inventory->loadObject()[i + 15]);
						_inventory->deleteByindex(i + 15);
						break;
					case EII_BAG:
						_inventory->useItem(_inventory->loadObject()[i + 15]);
						_inventory->deleteByindex(i + 15);
						break;
					case EII_LEAF:
						_inventory->reduceByindexandNum(i + 15, 1);
						_uimanager->upMental();
						break;
					case EII_BONFIRE:
						mObjFire.push_back(new OBJECT_FIRE);
						mObjFire.back()->init(false, { CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
						_inventory->deleteObjects(_inventory->loadObject()[i + 15]._kind, 1);
						break;
					case EII_FIREPIT:
						mObjFire.push_back(new OBJECT_FIRE);
						mObjFire.back()->init(true, { CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
						_inventory->deleteObjects(_inventory->loadObject()[i + 15]._kind, 1);
						break;
					case EII_STORAGE:
						mObjStorage.push_back(new OBJECT_STORAGE);
						mObjStorage.back()->init({ CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
						_inventory->deleteObjects(_inventory->loadObject()[i + 15]._kind, 1);
						break;
					}
				}

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					if (!_drawItem._isClick) {
						if (_inventory->loadObject()[i + 15]._kind != EII_NONE) {
							_drawItem._item = _inventory->loadObject()[i + 15];
							_inventory->deleteByindex(i + 15);
							_drawItem.previndex = i + 15;
							_drawItem._isClick = true;
						}
					}
					else {
						if (_inventory->loadObject()[i + 15]._kind == EII_NONE) {
							_inventory->saveByindex(i + 15, _drawItem._item);
						}
						else {
							_inventory->saveByindex(_drawItem.previndex, _inventory->loadObject()[i + 15]);
							_inventory->saveByindex(i + 15, _drawItem._item);
						}
						_drawItem.previndex = NULL;
						_drawItem._isClick = false;
					}
				}
			}
		}
		for (int i = 0; i < 3; ++i) {
			if (IsInRect(_ptMouse, { 1200, 488 + i * 34,1200 + 32, 488 + i * 34 + 32 })) {
				if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
					switch (_inventory->loadObject()[i + 18]._kind)
					{
					case EII_CARROT:
						_inventory->reduceByindexandNum(i + 18, 1);
						_uimanager->upHunger();
						break;
					case EII_RASPBERRY:
						_inventory->reduceByindexandNum(i + 18, 1);
						_uimanager->upHunger();
						break;
					case EII_AXE:
						_inventory->useItem(_inventory->loadObject()[i + 18]);
						_inventory->deleteByindex(i + 18);
						break;
					case EII_PICKAX:
						_inventory->useItem(_inventory->loadObject()[i + 18]);
						_inventory->deleteByindex(i + 18);
						break;
					case EII_TORCH:
						_inventory->useItem(_inventory->loadObject()[i + 18]);
						_inventory->deleteByindex(i + 18);
						break;
					case EII_BAG:
						_inventory->useItem(_inventory->loadObject()[i + 18]);
						_inventory->deleteByindex(i + 18);
						break;
					case EII_LEAF:
						_inventory->reduceByindexandNum(i + 18, 1);
						_uimanager->upMental();
						break;
					case EII_BONFIRE:
						mObjFire.push_back(new OBJECT_FIRE);
						mObjFire.back()->init(false, { CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
						_inventory->deleteObjects(_inventory->loadObject()[i + 18]._kind, 1);
						break;
					case EII_FIREPIT:
						mObjFire.push_back(new OBJECT_FIRE);
						mObjFire.back()->init(true, { CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
						_inventory->deleteObjects(_inventory->loadObject()[i + 18]._kind, 1);
						break;
					case EII_STORAGE:
						mObjStorage.push_back(new OBJECT_STORAGE);
						mObjStorage.back()->init({ CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y });
						_inventory->deleteObjects(_inventory->loadObject()[i + 18]._kind, 1);
						break;
					}
				}

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					if (!_drawItem._isClick) {
						if (_inventory->loadObject()[i + 18]._kind != EII_NONE) {
							_drawItem._item = _inventory->loadObject()[i + 18];
							_inventory->deleteByindex(i + 18);
							_drawItem.previndex = i + 18;
							_drawItem._isClick = true;
						}
					}
					else {
						if (_inventory->loadObject()[i + 18]._kind == EII_NONE) {
							_inventory->saveByindex(i + 18, _drawItem._item);
						}
						else {
							_inventory->saveByindex(_drawItem.previndex, _inventory->loadObject()[i + 18]);
							_inventory->saveByindex(i + 18, _drawItem._item);
						}
						_drawItem.previndex = NULL;
						_drawItem._isClick = false;
					}
				}
			}
		}
	}

	for (int k = 0; k < mObjStorage.size(); ++k) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (mObjStorage.at(k)->getisOpen()) {
					if (IsInRect(_ptMouse, { 1115 + i * 42, 275 + j * 44 ,1115 + i * 42 + 32, 275 + j * 44 + 32 })) {
						if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
							if (_inventory->resaveObject(mObjStorage.at(k)->loadItem()[i * 3 + j])) {
								mObjStorage.at(k)->deleteByindex(i * 3 + j);
							}
						}
						if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
							if (_drawItem._isClick) {
								if (mObjStorage.at(k)->loadItem()[i * 3 + j]._kind == EII_NONE) {
									mObjStorage.at(k)->saveByindex(i * 3 + j, _drawItem._item);
								}
								else {
									_inventory->saveByindex(_drawItem.previndex, mObjStorage.at(k)->loadItem()[i * 3 + j]);
									mObjStorage.at(k)->saveByindex(i * 3 + j, _drawItem._item);
								}
								_drawItem.previndex = NULL;
								_drawItem._isClick = false;
							}
						}
					}
				}
			}
		}
	}
}

void Map::CheckDropMental()
{
	for (int i = 0; i < mObjFire.size(); ++i) {
		if (getDistance(CAMERAMANAGER->getStandardPoint().x, CAMERAMANAGER->getStandardPoint().y, mObjFire.at(i)->getPosition().x, mObjFire.at(i)->getPosition().y) <= 500 && mObjFire.at(i)->getState() == EFS_IDLE) {
			_uimanager->reduceMental(REDUCEMENTAL, 0);
			return;
		}
	}
	if (_clock->getClockState() == AFTERNOON || _inventory->getHandItem()._kind == EII_TORCH) {
		_uimanager->reduceMental(REDUCEMENTAL, 0);
	}
	else if (_clock->getClockState() == EVENING) {
		_uimanager->reduceMental(REDUCEMENTAL, 2);
	}
	else {
		_uimanager->reduceMental(REDUCEMENTAL, 10);
	}
}

void Map::zOderCheck()
{
	int i;
	int j;

	i = CAMERAMANAGER->getStandardPoint().x / TILESIZEX;
	j = CAMERAMANAGER->getStandardPoint().y / TILESIZEY;

	for (int k = i + 1; k > i - 1; --k) {
		for (int l = j + 1; l > j - 1; --l) {
			if (vObjEnvi[k][l].getKind() != NONE_ENVIRONMENT)
			{
				zOderY = vObjEnvi[k][l].getPosition().y;
				return;
			}
		}
	}
}
