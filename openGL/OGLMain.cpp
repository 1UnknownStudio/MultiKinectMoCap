#include "./OGLMain.h"

OGLMain::OGLMain(const HWND &hWnd)
{
    this->mWndInstance        = hWnd;
    this->mRenderContext    = NULL;
    this->mDeviceContext    = NULL;

    this->mTimer            = NULL;
    this->mKinectManager    = NULL;
    this->mProgramShader    = NULL;

    this->mYaw              = 0.0f;
    this->mPitch            = 0.0f;
}

OGLMain::~OGLMain(void)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(this->mRenderContext);
    ReleaseDC(this->mWndInstance, this->mDeviceContext);

    this->mDeviceContext = NULL;
    this->mRenderContext = NULL;

    delete(this->mProgramShader);
    this->mProgramShader = NULL;

    delete(this->mKinectManager);
    this->mKinectManager = NULL;

    delete(this->mTimer);
    this->mTimer = NULL;
}

bool OGLMain::initialize(void)
{
    bool oK = false;
    PIXELFORMATDESCRIPTOR pFormat;

    memset(&pFormat, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pFormat.dwFlags        = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

    pFormat.nSize        = sizeof(PIXELFORMATDESCRIPTOR);
    pFormat.nVersion    = 1;

    pFormat.iPixelType    = LPD_TYPE_RGBA;
    pFormat.cColorBits    = 32;
    pFormat.cDepthBits    = 24;

    if((this->mDeviceContext = GetDC(this->mWndInstance)) != NULL)
    {
        if(SetPixelFormat(this->mDeviceContext, ChoosePixelFormat(this->mDeviceContext, &pFormat), &pFormat) == TRUE)
        {
            if((this->mRenderContext = wglCreateContext(this->mDeviceContext)) != NULL)
            {
                oK = (wglMakeCurrent(this->mDeviceContext, this->mRenderContext) == TRUE);
            }
        }
    }

    glewInit();
    wglSwapIntervalEXT(false);

    this->mTimer = new OGLTimer(0);
    this->mKinectManager = new CKinectManager();

    this->mProgramShader = new OGLShaderProgram(new OGLShader("./simple.vert", GL_VERTEX_SHADER), new OGLShader("./simple.frag", GL_FRAGMENT_SHADER));
    this->mProgramShader->activeProgram();

    return(oK);
}

void OGLMain::update(void)
{
    this->mTimer->update();
    this->mKinectManager->Update();

    this->mKinectManager->RefreshNumKinects();
    //this->mKinectManager->BestPositionSkeletonPoint();
    this->mKinectManager->BestPositionSkeletonPointAverage();
    //this->mKinectManager->ArithmeticAverageProcessSkeleton();

    float aspect = (float)(GetSystemMetrics(SM_CXSCREEN) / GetSystemMetrics(SM_CYSCREEN));
    aspect = (aspect < 1.0f) ? (float)(GetSystemMetrics(SM_CYSCREEN) / GetSystemMetrics(SM_CXSCREEN)) : aspect;

    this->mFrustunMatrix.setFrustum(90.0f, aspect, 0.1f, 1000.0f);
    this->mLookAtMatrix.setLookAt(OGLVector4f(0.0f, 0.5f, -0.1f), OGLVector4f(0.0f, 0.0f, 1.0f), OGLVector4f(0.0f, 1.0f, 0.0f));
}

void OGLMain::render(void)
{
    static float a = 0.0f;
    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    OGLMatrix4f modelMatrix;
    this->mProgramShader->activeProgram();

    this->mProgramShader->setUniformMatrix4("projectionMatrix", false, this->mFrustunMatrix.m_pMatrix4f);
    this->mProgramShader->setUniformMatrix4("viewMatrix", false, this->mLookAtMatrix.m_pMatrix4f);
    this->mProgramShader->setUniformMatrix4("modelMatrix", true, modelMatrix.m_pMatrix4f);

    OGLDebugRender dRender;
    dRender.drawGrid(50, 50.0f, OGLVector4f(1.0f, 1.0f, 1.0f));
    dRender.drawAxis(OGLVector4f(0.0f, 0.0f, 0.0f), 6.0f);

    this->mKinectManager->Draw();
    this->mProgramShader->releseProgram();

    wchar_t buffer[80] = {0};
    swprintf_s(buffer, L"FPS: %d", this->mTimer->getFps());

    SwapBuffers(this->mDeviceContext);
    SetWindowText(this->mWndInstance, buffer);
}
