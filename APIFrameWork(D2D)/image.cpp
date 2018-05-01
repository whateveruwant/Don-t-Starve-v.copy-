#include "stdafx.h"
#include "image.h"

image::image() : _imageInfo(NULL), _fileName(NULL), _alpha(1.0f)
{
}


image::~image()
{
}

//이미지 파일로 초기화
HRESULT image::init(ID2D1RenderTarget* RenderTarget, const TCHAR* fileName, int width, int height)
{
	D2DLoadBitmap(fileName, RenderTarget, imagingFactory, &_bitmap);

	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_imageInfo != NULL) release();
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = wcslen(fileName);
	_fileName = new TCHAR[len + 1];
	wcsncpy_s(_fileName, len + 1, fileName, len + 1);

	return S_OK;
}

//프레임 이미지 파일로 초기화
HRESULT image::init(ID2D1RenderTarget* RenderTarget, const TCHAR* fileName, int width, int height, int frameX, int frameY)
{
	D2DLoadBitmap(fileName, RenderTarget, imagingFactory, &_bitmap);

	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_imageInfo != NULL) release();
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	int len = wcslen(fileName);
	_fileName = new TCHAR[len + 1];
	wcsncpy_s(_fileName, len + 1, fileName, len + 1);

	return S_OK;
}

HRESULT image::init(ID2D1RenderTarget * RenderTarget, const TCHAR * fileName, int width, int height, float x, float y)
{
	D2DLoadBitmap(fileName, RenderTarget, imagingFactory, &_bitmap);

	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_imageInfo != NULL) release();
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->x = x;
	_imageInfo->y = y;

	int len = wcslen(fileName);
	_fileName = new TCHAR[len + 1];
	wcsncpy_s(_fileName, len + 1, fileName, len + 1);

	return S_OK;
}

//==================================================================
//		## 일반렌더 ##
//==================================================================
void image::render(ID2D1RenderTarget* RenderTarget)
{
	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(0.0f, 0.0f, _imageInfo->width, _imageInfo->height), _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
}
void image::render(ID2D1RenderTarget* RenderTarget, float destX, float destY)
{
	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(destX, destY, destX + _imageInfo->width, destY + _imageInfo->height), _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	//RenderTarget->FillOpacityMask(_bitmap, WhiteSmokeBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS, &D2D1::RectF(destX, destY, destX + _imageInfo->width, destY + _imageInfo->height));
}
void image::bottomrender(ID2D1RenderTarget * RenderTarget, float destX, float destY)
{
	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(destX - _imageInfo->width / 2, destY - _imageInfo->height, destX + _imageInfo->width / 2, destY), _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
}
void image::centerRender(ID2D1RenderTarget* RenderTarget, float destX, float destY)
{
	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(destX - _imageInfo->width / 2, destY - _imageInfo->frameHeight, destX + _imageInfo->width / 2, destY), _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
}
void image::render(ID2D1RenderTarget* RenderTarget, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(destX, destY, destX + sourWidth, destY + sourHeight), _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(sourX, sourY, sourX + sourWidth, sourY + sourHeight));
}
void image::resizeRender(ID2D1RenderTarget* RenderTarget, RECTF rcf)
{
	RenderTarget->DrawBitmap(_bitmap, rcf, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
}


//==================================================================
//		## 알파렌더 ##
//==================================================================
void image::alphaRender(ID2D1RenderTarget* RenderTarget, int destX, int destY, float alpha)
{
	_alpha = alpha;
	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(destX, destY, destX + _imageInfo->width, destY + _imageInfo->height), _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
}

void image::alphaRender(ID2D1RenderTarget* RenderTarget, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, float alpha)
{
	_alpha = alpha;
	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(destX, destY, destX + sourWidth, destY + sourHeight), _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(sourX, sourY, sourX + sourWidth, sourY + sourHeight));

}

void image::resizeAlphaRender(ID2D1RenderTarget* RenderTarget, RECTF rcf, float alpha)
{
	_alpha = alpha;
	RenderTarget->DrawBitmap(_bitmap, rcf, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
}


//==================================================================
//		## 프레임렌더 ##
//==================================================================
void image::frameRender(ID2D1RenderTarget* RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}


	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(destX, destY, destX + _imageInfo->frameWidth, destY + _imageInfo->frameHeight),
		_alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, 
		D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX, 
					(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY, 
					(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1), 
					(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));
}

void image::frameBottomRender(ID2D1RenderTarget * RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}


	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(destX - _imageInfo->frameWidth / 2, destY - _imageInfo->frameHeight, destX + _imageInfo->frameWidth / 2, destY),
		_alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX,
		(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY,
			(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1),
			(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));
}

void image::frameCenterRender(ID2D1RenderTarget* RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}


	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(destX - _imageInfo->frameWidth / 2, 
													destY - _imageInfo->frameHeight / 2, 
													destX + _imageInfo->frameWidth / 2, 
													destY + _imageInfo->frameHeight / 2), 
		_alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, 
		D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX, 
					(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY, 
					(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1), 
					(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));
}
void image::frameAlphaRender(ID2D1RenderTarget* RenderTarget, int destX, int destY, int currentFrameX, int currentFrameY, float alpha)
{
	_alpha = alpha;
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}


	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(destX, destY, destX + _imageInfo->frameWidth, destY + _imageInfo->frameHeight), 
		_alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, 
		D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX, 
					(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY, 
					(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1), 
					(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));
}


void image::release()
{
	if (_imageInfo)
	{
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		//_bitmap->Release();
	}
}