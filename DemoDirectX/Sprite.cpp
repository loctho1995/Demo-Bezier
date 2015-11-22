#include "Sprite.h"
#include "GameLog.h"

Sprite::Sprite(const char* filePath, RECT *sourceRect, int width, int height, D3DCOLOR colorKey)
{    
    this->InitWithSprite(filePath, sourceRect, width, height, colorKey);
}

Sprite::Sprite()
{
    
}

Sprite::~Sprite()
{
    if (mTexture != NULL)
        mTexture->Release();

    if (mSourceRect != NULL)
    {
        delete mSourceRect;
        mSourceRect = NULL;
    }        
}

void Sprite::InitWithSprite(const char* filePath, RECT *sourceRect, int width, int height, D3DCOLOR colorKey)
{
    HRESULT result;
    mSpriteHandler = GameGlobal::GetCurrentSpriteHandler();
    mPosition = D3DXVECTOR3(0, 0, 0);
    mRotation = 0;
    mRotationCenter = D3DXVECTOR2(mPosition.x, mPosition.y);
    mTranslation = D3DXVECTOR2(0, 0);
    mScalingCenter = D3DXVECTOR2(0, 0);
    mScale = D3DXVECTOR2(0, 1);
    mIsMatrixManually = false;

    if (sourceRect != NULL)
        mSourceRect = new RECT(*sourceRect);

    //convert from char* to LPWSTR
    //size_t size = mbsrtowcs(NULL, &filePath, 0, NULL);
    //LPWSTR file = new wchar_t(size + 1);
    //mbsrtowcs(file, &filePath, size + 1, NULL);
    //convert from LPWSTR to char*

#if _DEBUG
    result = D3DXGetImageInfoFromFileA(filePath, &mImageInfo);

    if (result != D3D_OK)
    {
        GAMELOG("[Error] get image info failed %s", filePath);
        return;
    }
#endif

    if (width == NULL)
    {
        if (sourceRect == NULL)
            mWidth = mImageInfo.Width;
        else
            mWidth = sourceRect->right - sourceRect->left;
    }
    else
        mWidth = width;

    if (height == NULL)
    {
        if (sourceRect == NULL)
            mHeight = mImageInfo.Height;
        else
            mHeight = sourceRect->bottom - sourceRect->top;
    }
    else
        mHeight = height;

    LPDIRECT3DDEVICE9 device;
    mSpriteHandler->GetDevice(&device);

    result = D3DXCreateTextureFromFileExA(
        device,
        filePath,
        mImageInfo.Width,
        mImageInfo.Height,
        1,
        D3DUSAGE_DYNAMIC,
        D3DFMT_UNKNOWN,
        D3DPOOL_DEFAULT,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        colorKey,
        &mImageInfo,
        NULL,
        &mTexture);

    if (result != D3D_OK)
    {
        GAMELOG("[Error] create texture failed %s", filePath);
        return;
    }

    mScale.x = mScale.y = 1;

    //if (mSourceRect != NULL)
    //{
    //    mScale.x = mWidth / (float)mImageInfo.Width;
    //    mScale.y = mHeight / (float)mImageInfo.Height;
    //}
    //else
    //{
    //    mScale.x = mScale.y = 1;
    //}
}

int Sprite::GetWidth()
{
    return mWidth;
}

int Sprite::GetHeight()
{
    return mHeight;
}

//void Sprite::Draw()
//{
//    if (!mIsMatrixManually)
//    {   
//        mRotationCenter = D3DXVECTOR2(mPosition.x, mPosition.y);// cho phep quay giua hinh
//        mScalingCenter = D3DXVECTOR2(mPosition.x, mPosition.y); 
//        //mScale = D3DXVECTOR2(1, -1); x = -1 flip theo truc 0y, y = -1 flip theo truc Ox
//
//        D3DXMatrixTransformation2D(&mMatrix, &mScalingCenter, 0, &mScale, &mRotationCenter, mRotation, &mTranslation);        
//    }
//    D3DXMATRIX oldMatrix;
//    mSpriteHandler->GetTransform(&oldMatrix);
//
//    mSpriteHandler->SetTransform(&mMatrix);
//
//    mSpriteHandler->Draw(mTexture,
//                        mSourceRect,
//                        NULL,
//                        new D3DXVECTOR3(mPosition.x - mWidth / 2, mPosition.y - mHeight / 2 , 1),
//                        D3DCOLOR_XRGB(255, 255, 255));
//
//    mSpriteHandler->SetTransform(&oldMatrix); // set lai matrix cu~ de Sprite chi ap dung transfrom voi class nay
//}

