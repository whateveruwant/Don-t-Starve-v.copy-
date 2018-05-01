#pragma once
#include "gameNode.h"
#include "loading.h"

class LoadingGameScene : public gameNode
{
private:
	loading* _loading;

public:
	LoadingGameScene();
	~LoadingGameScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void totalLoading();
};

