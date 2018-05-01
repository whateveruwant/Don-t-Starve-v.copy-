#pragma once
#include "gameNode.h"
#include "loading.h"

class LoadingMainScene : public gameNode
{
private:
	loading* _loading;

public:
	LoadingMainScene();
	~LoadingMainScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void totalLoading();
};