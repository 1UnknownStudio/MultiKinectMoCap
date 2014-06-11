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

#define MAX_ANGLES_HISOTRY  10
#define IMAGE_HEIGHT   480
#define IMAGE_WIDTH    640

#define IMAGE_NHEIGHT   240
#define IMAGE_NWIDTH    320

class CKinect
{
    private:
        INuiSensor   *m_pNuiSensor;
        HANDLE        m_hRgbStream;
        HANDLE        m_hNextSkeletonEvent;

        float         m_pSkeletonAngles[MAX_ANGLES_HISOTRY];
        float         m_SkeletonAngle;

        int           m_pImage[IMAGE_NWIDTH * IMAGE_NHEIGHT];
        int           m_SensorID;
        int           m_AngleID;

        OGLVector4f   m_pJointsPosition[20];
        OGLVector4f   m_SkeletonPosition;
        OGLVector4f   m_SkeletonColor;

        bool m_hasChanged;

        bool initColor      (void);
        bool initSkeleton   (void);

    public:
        CKinect                             (int, int, const OGLVector4f &);
        ~CKinect                            (void);

        bool   Update                       (void);
        bool   GetState                     (void);

        int    *getImage                    (void);
        float  *getAngle                    (void);

        OGLVector4f *getSkeletonColor       (void);
        OGLVector4f *getJointsPosition      (void);
        OGLVector4f *getSkeletonPosition    (void);
};
