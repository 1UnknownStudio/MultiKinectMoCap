#include "./CKinect.h"

CKinect::CKinect(int sId, int flags, const OGLVector3f &color)
{
	this->m_SensorID = sId;
	this->m_hasChanged = true;

	this->m_SkeletonColor.x = color.x;
	this->m_SkeletonColor.y = color.y;
	this->m_SkeletonColor.z = color.z;

	if (FAILED(NuiCreateSensorByIndex(this->m_SensorID, &this->m_pNuiSensor)))
	{
		OutputDebugStringA("Error al crear el bind!\n");
		exit(EXIT_FAILURE);
	}

	if (FAILED(this->m_pNuiSensor->NuiStatus()))
	{
		OutputDebugStringA("Error al mirar el estado!\n");
		this->m_pNuiSensor->Release();
		exit(EXIT_FAILURE);
	}

	if (FAILED(this->m_pNuiSensor->NuiInitialize(flags)))
	{
		OutputDebugStringA("Error al Inicializar los flags!\n");
		this->m_pNuiSensor->Release();
		exit(EXIT_FAILURE);
	}

	if ((flags & NUI_INITIALIZE_FLAG_USES_SKELETON) == NUI_INITIALIZE_FLAG_USES_SKELETON)
	{
		if (!this->initSkeleton())
		{
			this->m_pNuiSensor->Release();
			exit(EXIT_FAILURE);
		}
	}

	this->m_SkeletonPosition.x = 0.0f;
	this->m_SkeletonPosition.y = 0.0f;
	this->m_SkeletonPosition.z = 0.0f;
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

void CKinect::Update(void)
{
	NUI_SKELETON_FRAME skeletonFrame;
	int skeletonTrackedPos = 0;
	this->m_hasChanged = false;

	if (FAILED(this->m_pNuiSensor->NuiSkeletonGetNextFrame(1000, &skeletonFrame)))
	{
		OutputDebugStringA("Error al procesar el NuiSkeletonGetNextFrame!\n");
		return;
	}

	for (skeletonTrackedPos = 0; skeletonTrackedPos < NUI_SKELETON_COUNT; skeletonTrackedPos++)
	{
		if (skeletonFrame.SkeletonData[skeletonTrackedPos].eTrackingState == NUI_SKELETON_POSITION_TRACKED) break;
	}

	if (skeletonTrackedPos < NUI_SKELETON_COUNT)
	{
		for (int i = 0; i < 20; i++)
		{
			this->m_pJointsPosition[i].x = skeletonFrame.SkeletonData[skeletonTrackedPos].SkeletonPositions[i].x;
			this->m_pJointsPosition[i].y = skeletonFrame.SkeletonData[skeletonTrackedPos].SkeletonPositions[i].y;
			this->m_pJointsPosition[i].z = skeletonFrame.SkeletonData[skeletonTrackedPos].SkeletonPositions[i].z;
		}

		if (skeletonTrackedPos < NUI_SKELETON_COUNT)
		{
			this->m_SkeletonPosition.x = skeletonFrame.SkeletonData[skeletonTrackedPos].Position.x;
			this->m_SkeletonPosition.y = skeletonFrame.SkeletonData[skeletonTrackedPos].Position.y;
			this->m_SkeletonPosition.z = skeletonFrame.SkeletonData[skeletonTrackedPos].Position.z;
		}

		this->m_hasChanged = true;
	}
}

OGLVector3f *CKinect::getJointsPosition(void)
{
	
	return((this->m_hasChanged) ? this->m_pJointsPosition : NULL);
}

OGLVector3f *CKinect::getSkeletonPosition(void)
{
	return((this->m_hasChanged)? &this->m_SkeletonPosition : NULL);
}

OGLVector3f *CKinect::getSkeletonColor(void)
{
	return((this->m_hasChanged) ? &this->m_SkeletonColor : NULL );
}


bool CKinect::GetState()
{
	return(this->m_pNuiSensor->NuiStatus() == S_OK);
}