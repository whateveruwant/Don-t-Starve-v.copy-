#pragma once
#include "gameNode.h"
#include "loading.h"

class LoadingMapScene : public gameNode
{
	loading* _loading;

public:
	LoadingMapScene();
	~LoadingMapScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void totalLoading();
};