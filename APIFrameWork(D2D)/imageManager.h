#pragma once

#include "singletonBase.h"
#include "image.h"
//==================================================================
//		## imageManager ## (�̹��� �Ŵ���)
//==================================================================

class imageManager : public singletonBase <imageManager>
{
private:
	typedef map<tstring, image*> mapImageList;			//������ ���� �̹������
	typedef map<tstring, image*>::iterator mapImageIter;	//������ ���� �̹�������� �ݺ���

private:
	mapImageList _mImageList;	//������ ������ �̹������

public:
	//�̹����Ŵ��� �ʱ�ȭ
	HRESULT init(void);
	//�̹����Ŵ��� ����
	void release(void);

	//Ű������ �̹��� ���Ϸ� �ʱ�ȭ (�� ���)
	image* addImage(ID2D1RenderTarget* RenderTarget, tstring strKey, const TCHAR* fileName, int width, int height);
	//Ű������ ������ �̹��� ���Ϸ� �ʱ�ȭ
	image* addFrameImage(ID2D1RenderTarget* RenderTarget, tstring strKey, const TCHAR* fileName, int width, int height, int frameX, int frameY);

	image* addImage(ID2D1RenderTarget* RenderTarget, tstring strKey, const TCHAR* fileName, int width, int height, int x, int y);

	//�̹��� Ű������ ã��
	image* findImage(tstring strKey);
	bool searchImage(tstring strKey);
	//�̹��� Ű������ ����
	BOOL deleteImage(tstring strKey);
	//�̹��� ��ü ����
	BOOL deleteAll(void);

	//==================================================================
	//		## �Ϲݷ��� ##
	//==================================================================
	void render(tstring strKey, ID2D1RenderTarget* RenderTarget);
	void render(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY);
	void bottomrender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY);
	void centerRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY);
	void render(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);
	void resizeRender(tstring strKey, ID2D1RenderTarget* RenderTarget, D2D1_RECT_F rcf);

	//==================================================================
	//		## ���ķ��� ##
	//==================================================================
	void alphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, float alpha);
	void alphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, float alpha);
	void resizeAlphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, D2D1_RECT_F rcf, float alpha);

	//==================================================================
	//		## �����ӷ��� ##
	//==================================================================
	void frameRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY);
	void frameBottomRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY);
	void frameCenterRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY);
	void frameAlphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float destX, float destY, int currentFrameX, int currentFrameY, float alpha);


	//==================================================================
	//		## �������� ##
	//==================================================================
	//void loopRender(tstring strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	//void loopAlphaRender(tstring strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);


	imageManager();
	~imageManager();
};

