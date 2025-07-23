#pragma once
#include "Stdafx.h"

// 이미지 출력 방법
// 1. 파일 입출력 2. 리소스에 박고 쓰는 방법
// 외부에서 가져오는 방법이 용이

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
		// 프레임 관련 변수 추가
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
			// + 초기화
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
	// COLORREF: 윈도우에서 색상값을 표현하기 위한 데이터형 32비트 부호없는 정수형 -> RGB: 각각 1바이트 0 ~ 255 범위의 색상
	// 255, 0, 255 -> 마젠타 색상 많이 사용
	COLORREF		_transColor;

	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

public:
	// 빈 비트맵
	HRESULT init(int width, int height);

	// 이미지 삽입, 배경 삭제처리 + 프레임 관련 함수
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY,  bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));


	// 알파블렌드
	HRESULT initForAlphaBlend(void);

	// 투명 컬러키 세팅
	void setTransColor(bool isTrans, COLORREF transColor);

	// 메모리 해제
	void release(void);

	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);

	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	// 단일 이미지에 대한 처리 (설정자와 접근자)
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x; }

	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y; }

	void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	// 프레임에 대한 이미지 처리 (설정자와 접근자)
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

	// 이미지에 대한 너비와 높이
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	// 프레임에 대한 너비와 높이
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	GImage();
	~GImage() {}
};

