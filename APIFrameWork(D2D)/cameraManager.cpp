#include "stdafx.h"
#include "cameraManager.h"


cameraManager::cameraManager()
{
}


cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::update()
{
}

void cameraManager::render()
{
}

POINT cameraManager::getAbsPosition(const POINT _pt)
{
	POINT tmp;
	tmp.x = _pt.x - _standard->x + WINSIZEX_NUM / 2;
	tmp.y = _pt.y - _standard->y + WINSIZEY_NUM / 2;
	return tmp;
}