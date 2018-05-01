#include "stdafx.h"
#include "imageManager.h"
imageManager::imageManager()
{
}
imageManager::~imageManager()
{
}
//==================================================================
//		## 더이상 생성자, 소멸자는 사용하지 않는다 ##
//==================================================================

//이미지매니져 초기화
HRESULT imageManager::init(void)
{
	return S_OK;
}

//이미지매니져 해제
void imageManager::release(void)
{
	deleteAll();
}



//키값으로 이미지 파일로 초기화 (주 사용)
image* imageManager::addImage(ID2D1RenderTarget* RenderTarget, tstring strKey, const TCHAR* fileName, int width, int height)
{
	//추가 하려는 키 값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가 하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴시킨다
	if (img) return img;

	//이미지 새로 생성
	img = new image;
	//이미지가 제대로 초기화가 되지 않았다면 NULL 리턴
	if (FAILED(img->init(RenderTarget, fileName, width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지를 맵으로만든 이미지 목록에 추가한다
	//_mImageList.insert(pair<tstring, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::addFrameImage(ID2D1RenderTarget* RenderTarget, tstring strKey, const TCHAR* fileName, int width, int height, int frameX, int frameY)
{
	//추가 하려는 키 값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가 하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴시킨다
	if (img) return img;

	//이미지 새로 생성
	img = new image;
	//이미지가 제대로 초기화가 되지 않았다면 NULL 리턴
	if (FAILED(img->init(RenderTarget, fileName, width, height, frameX, frameY)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지를 맵으로만든 이미지 목록에 추가한다
	//_mImageList.insert(pair<tstring, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(ID2D1RenderTarget * RenderTarget, tstring strKey, const TCHAR * fileName, int width, int height, int x, int y)
{
	//추가 하려는 키 값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가 하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴시킨다
	if (img) return img;

	//이미지 새로 생성
	img = new image;
	//이미지가 제대로 초기화가 되지 않았다면 NULL 리턴
	if (FAILED(img->init(RenderTarget, fileName, width, height, x, y)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지를 맵으로만든 이미지 목록에 추가한다
	//_mImageList.insert(pair<tstring, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//이미지 키값으로 찾기
image* imageManager::findImage(tstring strKey)
{
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면
	if (key != _mImageList.end())
	{
		return key->second;
	}

	//검색한 키로 이미지를 못찾았다면 NULL
	return NULL;
}
bool imageManager::searchImage(tstring strKey)
{
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면
	if (key != _mImageList.end())
	{
		return true;
	}

	//검색한 키로 이미지를 못찾았다면 NULL
	return false;
}

//이미지 키값으로 삭제
BOOL imageManager::deleteImage(tstring strKey)
{
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면
	if (key != _mImageList.end())
	{
		//이미지 해제
		key->second->release();
		//메모리 해제
		SAFE_DELETE(key->second);
		//맵에서 반복자 삭제
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

//이미지 전체 삭제
BOOL imageManager::deleteAll(void)
{
	//맵 전체를 돌면서 지운다
	mapImageIter iter = _mImageList.begin();
	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	//맵 전체 삭제
	_mImageList.clear();

	return TRUE;
}

//==================================================================
//		## 일반렌더 ##
//==================================================================
void imageManager::render(tstring strKey, ID2D1RenderTarget* RenderTarget)
{
	//이미지를 찾은후 렌더
	image* img = findImage(strKey);
	if (img) img->render(RenderTarget);
}
void imageManager::render(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY)
{
	//이미지를 찾은후 렌더
	image* img = findImage(strKey);
	if (img) img->render(RenderTarget, destX, destY);
}
void imageManager::bottomrender(tstring strKey, ID2D1RenderTarget * RenderTarget, float destX, float destY)
{
	//이미지를 찾은후 렌더
	image* img = findImage(strKey);
	if (img) img->bottomrender(RenderTarget, destX, destY);
}
void imageManager::centerRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY)
{
	//이미지를 찾은후 렌더
	image* img = findImage(strKey);
	if (img) img->centerRender(RenderTarget, destX, destY);
}
void imageManager::render(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	//이미지를 찾은후 렌더
	image* img = findImage(strKey);
	if (img) img->render(RenderTarget, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::resizeRender(tstring strKey, ID2D1RenderTarget* RenderTarget, RECTF rcf)
{
	//이미지를 찾은후 렌더
	image* img = findImage(strKey);
	if (img) img->resizeRender(RenderTarget, rcf);
}

//==================================================================
//		## 알파렌더 ##
//==================================================================
void imageManager::alphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, float alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(RenderTarget, destX, destY, alpha);
}
void imageManager::alphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, float alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(RenderTarget, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::resizeAlphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, RECTF rcf, float alpha)
{
	image* img = findImage(strKey);
	if (img) img->resizeAlphaRender(RenderTarget, rcf, alpha);
}



//==================================================================
//		## 프레임렌더 ##
//==================================================================
void imageManager::frameRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(RenderTarget, destX, destY, currentFrameX, currentFrameY);
}
void imageManager::frameBottomRender(tstring strKey, ID2D1RenderTarget * RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);
	if (img) img->frameBottomRender(RenderTarget, destX, destY, currentFrameX, currentFrameY);
}
void imageManager::frameCenterRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);
	if (img) img->frameCenterRender(RenderTarget, destX, destY, currentFrameX, currentFrameY);
}
void imageManager::frameAlphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY, float alpha)
{
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(RenderTarget, destX, destY, currentFrameX, currentFrameY, alpha);
}



//==================================================================
//		## 루프렌더 ##
//==================================================================
//void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
//{
//	image* img = findImage(strKey);
//	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
//}
//void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
//{
//	image* img = findImage(strKey);
//	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
//}
