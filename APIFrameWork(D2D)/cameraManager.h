#pragma once
#include "gameNode.h"
#include "singletonBase.h"

class cameraManager :public singletonBase<cameraManager>
{
private:
	POINT* _standard;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	POINT getAbsPosition(const POINT _pt);

	void setPositionMemotyRick(POINT* _pt) { _standard = _pt; }
	POINT getStandardPoint() { return *_standard; }
};