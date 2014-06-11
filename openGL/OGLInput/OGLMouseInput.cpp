#include "./OGLMouseInput.h"
#include <stdio.h>

OGLMouseInput::OGLMouseInput(int sWidth, int sHeight, HWND &hWnd)
{
    this->mScreenCenterX    = (int) (sWidth / 2);
    this->mScreenCenterY    = (int) (sHeight / 2);

    this->mYaw              = 0.0f;
    this->mPitch            = 0.0f;
    this->mAngle            = 0.0f;

    this->mLastX            = 0;
    this->mLastY            = 0;

    this->mLeftButton       = false;
    this->mRightButton      = false;
    this->mScreenHandle     = hWnd;

    POINT p;
    GetCursorPos(&p);
    ScreenToClient(this->mScreenHandle, &p);

    this->mCurrentX         = p.x;
    this->mCurrentY         = p.y;
}

OGLMouseInput::~OGLMouseInput(void)
{
}

void OGLMouseInput::update(void)
{
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(this->mScreenHandle, &p);

    this->mLastX = this->mCurrentX;
    this->mLastY = this->mCurrentY;

    this->mCurrentX  = p.x;
    this->mCurrentY  = p.y;

    this->mPitch     = (float) (this->mLastY - p.y);
    this->mYaw       = (float) (this->mLastX - p.x);

    if(p.x != this->mScreenCenterX || p.y != this->mScreenCenterX)
    {

        this->mCurrentX = this->mScreenCenterX;
        this->mCurrentY = this->mScreenCenterY;

        this->mLastX = this->mCurrentX;
        this->mLastY = this->mCurrentY;

        p.x = this->mScreenCenterX;
        p.y = this->mScreenCenterY;

        ClientToScreen(this->mScreenHandle, &p);
        SetCursorPos(p.x, p.y);
    }
}

float OGLMouseInput::getAngle(void)
{
    return(this->mAngle * OGLPI / 180.0f);
}

float OGLMouseInput::getPitch(void)
{
    return(this->mPitch * OGLPI / 180.0f);
}

float OGLMouseInput::getYaw(void)
{
    return(this->mYaw * OGLPI / 180.0f);
}

int OGLMouseInput::getX(void)
{
    return(this->mCurrentX);
}

int OGLMouseInput::getY(void)
{
    return(this->mCurrentY);
}
