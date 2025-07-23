#pragma once
#include "Stdafx.h"

// �̹��� ��� ���
// 1. ���� ����� 2. ���ҽ��� �ڰ� ���� ���
// �ܺο��� �������� ����� ����

class GImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0, LOAD_FILE,
		LOAD_EMPTY, LOAD_END
	};

	typedef struct tagImage
	{
		DWORD	resID;
		HDC		hMemDC;
		HBITMAP hBit;
		HBITMAP hOBIT;
		int		width;
		int		height;
		float	x;
		float	y;
		// ������ ���� ���� �߰�
		int currentFrameX;
		int currentFrameY;
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		BYTE	loadType;


		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBIT = NULL;
			width = 0;
			height = 0;
			// + �ʱ�ȭ
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, * LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	char*			_fileName;
	bool			_isTrans;
	// COLORREF: �����쿡�� ������ ǥ���ϱ� ���� �������� 32��Ʈ ��ȣ���� ������ -> RGB: ���� 1����Ʈ 0 ~ 255 ������ ����
	// 255, 0, 255 -> ����Ÿ ���� ���� ���
	COLORREF		_transColor;

	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

public:
	// �� ��Ʈ��
	HRESULT init(int width, int height);

	// �̹��� ����, ��� ����ó�� + ������ ���� �Լ�
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY,  bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));


	// ���ĺ���
	HRESULT initForAlphaBlend(void);

	// ���� �÷�Ű ����
	void setTransColor(bool isTrans, COLORREF transColor);

	// �޸� ����
	void release(void);

	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);

	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	// ���� �̹����� ���� ó�� (�����ڿ� ������)
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x; }

	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y; }

	void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	// �����ӿ� ���� �̹��� ó�� (�����ڿ� ������)
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// �̹����� ���� �ʺ�� ����
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	// �����ӿ� ���� �ʺ�� ����
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	GImage();
	~GImage() {}
};

