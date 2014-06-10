 #include "./CKinect.h"

CKinect::CKinect(int sId, int flags, const OGLVector4f &color)
{
    this->m_AngleID = 0;
    this->m_SensorID = sId;
    this->m_hasChanged = true;
    this->m_SkeletonAngle = 0.0f;
	
	this->m_SkeletonPosition.x = 0.0f;
    this->m_SkeletonPosition.y = 0.0f;
    this->m_SkeletonPosition.z = 0.0f;

    this->m_SkeletonColor.x = color.x;
    this->m_SkeletonColor.y = color.y;
    this->m_SkeletonColor.z = color.z;
	
	for (float *f = this->m_pSkeletonAngles; f < this->m_pSkeletonAngles + MAX_ANGLES_HISOTRY; f++) *f = 0.0f;

    if (FAILED(NuiCreateSensorByIndex(this->m_SensorID, &this->m_pNuiSensor)))
    {
        MessageBox(NULL, L"Error al crear el bind!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        exit(EXIT_FAILURE);
    }

    if (FAILED(this->m_pNuiSensor->NuiStatus()))
    {
        MessageBox(NULL, L"Error al mirar el estado!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        this->m_pNuiSensor->Release();
        exit(EXIT_FAILURE);
    }

    if (FAILED(this->m_pNuiSensor->NuiInitialize(flags)))
    {
        MessageBox(NULL, L"Error al Inicializar los flags!", L"Error", MB_ICONEXCLAMATION | MB_OK);
		this->m_pNuiSensor->NuiShutdown();
        this->m_pNuiSensor->Release();
        exit(EXIT_FAILURE);
    }

	if ((flags & NUI_INITIALIZE_FLAG_USES_SKELETON) == NUI_INITIALIZE_FLAG_USES_SKELETON && !this->initSkeleton())
    {
		MessageBox(NULL, L"Error al Inicializar el esqueleto!", L"Error", MB_ICONEXCLAMATION | MB_OK);
		this->m_pNuiSensor->NuiShutdown();
		this->m_pNuiSensor->Release();
		exit(EXIT_FAILURE);
    }

	if ((flags & NUI_INITIALIZE_FLAG_USES_COLOR) == NUI_INITIALIZE_FLAG_USES_COLOR && !this->initColor())
	{
		MessageBox(NULL, L"Error al Inicializar el color!", L"Error", MB_ICONEXCLAMATION | MB_OK);
		this->m_pNuiSensor->NuiShutdown();
		this->m_pNuiSensor->Release();
		exit(EXIT_FAILURE);
	}
}

CKinect::~CKinect()
{
    if (this->m_pNuiSensor != NULL)
    {
        this->m_pNuiSensor->NuiShutdown();
        this->m_pNuiSensor->Release();
        this->m_pNuiSensor = NULL;
    }
}

bool CKinect::initSkeleton(void)
{
    if (FAILED(this->m_hNextSkeletonEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
    {
        OutputDebugStringA("Error en CreateEvent!\n");
        return(false);
    }

    if (FAILED(this->m_pNuiSensor->NuiSkeletonTrackingEnable(this->m_hNextSkeletonEvent, 0)))
    {
        OutputDebugStringA("Error en NuiSkeletonTrackingEnable!\n");
        return(false);
    }

    return(true);
}

bool CKinect::initColor(void)
{
	if (FAILED(this->m_pNuiSensor->NuiImageStreamOpen(NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480, 0, 2, NULL, &this->m_hRgbStream)))
	{
		OutputDebugStringA("Error en NuiImageStreamOpen!\n");
		return(false);
	}

	return(true);
}

bool CKinect::Update(void)
{
    NUI_SKELETON_BONE_ORIENTATION boneOrientations[NUI_SKELETON_POSITION_COUNT];
    NUI_SKELETON_FRAME skeletonFrame;
    int skeletonTrackedPos = 0;

    if (FAILED(this->m_pNuiSensor->NuiSkeletonGetNextFrame(1000, &skeletonFrame)))
    {
        OutputDebugStringA("Error al procesar el NuiSkeletonGetNextFrame!\n");
        return(false);
    }

    NUI_TRANSFORM_SMOOTH_PARAMETERS somewhatLatentParams = { 0.5f, 0.1f, 0.5f, 0.1f, 0.1f };
    NUI_TRANSFORM_SMOOTH_PARAMETERS verySmoothParams ={ 0.7f, 0.3f, 1.0f, 1.0f, 1.0f };
    NUI_TRANSFORM_SMOOTH_PARAMETERS defaultParams = { 0.5f, 0.5f, 0.5f, 0.05f, 0.04f };
    this->m_pNuiSensor->NuiTransformSmooth(&skeletonFrame, &defaultParams);

    for (skeletonTrackedPos = 0; skeletonTrackedPos < NUI_SKELETON_COUNT; skeletonTrackedPos++)
    {
        if (skeletonFrame.SkeletonData[skeletonTrackedPos].eTrackingState == NUI_SKELETON_POSITION_TRACKED) break;
    }
	
	NUI_IMAGE_FRAME imageFrame;
	NUI_LOCKED_RECT lockedRect;

	this->m_pNuiSensor->NuiImageStreamGetNextFrame(this->m_hRgbStream, 9000, &imageFrame);
	INuiFrameTexture *texture = imageFrame.pFrameTexture;
	texture->LockRect(0, &lockedRect, NULL, 0);

	if (lockedRect.Pitch != 0)
	{
        unsigned int *buffer = (unsigned int *)malloc(sizeof(int)* 640 * 480);
        unsigned int *currentByte = (unsigned int *)lockedRect.pBits;
        unsigned int *dataEnd = currentByte + 640 * 480;
        unsigned int *b = buffer;

		while (currentByte < dataEnd) *b++ = *currentByte++;
        
        for (unsigned int i = 0, mi = (640 * 480) - 1; i < 640 * 480 / 2; i++, mi--)
        {
            int t = *(buffer + i);
            *(buffer + i)  = *(buffer + mi);
            *(buffer + mi) = t;
        }
        
        for (int cy = 0; cy < 240; cy++) for (int cx = 0; cx < 320; cx++)
        {
            int pixel = cy * 320 + cx;
            int nearestMatch = ((int)(cy / 0.5)) * 640 + (int)(cx / 0.5);
            *(this->m_pImage + pixel) = *(buffer + nearestMatch);
        }
        
        free(buffer);
    }

	texture->UnlockRect(0);
	this->m_pNuiSensor->NuiImageStreamReleaseFrame(this->m_hRgbStream, &imageFrame);

    if (skeletonTrackedPos < NUI_SKELETON_COUNT)
    {
        for (int i = 0; i < 20; i++)
        {
            this->m_pJointsPosition[i].x = skeletonFrame.SkeletonData[skeletonTrackedPos].SkeletonPositions[i].x;
            this->m_pJointsPosition[i].y = skeletonFrame.SkeletonData[skeletonTrackedPos].SkeletonPositions[i].y;
            this->m_pJointsPosition[i].z = skeletonFrame.SkeletonData[skeletonTrackedPos].SkeletonPositions[i].z;
        }
        
        this->m_SkeletonPosition.x = skeletonFrame.SkeletonData[skeletonTrackedPos].Position.x;
        this->m_SkeletonPosition.y = skeletonFrame.SkeletonData[skeletonTrackedPos].Position.y;
        this->m_SkeletonPosition.z = skeletonFrame.SkeletonData[skeletonTrackedPos].Position.z;

        NuiSkeletonCalculateBoneOrientations(&skeletonFrame.SkeletonData[skeletonTrackedPos], boneOrientations);

        OGLVector4f v1 = this->m_pJointsPosition[NUI_SKELETON_POSITION_SHOULDER_RIGHT] - this->m_pJointsPosition[NUI_SKELETON_POSITION_SHOULDER_LEFT];
        OGLVector4f v2(1.0f, 0.0f, 0.0f);

        v1.x = std::ceilf(v1.x * 100.0f + 0.5f) / 100.0f;
        v1.y = std::ceilf(v1.y * 100.0f + 0.5f) / 100.0f;
        v1.z = std::ceilf(v1.z * 100.0f + 0.5f) / 100.0f;
      
        v1.y = 0.0f;
        v2 = v2.normalize();
        v1 = v1.normalize();

        float aCos = v1.dot(v2);
        float aSin = v1.cross(v2).length();

        this->m_SkeletonAngle = std::acosf(aCos) * 180.0f / 3.14159265f;
        //this->m_SkeletonAngle = std::atan2f(aSin, aCos) * 180.0f / 3.14159265f;

        if (OGLVector4f(0.0f, 1.0f, 0.0f).dot(v1.cross(v2)) < 0)
        {
            this->m_SkeletonAngle = -this->m_SkeletonAngle;
        }

        *(this->m_pSkeletonAngles + this->m_AngleID) = std::floorf(this->m_SkeletonAngle);
        this->m_AngleID = (this->m_AngleID++) % MAX_ANGLES_HISOTRY;

        this->m_SkeletonAngle = 0.0f;
        for (float *f = this->m_pSkeletonAngles; f < this->m_pSkeletonAngles + MAX_ANGLES_HISOTRY; f++)  this->m_SkeletonAngle += *f;
        this->m_SkeletonAngle = std::floorf(this->m_SkeletonAngle / MAX_ANGLES_HISOTRY);
        /*
        float x = boneOrientations[NUI_SKELETON_POSITION_HIP_CENTER].hierarchicalRotation.rotationQuaternion.x;
        float y = boneOrientations[NUI_SKELETON_POSITION_HIP_CENTER].hierarchicalRotation.rotationQuaternion.y;
        float z = boneOrientations[NUI_SKELETON_POSITION_HIP_CENTER].hierarchicalRotation.rotationQuaternion.z;
        float w = boneOrientations[NUI_SKELETON_POSITION_HIP_CENTER].hierarchicalRotation.rotationQuaternion.w;

        float ro = atan2f(2.0f*(x*y + w*z), w*w + x*x - y*y - z*z);
        float ya = atan2f(2.0f*(y*z + w*x), w*w - x*x - y*y + z*z);
        float pp = asinf(-2.0f*(x*z - w*y));
        */
        return(true);
    }

    return(false);
}

OGLVector4f *CKinect::getJointsPosition(void)
{
    
    return(this->m_pJointsPosition);
}

OGLVector4f *CKinect::getSkeletonPosition(void)
{
    return(&this->m_SkeletonPosition);
}

OGLVector4f *CKinect::getSkeletonColor(void)
{
    return(&this->m_SkeletonColor);
}

int *CKinect::getImage(void)
{
	return(this->m_pImage);
}

float *CKinect::getAngle(void)
{
    return(&this->m_SkeletonAngle);
}

bool CKinect::GetState()
{
    return(this->m_pNuiSensor->NuiStatus() == S_OK);
}
