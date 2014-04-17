#include "CKinectManager.h"

CKinectManager::CKinectManager()
{
    this->m_NumSensors = 0;
    srand((unsigned int) time(NULL));

    if (FAILED(NuiGetSensorCount(&this->m_NumSensors)))
    {
        OutputDebugStringA("Error al detectar el numero de Kinects!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_KINECT_SENSORS; i++)
    {
        this->m_FreeKinects.insert(std::pair<int, int>(i, 1));
    }

    for (int i = 0; i < this->m_NumSensors; ++i)
    {
        this->m_Kinects.push_back(new CKinect(i, NUI_INITIALIZE_FLAG_USES_SKELETON, OGLVector4f((rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f)));
        this->m_FreeKinects.at(i) = 0;
    }

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_HEAD);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_SHOULDER_CENTER);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_SHOULDER_CENTER);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_SHOULDER_RIGHT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_SHOULDER_CENTER);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_SHOULDER_LEFT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_SHOULDER_LEFT);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_ELBOW_LEFT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_SHOULDER_RIGHT);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_ELBOW_RIGHT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_ELBOW_LEFT);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_WRIST_LEFT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_ELBOW_RIGHT);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_WRIST_RIGHT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_WRIST_LEFT);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_HAND_LEFT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_WRIST_RIGHT);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_HAND_RIGHT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_SHOULDER_CENTER);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_SPINE);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_SPINE);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_HIP_CENTER);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_HIP_CENTER);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_HIP_LEFT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_HIP_CENTER);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_HIP_RIGHT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_HIP_LEFT);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_KNEE_LEFT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_HIP_RIGHT);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_KNEE_RIGHT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_KNEE_LEFT);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_ANKLE_LEFT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_KNEE_RIGHT);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_ANKLE_RIGHT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_ANKLE_LEFT);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_FOOT_LEFT);

    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_ANKLE_RIGHT);
    this->m_pJoinsDrawOrder.push_back(NUI_SKELETON_POSITION_FOOT_RIGHT);
}

CKinectManager::~CKinectManager()
{
    for (int i = 0; i < this->m_NumSensors; i++)
    {
        delete(this->m_Kinects.at(i));
    }

    this->m_Kinects.clear();
    this->m_FreeKinects.clear();

    this->m_pSkeletonsPosition.clear();
    this->m_pSkeletonsColor.clear();
    this->m_pJointsPosition.clear();
    this->m_pSkeletonAngles.clear();
}

void CKinectManager::releaseKinct()
{
    for (int i = 0; i < this->m_NumSensors; i++)
    {
        if (!this->m_Kinects.at(i)->GetState())
        {
            this->m_NumSensors--;
            this->m_FreeKinects.at(i) = 1;

            delete(this->m_Kinects.at(i));
            this->m_Kinects.erase(this->m_Kinects.begin() + i);
        }
    }
}

