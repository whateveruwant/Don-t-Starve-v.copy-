#include "stdafx.h"
#include "imageManager.h"
imageManager::imageManager()
{
}
imageManager::~imageManager()
{
}
//==================================================================
//		## ���̻� ������, �Ҹ��ڴ� ������� �ʴ´� ##
//==================================================================

//�̹����Ŵ��� �ʱ�ȭ
HRESULT imageManager::init(void)
{
	return S_OK;
}

//�̹����Ŵ��� ����
void imageManager::release(void)
{
	deleteAll();
}



//Ű������ �̹��� ���Ϸ� �ʱ�ȭ (�� ���)
image* imageManager::addImage(ID2D1RenderTarget* RenderTarget, tstring strKey, const TCHAR* fileName, int width, int height)
{
	//�߰� �Ϸ��� Ű ������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰� �Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�̹��� ���� ����
	img = new image;
	//�̹����� ����� �ʱ�ȭ�� ���� �ʾҴٸ� NULL ����
	if (FAILED(img->init(RenderTarget, fileName, width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� �����θ��� �̹��� ��Ͽ� �߰��Ѵ�
	//_mImageList.insert(pair<tstring, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::addFrameImage(ID2D1RenderTarget* RenderTarget, tstring strKey, const TCHAR* fileName, int width, int height, int frameX, int frameY)
{
	//�߰� �Ϸ��� Ű ������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰� �Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�̹��� ���� ����
	img = new image;
	//�̹����� ����� �ʱ�ȭ�� ���� �ʾҴٸ� NULL ����
	if (FAILED(img->init(RenderTarget, fileName, width, height, frameX, frameY)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� �����θ��� �̹��� ��Ͽ� �߰��Ѵ�
	//_mImageList.insert(pair<tstring, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(ID2D1RenderTarget * RenderTarget, tstring strKey, const TCHAR * fileName, int width, int height, int x, int y)
{
	//�߰� �Ϸ��� Ű ������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰� �Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�̹��� ���� ����
	img = new image;
	//�̹����� ����� �ʱ�ȭ�� ���� �ʾҴٸ� NULL ����
	if (FAILED(img->init(RenderTarget, fileName, width, height, x, y)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� �����θ��� �̹��� ��Ͽ� �߰��Ѵ�
	//_mImageList.insert(pair<tstring, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//�̹��� Ű������ ã��
image* imageManager::findImage(tstring strKey)
{
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (key != _mImageList.end())
	{
		return key->second;
	}

	//�˻��� Ű�� �̹����� ��ã�Ҵٸ� NULL
	return NULL;
}
bool imageManager::searchImage(tstring strKey)
{
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (key != _mImageList.end())
	{
		return true;
	}

	//�˻��� Ű�� �̹����� ��ã�Ҵٸ� NULL
	return false;
}

//�̹��� Ű������ ����
BOOL imageManager::deleteImage(tstring strKey)
{
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (key != _mImageList.end())
	{
		//�̹��� ����
		key->second->release();
		//�޸� ����
		SAFE_DELETE(key->second);
		//�ʿ��� �ݺ��� ����
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

//�̹��� ��ü ����
BOOL imageManager::deleteAll(void)
{
	//�� ��ü�� ���鼭 �����
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

	//�� ��ü ����
	_mImageList.clear();

	return TRUE;
}

//==================================================================
//		## �Ϲݷ��� ##
//==================================================================
void imageManager::render(tstring strKey, ID2D1RenderTarget* RenderTarget)
{
	//�̹����� ã���� ����
	image* img = findImage(strKey);
	if (img) img->render(RenderTarget);
}
void imageManager::render(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY)
{
	//�̹����� ã���� ����
	image* img = findImage(strKey);
	if (img) img->render(RenderTarget, destX, destY);
}
void imageManager::bottomrender(tstring strKey, ID2D1RenderTarget * RenderTarget, float destX, float destY)
{
	//�̹����� ã���� ����
	image* img = findImage(strKey);
	if (img) img->bottomrender(RenderTarget, destX, destY);
}
void imageManager::centerRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY)
{
	//�̹����� ã���� ����
	image* img = findImage(strKey);
	if (img) img->centerRender(RenderTarget, destX, destY);
}
void imageManager::render(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	//�̹����� ã���� ����
	image* img = findImage(strKey);
	if (img) img->render(RenderTarget, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::resizeRender(tstring strKey, ID2D1RenderTarget* RenderTarget, RECTF rcf)
{
	//�̹����� ã���� ����
	image* img = findImage(strKey);
	if (img) img->resizeRender(RenderTarget, rcf);
}

//==================================================================
//		## ���ķ��� ##
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
//		## �����ӷ��� ##
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
//		## �������� ##
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
