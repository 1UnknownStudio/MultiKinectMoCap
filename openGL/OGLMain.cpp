#include "./OGLMain.h"

OGLMain::OGLMain(const HWND &hWnd)
{
    this->mWndInstance      = hWnd;
    this->mRenderContext    = NULL;
    this->mDeviceContext    = NULL;

    this->mTimer            = NULL;
    this->mKinectManager    = NULL;
    this->mProgramShader    = NULL;

    this->mFun              = 0;
    this->mDrw              = 0;

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
    glEnable(GL_SCISSOR_TEST);
    wglSwapIntervalEXT(false);

    this->mTimer = new OGLTimer(0);
    this->mKinectManager = new CKinectManager();
    this->mProgramShader = new OGLShaderProgram(new OGLShader("./simple.vert", GL_VERTEX_SHADER), new OGLShader("./simple.frag", GL_FRAGMENT_SHADER));

    this->mKeyboard.addKey("1", 0x31); this->mKeyboard.addKey("2", 0x32);
    this->mKeyboard.addKey("3", 0x33); this->mKeyboard.addKey("4", 0x34);

    this->mKeyboard.addKey("d", 0x44); this->mKeyboard.addKey("f", 0x46);

    return(oK);
}

void OGLMain::update(void)
{
    this->mTimer->update();
    this->mKeyboard.update();

    this->mKinectManager->Update();
    this->mKinectManager->RefreshNumKinects();

    if (this->mKeyboard.isKeyPressed("1") && this->mTimer->endOfTime("1", 0.5)) this->mFun = 0;
    if (this->mKeyboard.isKeyPressed("2") && this->mTimer->endOfTime("2", 0.5)) this->mFun = 1;
    if (this->mKeyboard.isKeyPressed("3") && this->mTimer->endOfTime("3", 0.5)) this->mFun = 2;
    if (this->mKeyboard.isKeyPressed("4") && this->mTimer->endOfTime("4", 0.5)) this->mFun = 3;

    if (this->mFun == 0) this->mKinectManager->ArithmeticAverage();
    else if (this->mFun == 1) this->mKinectManager->BestPointAritmeticAverage();
    else if (this->mFun == 2) this->mKinectManager->BestPointAritmeticAverageWeight();
    else this->mKinectManager->BestAngle();

    float aspect = (float)(GetSystemMetrics(SM_CXSCREEN) / GetSystemMetrics(SM_CYSCREEN));
    aspect = (aspect < 1.0f) ? (float)(GetSystemMetrics(SM_CYSCREEN) / GetSystemMetrics(SM_CXSCREEN)) : aspect;

    this->mFrustunMatrix.setFrustum(90.0f, aspect, 0.1f, 1000.0f);
    this->mLookAtMatrix.setLookAt(OGLVector4f(0.0f, 1.0f, -0.2f), OGLVector4f(0.0f, 0.0f, 1.0f), OGLVector4f(0.0f, 1.0f, 0.0f));
}

void OGLMain::render(void)
{
    OGLDebugRender dRender;

    glViewport(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    glScissor(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->mProgramShader->activeProgram();
    this->mProgramShader->setUniformMatrix4("viewMatrix", false, this->mLookAtMatrix.m_pMatrix4f);
    this->mProgramShader->setUniformMatrix4("projectionMatrix", false, this->mFrustunMatrix.m_pMatrix4f);

    dRender.drawGrid(50, 50.0f, OGLVector4f(0.3f, 0.3f, 0.3f));
    if (this->mFun == 0) dRender.drawPoint(OGLVector4f(0.0f, 0.0f, 0.0f), OGLVector4f(1.0f, 0.0f, 0.0f), 10.0f);
    if (this->mFun == 1) dRender.drawPoint(OGLVector4f(0.0f, 0.0f, 0.0f), OGLVector4f(0.0f, 1.0f, 0.0f), 10.0f);
    if (this->mFun == 2) dRender.drawPoint(OGLVector4f(0.0f, 0.0f, 0.0f), OGLVector4f(0.0f, 0.0f, 1.0f), 10.0f);
    if (this->mFun == 3) dRender.drawPoint(OGLVector4f(0.0f, 0.0f, 0.0f), OGLVector4f(0.0f, 0.0f, 0.0f), 10.0f);

    this->mKinectManager->Draw();
    this->mProgramShader->releseProgram();

    glWindowPos2i(0, 0);
    glDrawPixels(320, 240, GL_BGRA, GL_UNSIGNED_BYTE, (unsigned char *)this->mKinectManager->getImage());

    glViewport(0, 240, 320, 240);
    glScissor(0, 240, 320, 240);

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->mProgramShader->activeProgram();
    this->mProgramShader->setUniformMatrix4("viewMatrix", false, this->mLookAtMatrix.m_pMatrix4f);
    this->mProgramShader->setUniformMatrix4("projectionMatrix", false, this->mFrustunMatrix.m_pMatrix4f);

    dRender.drawGrid(50, 50.0f, OGLVector4f(0.3f, 0.3f, 0.3f));
    this->mKinectManager->DrawAllSkeletons();
    this->mProgramShader->releseProgram();

    glViewport(0, 480, 320, 240);
    glScissor(0, 480, 320, 240);

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->mProgramShader->activeProgram();
    this->mProgramShader->setUniformMatrix4("viewMatrix", false, this->mLookAtMatrix.m_pMatrix4f);
    this->mProgramShader->setUniformMatrix4("projectionMatrix", false, this->mFrustunMatrix.m_pMatrix4f);

    dRender.drawGrid(50, 50.0f, OGLVector4f(0.3f, 0.3f, 0.3f));
    this->mKinectManager->DrawSkeleton(0);
    this->mProgramShader->releseProgram();

    wchar_t buffer[80] = {0};
    swprintf_s(buffer, L"FPS: %lf  FrameTime: %lfms", this->mTimer->getFps(), this->mTimer->getFrameTimeInMs());

    SwapBuffers(this->mDeviceContext);
    SetWindowText(this->mWndInstance, buffer);
}
