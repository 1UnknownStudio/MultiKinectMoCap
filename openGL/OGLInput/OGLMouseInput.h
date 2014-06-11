#pragma once

#include <Windows.h>
#include <cmath>

#define OGLPI   3.14159265f
#define OGL2PI  2.0f * 3.14159265f
#define OGL12PI 0.5f * 3.14159265f

class OGLMouseInput
{
    private:
        int mScreenCenterX;
        int mScreenCenterY;

        int mCurrentX;
        int mCurrentY;

        int mLastX;
        int mLastY;

        float mYaw;
        float mPitch;
        float mAngle;

        bool mLeftButton;
        bool mRightButton;

        HWND mScreenHandle;

    public:
        OGLMouseInput           (int, int, HWND &);
        ~OGLMouseInput          (void);

        void    update          (void);
        
        float    getAngle       (void);
        float    getPitch       (void);
        float    getYaw         (void);

        int     getX            (void);
        int     getY            (void);
};
