#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include <NuiApi.h>
#include <NuiSensor.h>
#include <NuiSkeleton.h>
#include <NuiImageCamera.h>

#include "./../openGL/OGLMath/OGLVector3f.h"
#include "./../openGL/OGLMath/OGLMatrix4f.h"

class CKinect
{
	private:
		INuiSensor	*m_pNuiSensor;
		HANDLE		 m_hNextSkeletonEvent;
		int			 m_SensorID;

		OGLVector3f m_pJointsPosition[20];
		OGLVector3f m_SkeletonPosition;
		OGLVector3f m_SkeletonColor;

		bool m_hasChanged;
		bool initSkeleton(void);

	public:
		CKinect(int, int, const OGLVector3f &);
		~CKinect();

		void		 Update(void);
		bool		 GetState(void);
		OGLVector3f *getSkeletonColor(void);
		OGLVector3f *getJointsPosition(void);
		OGLVector3f *getSkeletonPosition(void);
};