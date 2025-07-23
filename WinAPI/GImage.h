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
		BYTE	loadType;

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBIT = NULL;
			width = 0;
			height = 0;
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

	// �̹��� ����, ��� ����ó��
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

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

	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	GImage();
	~GImage() {}
};