void Sprite::Draw(D3DXVECTOR3 position, RECT *sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXVECTOR2 scalingCenter, D3DXCOLOR colorKey)
{
    mScalingCenter = D3DXVECTOR2(mPosition.x, mPosition.y);

    D3DXVECTOR3 inPosition = mPosition;
    RECT *inSourceRect = mSourceRect;
    float inRotation = mRotation;
    D3DXVECTOR2 inCcale = mScale;
    D3DXVECTOR2 inTranslation = mTranslation;
    D3DXVECTOR2 inRotationCenter = mRotationCenter;
    D3DXVECTOR2 inScalingCenter = mScalingCenter;   

    if (!mIsMatrixManually)
    {
        if (position != D3DXVECTOR3())
            inPosition = position;

        if (sourceRect != NULL)
            inSourceRect = sourceRect;

        if (scale != D3DXVECTOR2())
            inCcale = scale;

        if (transform != D3DXVECTOR2())
            inTranslation = transform;

        if (rotationCenter != D3DXVECTOR2())
            inRotationCenter = rotationCenter;
        else
            mRotationCenter = D3DXVECTOR2(inPosition.x, inPosition.y);// cho phep quay giua hinh

        if (scalingCenter != D3DXVECTOR2())
            inScalingCenter = scalingCenter;


        //mScale = D3DXVECTOR2(1, -1); x = -1 flip theo truc 0y, y = -1 flip theo truc Ox

        D3DXMatrixTransformation2D(&mMatrix, &inScalingCenter, 0, &inCcale, &inRotationCenter, inRotation, &inTranslation);
    }

    D3DXMATRIX oldMatrix;
    mSpriteHandler->GetTransform(&oldMatrix);
    mSpriteHandler->SetTransform(&mMatrix);

    mSpriteHandler->Draw(mTexture,
        inSourceRect,
        NULL,
        new D3DXVECTOR3(inPosition.x - mWidth / 2, inPosition.y - mHeight / 2, 0),
        D3DCOLOR_ARGB(255, 255, 255, 255)); // nhung pixel nao co mau trang se duoc to mau nay len

    mSpriteHandler->SetTransform(&oldMatrix); // set lai matrix cu~ de Sprite chi ap dung transfrom voi class nay
}

void Sprite::SetSourceRect(RECT *rect)
{
    mSourceRect = rect;
}

LPDIRECT3DTEXTURE9 Sprite::GetTexture()
{
    return mTexture;
}

void Sprite::SetPosition(D3DXVECTOR3 pos)
{
    mPosition = pos;
}

void Sprite::SetPosition(float x, float y)
{
    mPosition = D3DXVECTOR3(x, y, 0);
}

void Sprite::SetPosition(D3DXVECTOR2 pos)
{
    this->SetPosition(pos.x, pos.y);
}

D3DXVECTOR3 Sprite::GetPosition()
{
    return mPosition;
}

D3DXVECTOR2 Sprite::GetScale()
{
    return mScale;
}

void Sprite::SetScale(D3DXVECTOR2 scale)
{
    mScale = scale;
}

D3DXVECTOR2 Sprite::GetTranslation()
{
    return mTranslation;
}

void Sprite::SetTranslation(D3DXVECTOR2 translation)
{
    mTranslation = translation;
}

D3DMATRIX Sprite::GetMatrix()
{
    return mMatrix;
}

void Sprite::SetMatrix(D3DXMATRIX matrix)
{
    mMatrix = matrix;
}

void Sprite::SetMatrixManuallyFlag(bool flag)
{
    mIsMatrixManually = flag;
}

D3DXVECTOR2 Sprite::GetScalingCenter()
{
    return mScalingCenter;
}

void Sprite::SetScalingCenter(D3DXVECTOR2 scalingCenter)
{
    mScalingCenter = scalingCenter;
}

D3DXVECTOR2 Sprite::GetRotationCenter()
{
    return mRotationCenter;
}

void Sprite::SetRotationCenter(D3DXVECTOR2 rotationCenter)
{
    mRotationCenter = rotationCenter;
}

float Sprite::GetRotation()
{
    return mRotation;
}

void Sprite::SetRotation(float rotation) 
{
    mRotation = rotation;
}

float Sprite::GetScaleCenter()
{
    return mScaleCenter;
}

void Sprite::SetScaleCenter(float scaleCenter)
{
    mScaleCenter = scaleCenter;
}

D3DXIMAGE_INFO Sprite::GetImageInfo()
{
    return mImageInfo;
}

void Sprite::FlipHorizontal(bool flag)
{
    if (mIsFlipHorizontal != flag)
    {
        mIsFlipHorizontal = flag;
        mScale = D3DXVECTOR2(mScale.x, -mScale.y);
    }
        
}

void Sprite::FlipVertical(bool flag)
{
    if (mIsFlipVertical != flag)
    {
        mIsFlipVertical = flag;
        mScale = D3DXVECTOR2(-mScale.x, mScale.y);
    }
        
}

bool Sprite::IsFlipHorizontal()
{
    return mIsFlipHorizontal;
}

bool Sprite::IsFlipVertical()
{
    return mIsFlipVertical;
}

void Sprite::SetWidth(int width)
{
    mWidth = width;
}

void Sprite::SetHeight(int height)
{
    mHeight = height;
}