void CKinectManager::addKinect(int v_NumSensors)
{
    for (int i = 0; i < MAX_KINECT_SENSORS && v_NumSensors > 0; i++)
    {
        if (this->m_FreeKinects.at(i) == 1)
        {
            this->m_Kinects.push_back(new CKinect(i, NUI_INITIALIZE_FLAG_USES_SKELETON, OGLVector4f((rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f)));
            this->m_FreeKinects.at(i) = 0;
            this->m_NumSensors++;

            v_NumSensors--;
        }
    }
}

void CKinectManager::RefreshNumKinects()
{

    int v_NumSensors = 0;

    if (FAILED(NuiGetSensorCount(&v_NumSensors)))
    {
        OutputDebugStringA("Error al detectar el numero de Kinects!\n");
        exit(EXIT_FAILURE);
    }

    if (this->m_NumSensors > v_NumSensors)
    {
        OutputDebugStringA("releaseKinct()\n");
        this->releaseKinct();
    }
    else if (this->m_NumSensors < v_NumSensors)
    {
        Sleep(5000);
        OutputDebugStringA("addKinect()\n");
        this->addKinect(v_NumSensors - this->m_NumSensors);
    }
}

void CKinectManager::Draw()
{
    OGLDebugRender dRender;

    for (unsigned int i = 0; i < this->m_pJoinsDrawOrder.size(); i += 2)
    {
        dRender.drawLine(this->m_JoinsInformation[this->m_pJoinsDrawOrder[i]], this->m_JoinsInformation[this->m_pJoinsDrawOrder[i + 1]], OGLVector4f(1.0f, 0.0f, 0.0f));
    }
}

void CKinectManager::Update(void)
{
    this->m_pSkeletonAngles.clear();
    this->m_pSkeletonsColor.clear();
    this->m_pJointsPosition.clear();
    this->m_pSkeletonsPosition.clear();
    
    for (std::vector<CKinect *>::iterator it = this->m_Kinects.begin(); it != this->m_Kinects.end(); it++)
    {
        (*it)->Update();

        OGLVector4f *skeletonColor = (*it)->getSkeletonColor();
        OGLVector4f *skeletonJoins = (*it)->getJointsPosition();
        OGLVector4f *skeletonPosition = (*it)->getSkeletonPosition();
        float *skeletonAngle = (*it)->getAngle();

        if (skeletonJoins != NULL) this->m_pJointsPosition.push_back(skeletonJoins);
        if (skeletonColor != NULL) this->m_pSkeletonsColor.push_back(skeletonColor);
        if (skeletonAngle != NULL) this->m_pSkeletonAngles.push_back(skeletonAngle);
        if (skeletonPosition != NULL) this->m_pSkeletonsPosition.push_back(skeletonPosition);
    }
}

void CKinectManager::DrawAllSkeletons(void)
{
    OGLDebugRender dRender;

    for (unsigned int i = 0; i < this->m_pJointsPosition.size(); i++)
    {
        for (unsigned int j = 0; j < this->m_pJoinsDrawOrder.size(); j += 2)
        {
            dRender.drawLine(this->m_pJointsPosition[i][this->m_pJoinsDrawOrder[j]], this->m_pJointsPosition[i][this->m_pJoinsDrawOrder[j + 1]], *this->m_pSkeletonsColor[i]);
        }
    }
}

void CKinectManager::ArithmeticAverageProcessSkeleton()
{
    memset(this->m_JoinsInformation, 0, sizeof(OGLVector4f)* 20);

    for (unsigned int i = 0; i < this->m_pJointsPosition.size(); i++)
    {
        for (int j = 0; j < 20; j++)
        {
            this->m_JoinsInformation[j].x += this->m_pJointsPosition[i][j].x;
            this->m_JoinsInformation[j].y += this->m_pJointsPosition[i][j].y;
            this->m_JoinsInformation[j].z += this->m_pJointsPosition[i][j].z;
        }
    }


    for (int i = 0; i < 20; i++)
    {
        this->m_JoinsInformation[i].x /= this->m_pJointsPosition.size();
        this->m_JoinsInformation[i].y /= this->m_pJointsPosition.size();
        this->m_JoinsInformation[i].z /= this->m_pJointsPosition.size();
    }
}

void CKinectManager::BestPositionSkeletonPointAverage()
{
    int index = 0;
    std::vector<OGLVector4f> joints;
    std::vector<std::vector<OGLVector4f>> skeletons;

    for (unsigned int i = 1; i < this->m_pSkeletonAngles.size(); i++)
    {
        if (this->m_pSkeletonAngles[i] < this->m_pSkeletonAngles[i - 1]) index = i;
    }

    for (unsigned int i = 0; i < this->m_pJointsPosition.size(); i++)
    {
        OGLVector4f aux;
        aux.x = this->m_pSkeletonsPosition[i]->x - this->m_pSkeletonsPosition[index]->x;
        aux.z = this->m_pSkeletonsPosition[i]->z - this->m_pSkeletonsPosition[index]->z;
        aux.y = this->m_pSkeletonsPosition[i]->y - this->m_pSkeletonsPosition[index]->y;

        for (int j = 0; j < 20; j++)
        {
            joints.push_back(this->m_pJointsPosition[i][j] - aux);
        }

        skeletons.push_back(joints);
        joints.clear();
    }

    memset(this->m_JoinsInformation, 0, sizeof(OGLVector4f)* 20);

    for (unsigned int i = 0; i < this->m_pJointsPosition.size(); i++)
    {
        for (int j = 0; j < 20; j++)
        {
            this->m_JoinsInformation[j].x += skeletons[i][j].x;
            this->m_JoinsInformation[j].y += skeletons[i][j].y;
            this->m_JoinsInformation[j].z += skeletons[i][j].z;
        }
    }


    for (int i = 0; i < 20; i++)
    {
        this->m_JoinsInformation[i].x /= this->m_pJointsPosition.size();
        this->m_JoinsInformation[i].y /= this->m_pJointsPosition.size();
        this->m_JoinsInformation[i].z /= this->m_pJointsPosition.size();
    }
}

void CKinectManager::BestPositionSkeletonPoint()
{
    int index = 0;
    memset(this->m_JoinsInformation, 0, sizeof(OGLVector4f)* 20);

    for (unsigned int i = 1; i < this->m_pSkeletonAngles.size(); i++)
    {
        if (this->m_pSkeletonAngles[i] < this->m_pSkeletonAngles[i - 1]) index = i;
    }

    for (unsigned int i = 0; i < 20 && index < this->m_pJointsPosition.size(); i++)
    {
        this->m_JoinsInformation[i] = this->m_pJointsPosition[index][i];
    }
}
