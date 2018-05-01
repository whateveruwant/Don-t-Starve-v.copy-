#pragma once
#include "gameNode.h"

enum LOAD_KIND {
	LOAD_KIND_IMAGE_0,
	LOAD_KIND_IMAGE_1,
	LOAD_KIND_FRAMEIMAGE_0,
	LOAD_KIND_SOUND,
	LOAD_KIND_END
};

struct tagImageResource {
	tstring keyName;			// �̹��� Ű��
	const TCHAR* fileName;	// ���� �̸�
	int x, y;				// ��ġ ��ǥ
	int width, height;		// ���μ��� ũ��
	int frameX, frameY;		// ������ xy
};

struct tagSoundResource {
	string keyName;			// �̹��� Ű��
	string fileName;	// ���� �̸�
	bool bgm;
	bool loop;
};

class loadItem {
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;
	tagSoundResource _soundResource;
public:
	loadItem() {}
	~loadItem() {}

	// Ű������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT initForImage(tstring keyName, const TCHAR* fileName, int width, int height);
	HRESULT initForImage(tstring keyName, const TCHAR* fileName, int x, int y, int width, int height);
	// Ű������ ������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT initForFrameImage(tstring keyName, const TCHAR* fileName, int width, int height, int frameX, int frameY);
	// Ű������ ���� ���Ϸ� �ʱ�ȭ
	HRESULT initForSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);


	// �ε� ������ ���� ��������
	LOAD_KIND getLoadingKind() { return _kind; }
	tagImageResource getImageResource() { return _imageResource; }
	tagSoundResource getSoundResource() { return _soundResource; }
};

class loading : public gameNode
{
private:
	typedef vector<loadItem*> arrLoadItem;

private:
	arrLoadItem _vLoadItem;

	// �ε�ȭ�鿡�� ����� �̹��� �� �ε���
	image* _background;
	int _currentGauge;				// �ε��� ������

public:
	loading();
	~loading();

	HRESULT init();
	void release();
	void update();
	void render();



	// Ű������ �̹��� ���Ϸ� �ʱ�ȭ
	void loadImage(tstring keyName, const TCHAR* fileName, int width, int height);
	void loadImage(tstring keyName, const TCHAR* fileName, int x, int y, int width, int height);
	// Ű������ ������ �̹��� ���Ϸ� �ʱ�ȭ
	void loadFrameImage(tstring keyName, const TCHAR* fileName, int width, int height, int frameX, int frameY);
	//Ű������ ���� ���Ϸ� �ʱ�ȭ
	void loadSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);

	// �ε� �Ϸ� (�Ϸ� �� �� ����)
	BOOL loadingDone();

	// �ε������ ���� ��������
	arrLoadItem getLoadItem() { return _vLoadItem; }
};