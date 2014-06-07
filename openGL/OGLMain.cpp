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
    wglSwapIntervalEXT(false);

    this->mTimer = new OGLTimer(0);
    this->mKinectManager = new CKinectManager();

    this->mProgramShader = new OGLShaderProgram(new OGLShader("./simple.vert", GL_VERTEX_SHADER), new OGLShader("./simple.frag", GL_FRAGMENT_SHADER));
    this->mProgramShader->activeProgram();

    this->mKeyboard.addKey("1", 0x31);
    this->mKeyboard.addKey("2", 0x32);
    this->mKeyboard.addKey("3", 0x33);

    this->mKeyboard.addKey("d", 0x44);
    this->mKeyboard.addKey("f", 0x46);

    return(oK);
}

void OGLMain::update(void)
{
    this->mTimer->update();
    this->mKeyboard.update();

    this->mKinectManager->Update();

    this->mKinectManager->RefreshNumKinects();
<<<<<<< HEAD
<<<<<<< HEAD

    if (this->mKeyboard.isKeyPressed("1") && this->mTimer->endOfTime("1", 0.5)) this->mFun = 0;
    if (this->mKeyboard.isKeyPressed("2") && this->mTimer->endOfTime("2", 0.5)) this->mFun = 1;
    if (this->mKeyboard.isKeyPressed("3") && this->mTimer->endOfTime("3", 0.5)) this->mFun = 2;

    if (this->mKeyboard.isKeyPressed("f") && this->mTimer->endOfTime("f", 0.5)) this->mFun = (this->mFun + 1) % 3;
    if (this->mKeyboard.isKeyPressed("d") && this->mTimer->endOfTime("d", 0.5)) this->mDrw = (this->mDrw + 1) % 2;

    if (this->mFun == 0) this->mKinectManager->ArithmeticAverage();
    else if (this->mFun == 1) this->mKinectManager->BestPointAritmeticAverage();
    else this->mKinectManager->BestPointAritmeticAverageWeight();
=======
=======
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
    //this->mKinectManager->BestPositionSkeletonPoint();
    this->mKinectManager->BestPositionSkeletonPointAverage();
    //this->mKinectManager->ArithmeticAverageProcessSkeleton();
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4

    float aspect = (float)(GetSystemMetrics(SM_CXSCREEN) / GetSystemMetrics(SM_CYSCREEN));
    aspect = (aspect < 1.0f) ? (float)(GetSystemMetrics(SM_CYSCREEN) / GetSystemMetrics(SM_CXSCREEN)) : aspect;

    this->mFrustunMatrix.setFrustum(90.0f, aspect, 0.1f, 1000.0f);
<<<<<<< HEAD
<<<<<<< HEAD
    this->mLookAtMatrix.setLookAt(OGLVector4f(0.0f, 1.0f, -0.2f), OGLVector4f(0.0f, 0.0f, 1.0f), OGLVector4f(0.0f, 1.0f, 0.0f));
=======
    this->mLookAtMatrix.setLookAt(OGLVector4f(0.0f, 0.5f, -0.1f), OGLVector4f(0.0f, 0.0f, 1.0f), OGLVector4f(0.0f, 1.0f, 0.0f));
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
=======
    this->mLookAtMatrix.setLookAt(OGLVector4f(0.0f, 0.5f, -0.1f), OGLVector4f(0.0f, 0.0f, 1.0f), OGLVector4f(0.0f, 1.0f, 0.0f));
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
}

void OGLMain::render(void)
{
    static float a = 0.0f;
<<<<<<< HEAD
<<<<<<< HEAD
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

=======
=======
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    OGLMatrix4f modelMatrix;
<<<<<<< HEAD
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
=======
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
    this->mProgramShader->activeProgram();

    this->mProgramShader->setUniformMatrix4("projectionMatrix", false, this->mFrustunMatrix.m_pMatrix4f);
    this->mProgramShader->setUniformMatrix4("viewMatrix", false, this->mLookAtMatrix.m_pMatrix4f);
<<<<<<< HEAD
<<<<<<< HEAD

    OGLDebugRender dRender;
    dRender.drawGrid(50, 50.0f, OGLVector4f(0.3f, 0.3f, 0.3f));
    //dRender.drawPoint(OGLVector4f(), OGLVector4f(1.0f, 0.0f, 0.0f), 10.0f);
    //dRender.drawAxis(OGLVector4f(0.0f, 0.0f, 0.0f), 6.0f);

    if (this->mDrw == 0) this->mKinectManager->Draw();
    else this->mKinectManager->DrawAllSkeletons();

    char s[255] = { 0 };
    sprintf_s(s, "DrawCallNr: %d \t KinectCallNr %d\n", this->mDrw, this->mFun);
    OutputDebugStringA(s);

    this->mProgramShader->releseProgram();

	glWindowPos2i(0, 0);
	glDrawPixels(320, 240, GL_BGRA, GL_BYTE, (char *)this->mKinectManager->getImage());
=======
    this->mProgramShader->setUniformMatrix4("modelMatrix", true, modelMatrix.m_pMatrix4f);

    OGLDebugRender dRender;
    dRender.drawGrid(50, 50.0f, OGLVector4f(1.0f, 1.0f, 1.0f));
    dRender.drawAxis(OGLVector4f(0.0f, 0.0f, 0.0f), 6.0f);

    this->mKinectManager->Draw();
    this->mProgramShader->releseProgram();
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4
=======
    this->mProgramShader->setUniformMatrix4("modelMatrix", true, modelMatrix.m_pMatrix4f);

    OGLDebugRender dRender;
    dRender.drawGrid(50, 50.0f, OGLVector4f(1.0f, 1.0f, 1.0f));
    dRender.drawAxis(OGLVector4f(0.0f, 0.0f, 0.0f), 6.0f);

    this->mKinectManager->Draw();
    this->mProgramShader->releseProgram();
>>>>>>> 091632ebba4714203c85ad21e75fdb02a07ca6f4

    wchar_t buffer[80] = {0};
    swprintf_s(buffer, L"FPS: %lf  FrameTime: %lfms", this->mTimer->getFps(), this->mTimer->getFrameTimeInMs());

    SwapBuffers(this->mDeviceContext);
    SetWindowText(this->mWndInstance, buffer);
}
