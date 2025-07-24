#pragma once
#include "SingletonBase.h"
#include "GImage.h"

class ImageManager : public SingletonBase <ImageManager>
{
private:
	typedef std::map<std::string, GImage*> mapImageList;
	typedef std::map<std::string, GImage*> ::iterator mapImageIter;

private:
	mapImageList _mImageList;

public:
	HRESULT init(void);
	void release(void);


	GImage* addImage(std::string strKey, int width, int height);
	GImage* addImage(std::string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addImage(std::string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(std::string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(std::string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	GImage* findImage(std::string strKey);
	bool deleteImage(std::string strKey);
	bool deleteAll();

	void setTransColor(bool isTrans, COLORREF transColor);

	void render(std::string strKey, HDC hdc);
	void render(std::string strKey, HDC hdc, int destX, int destY);
	void render(std::string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void alphaRender(std::string strKey, HDC hdc, BYTE alpha);
	void alphaRender(std::string strKey, HDC hdc, int destX, int destY, BYTE alpha);

	void frameRender(std::string strKey, HDC hdc, int destX, int destY);
	void frameRender(std::string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	ImageManager();
	~ImageManager();

};


