#include "ImageManager.h"

HRESULT ImageManager::init(void)
{
    // Do Nothing
    return S_OK;
}

void ImageManager::setTransColor(bool isTrans, COLORREF transColor)
{
}

void ImageManager::release(void)
{
    this->deleteAll();
}


ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
}

GImage* ImageManager::addImage(std::string strKey, int width, int height)
{
    GImage* img = findImage(strKey);

    if (img) return img;

    img = new GImage;
    if (FAILED(img->init(width, height)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    _mImageList.insert(make_pair(strKey, img));

    return img;
}

GImage* ImageManager::addImage(std::string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
    GImage* img = findImage(strKey);

    if (img) return img;

    img = new GImage;
    if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    _mImageList.insert(make_pair(strKey, img));

    return img;
}

GImage* ImageManager::addImage(std::string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
    GImage* img = findImage(strKey);

    if (img) return img;

    img = new GImage;
    if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    _mImageList.insert(make_pair(strKey, img));

    return img;
}

GImage* ImageManager::addFrameImage(std::string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    GImage* img = findImage(strKey);

    if (img) return img;

    img = new GImage;
    if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    _mImageList.insert(make_pair(strKey, img));

    return img;
}

GImage* ImageManager::addFrameImage(std::string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    GImage* img = findImage(strKey);

    if (img) return img;

    img = new GImage;
    if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    _mImageList.insert(make_pair(strKey, img));

    return img;
}

GImage* ImageManager::findImage(std::string strKey)
{
    auto key = _mImageList.find(strKey);

    if (key != _mImageList.end())
    {
        key->second->release();
        SAFE_DELETE(key->second);
        _mImageList.erase(key);

        return false;
    }

    return false;
}

// @!
bool ImageManager::deleteImage(std::string strKey)
{
    auto key = _mImageList.find(strKey);

    if (key != _mImageList.end())
    {
        key->second->release();
        SAFE_DELETE(key->second);
        _mImageList.erase(key);

        return false;
    }

    return false;
}

bool ImageManager::deleteAll()
{
    auto iter = _mImageList.begin();

    for (; iter != _mImageList.end();)
    {
        if (iter->second != nullptr)
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

    _mImageList.clear();

    return false;
}

void ImageManager::render(std::string strKey, HDC hdc)
{
    GImage* img = findImage(strKey);
    if (img) img->render(hdc);
}

void ImageManager::render(std::string strKey, HDC hdc, int destX, int destY)
{
    GImage* img = findImage(strKey);
    if (img) img->render(hdc, destX, destY);
}

void ImageManager::render(std::string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
    GImage* img = findImage(strKey);
    if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void ImageManager::alphaRender(std::string strKey, HDC hdc, BYTE alpha)
{                 
    GImage* img = findImage(strKey);
    if (img) img->alphaRender(hdc, alpha);
}                                                
                                                 
void ImageManager::alphaRender(std::string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{        
    GImage* img = findImage(strKey);
    if (img) img->alphaRender(hdc, destX, destY, alpha);
}                                                 
                                                  
void ImageManager::frameRender(std::string strKey, HDC hdc, int destX, int destY)
{        
    GImage* img = findImage(strKey);
    if (img) img->frameRender(hdc, destX, destY);
}                                                 
                                                  
void ImageManager::frameRender(std::string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
    GImage* img = findImage(strKey);
    if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}