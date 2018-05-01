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
	tstring keyName;			// 이미지 키값
	const TCHAR* fileName;	// 파일 이름
	int x, y;				// 위치 좌표
	int width, height;		// 가로세로 크기
	int frameX, frameY;		// 프레임 xy
};

struct tagSoundResource {
	string keyName;			// 이미지 키값
	string fileName;	// 파일 이름
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

	// 키값으로 이미지 파일로 초기화
	HRESULT initForImage(tstring keyName, const TCHAR* fileName, int width, int height);
	HRESULT initForImage(tstring keyName, const TCHAR* fileName, int x, int y, int width, int height);
	// 키값으로 프레임 이미지 파일로 초기화
	HRESULT initForFrameImage(tstring keyName, const TCHAR* fileName, int width, int height, int frameX, int frameY);
	// 키값으로 사운드 파일로 초기화
	HRESULT initForSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);


	// 로딩 아이템 종류 가져오기
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

	// 로딩화면에서 사용할 이미지 및 로딩바
	image* _background;
	int _currentGauge;				// 로딩바 게이지

public:
	loading();
	~loading();

	HRESULT init();
	void release();
	void update();
	void render();



	// 키값으로 이미지 파일로 초기화
	void loadImage(tstring keyName, const TCHAR* fileName, int width, int height);
	void loadImage(tstring keyName, const TCHAR* fileName, int x, int y, int width, int height);
	// 키값으로 프레임 이미지 파일로 초기화
	void loadFrameImage(tstring keyName, const TCHAR* fileName, int width, int height, int frameX, int frameY);
	//키값으로 사운드 파일로 초기화
	void loadSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);

	// 로딩 완료 (완료 후 씬 변경)
	BOOL loadingDone();

	// 로드아이템 벡터 가져오기
	arrLoadItem getLoadItem() { return _vLoadItem; }
};