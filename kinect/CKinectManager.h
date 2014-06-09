#pragma once
using namespace std;

#include <map>
#include <array>
#include <ctime>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include <NuiApi.h>
#include <NuiSensor.h>
#include <NuiSkeleton.h>
#include <NuiImageCamera.h>

#include "./CKinect.h"

#include "./../openGL/OGLMath/OGLVector4f.h"
#include "./../openGL/OGLDebugRender/OGLDebugRender.h"

#define MAX_KINECT_SENSORS 4

class CKinectManager
{
    private:
        int     m_NumSensors;

        std::vector<CKinect *>    m_Kinects;
        std::map<int, int>        m_FreeKinects;
        
        std::vector<float *>          m_pSkeletonAngles;
        std::vector<OGLVector4f *>    m_pJointsPosition;
        std::vector<OGLVector4f *>    m_pSkeletonsColor;
        std::vector<OGLVector4f *>    m_pSkeletonsPosition;

        std::vector<int> m_pJoinsDrawOrder;
        OGLVector4f      m_JoinsInformation[20];

        void addKinect(int);
        void releaseKinct();
        
    public:
        CKinectManager(void);
        ~CKinectManager();

		int     *getImage(void);
        void    toFile(void);

        void    BestAngle(void);
        void    ArithmeticAverage(void);
        void    BestPointAritmeticAverage(void);
        void    BestPointAritmeticAverageWeight(void);

        void    RefreshNumKinects(void);
        void    DrawAllSkeletons(void);
        void    DrawSkeleton(int);

        void    Draw(void);
        void    Update(void);
};
