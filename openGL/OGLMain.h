#pragma 
#include <Windows.h>
#include <gl\glew.h>
#include <gl\wglew.h>

#include <cmath>
#include <ctime>

#include "./../kinect/CKinect.h"
#include "./../kinect/CKinectManager.h"

#include "./OGLMath/OGLVector4f.h"
#include "./OGLMath/OGLMatrix4f.h"

#include "./OGLDebugRender/OGLDebugRender.h"
#include "./OGLInput/OGLKeyboardInput.h"

#include "./OGLTimer/OGLTimer.h"
#include "./OGLShader/OGLShader.h"
#include "./OGLShader/OGLShaderProgram.h"

class OGLMain
{
    private:
        HDC     mDeviceContext;
        HGLRC   mRenderContext;
        HWND    mWndInstance;


        OGLShaderProgram *mProgramShader;
        CKinectManager *mKinectManager;
        OGLTimer *mTimer;

        OGLKeyboardInput mKeyboard;
        OGLMatrix4f mFrustunMatrix;
        OGLMatrix4f mLookAtMatrix;

        int mFun;
        int mDrw;

        float mYaw;
        float mPitch;

    public:
        OGLMain            (const HWND &);
        ~OGLMain           (void);

        void render        (void);
        void update        (void);
        bool initialize    (void);
};
