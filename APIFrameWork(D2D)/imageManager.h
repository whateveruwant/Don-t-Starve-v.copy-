#pragma once

#include "singletonBase.h"
#include "image.h"
//==================================================================
//		## imageManager ## (이미지 매니져)
//==================================================================

class imageManager : public singletonBase <imageManager>
{
private:
	typedef map<tstring, image*> mapImageList;			//맵으로 만든 이미지목록
	typedef map<tstring, image*>::iterator mapImageIter;	//맵으로 만든 이미지목록의 반복자

private:
	mapImageList _mImageList;	//맵으로 구현된 이미지목록

public:
	//이미지매니져 초기화
	HRESULT init(void);
	//이미지매니져 해제
	void release(void);

	//키값으로 이미지 파일로 초기화 (주 사용)
	image* addImage(ID2D1RenderTarget* RenderTarget, tstring strKey, const TCHAR* fileName, int width, int height);
	//키값으로 프레임 이미지 파일로 초기화
	image* addFrameImage(ID2D1RenderTarget* RenderTarget, tstring strKey, const TCHAR* fileName, int width, int height, int frameX, int frameY);

	image* addImage(ID2D1RenderTarget* RenderTarget, tstring strKey, const TCHAR* fileName, int width, int height, int x, int y);

	//이미지 키값으로 찾기
	image* findImage(tstring strKey);
	bool searchImage(tstring strKey);
	//이미지 키값으로 삭제
	BOOL deleteImage(tstring strKey);
	//이미지 전체 삭제
	BOOL deleteAll(void);

	//==================================================================
	//		## 일반렌더 ##
	//==================================================================
	void render(tstring strKey, ID2D1RenderTarget* RenderTarget);
	void render(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY);
	void bottomrender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY);
	void centerRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY);
	void render(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);
	void resizeRender(tstring strKey, ID2D1RenderTarget* RenderTarget, D2D1_RECT_F rcf);

	//==================================================================
	//		## 알파렌더 ##
	//==================================================================
	void alphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, float alpha);
	void alphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, float alpha);
	void resizeAlphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, D2D1_RECT_F rcf, float alpha);

	//==================================================================
	//		## 프레임렌더 ##
	//==================================================================
	void frameRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY);
	void frameBottomRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY);
	void frameCenterRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY);
	void frameAlphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY, float alpha);


	//==================================================================
	//		## 루프렌더 ##
	//==================================================================
	//void loopRender(tstring strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	//void loopAlphaRender(tstring strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);


	imageManager();
	~imageManager();
};

