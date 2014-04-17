#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include <NuiApi.h>
#include <NuiSensor.h>
#include <NuiSkeleton.h>
#include <NuiImageCamera.h>

#include "./../openGL/OGLMath/OGLVector4f.h"
#include "./../openGL/OGLMath/OGLMatrix4f.h"

class CKinect
{
    private:
        INuiSensor    *m_pNuiSensor;
        HANDLE         m_hNextSkeletonEvent;

        float         m_SkeletonAngle;
        int             m_SensorID;

        OGLVector4f m_pJointsPosition[20];
        OGLVector4f m_SkeletonPosition;
        OGLVector4f m_SkeletonColor;

        bool m_hasChanged;
        bool initSkeleton(void);

    public:
        CKinect(int, int, const OGLVector4f &);
        ~CKinect();

        void        Update(void);
        bool        GetState(void);
        
        float       *getAngle(void);
        OGLVector4f *getSkeletonColor(void);
        OGLVector4f *getJointsPosition(void);
        OGLVector4f *getSkeletonPosition(void);
};
