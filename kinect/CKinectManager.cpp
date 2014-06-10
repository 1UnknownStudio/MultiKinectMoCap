#include "CKinectManager.h"

CKinectManager::CKinectManager()
{
    this->m_KBase = 0;
    this->m_NumSensors = 0;
    srand((unsigned int) time(NULL));
    memset(this->m_JoinsInformation, 0, sizeof(OGLVector4f)* 20);

    if (FAILED(NuiGetSensorCount(&this->m_NumSensors)))
    {
        MessageBox(NULL, L"Error al detectar el numero de Kinects!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_KINECT_SENSORS; i++)
    {
        this->m_FreeKinects.insert(std::pair<int, int>(i, 1));
    }

    for (int i = 0; i < this->m_NumSensors; ++i)
    {
		this->m_Kinects.push_back(new CKinect(i, NUI_INITIALIZE_FLAG_USES_SKELETON | NUI_INITIALIZE_FLAG_USES_DEPTH | NUI_INITIALIZE_FLAG_USES_COLOR , OGLVector4f((rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f)));
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
		if (this->m_Kinects.at(i)->GetState()) continue;
		
		this->m_NumSensors--;
		this->m_FreeKinects.at(i) = 1;
		
		delete(this->m_Kinects.at(i));
		this->m_Kinects.erase(this->m_Kinects.begin() + i);
    }
}

void CKinectManager::addKinect(int v_NumSensors)
{
	for (int i = 0; i < MAX_KINECT_SENSORS && v_NumSensors > 0; i++)
	{
		if (!this->m_FreeKinects.at(i) == 1) continue;

		this->m_Kinects.push_back(new CKinect(i, NUI_INITIALIZE_FLAG_USES_SKELETON, OGLVector4f((rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f)));
		this->m_FreeKinects.at(i) = 0;
		this->m_NumSensors++;
		v_NumSensors--;
	}
}

void CKinectManager::RefreshNumKinects()
{
    int v_NumSensors = 0;

    if (FAILED(NuiGetSensorCount(&v_NumSensors)))
    {
        MessageBox(NULL, L"Error al detectar el numero de Kinects!", L"Advertencia", MB_ICONEXCLAMATION | MB_OK);
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

void CKinectManager::Update(void)
{
    this->m_KBase = 0;

    this->m_pSkeletonAngles.clear();
    this->m_pSkeletonsColor.clear();
    this->m_pJointsPosition.clear();
    this->m_pSkeletonsPosition.clear();
    
    for (std::vector<CKinect *>::iterator it = this->m_Kinects.begin(); it != this->m_Kinects.end(); it++)
    {
        if (!(*it)->Update()) continue;
        
        this->m_pSkeletonsPosition.push_back((*it)->getSkeletonPosition());
        this->m_pJointsPosition.push_back((*it)->getJointsPosition());
        this->m_pSkeletonsColor.push_back((*it)->getSkeletonColor());
        this->m_pSkeletonAngles.push_back((*it)->getAngle());
    }
}

void CKinectManager::toFile(void)
{
    static unsigned int f = 0;
    FILE *pFile = NULL;

    if (FAILED(fopen_s(&pFile, "diff.txt", "a"))) MessageBox(NULL, L"pFile!", L"Error", MB_ICONEXCLAMATION | MB_OK);
    fprintf_s(pFile, "Frame: %d\n", f++);

    for (unsigned int j = 0; j < 20; j++)
    {
        fprintf_s(pFile, "joint %d =>", j);
        for (unsigned int i = 0; i < this->m_pSkeletonsPosition.size(); i++)
        {
            fprintf_s(pFile, "\t %f %f %f", this->m_pSkeletonsPosition[i][j].x, this->m_pSkeletonsPosition[i][j].y, this->m_pSkeletonsPosition[i][j].z);
        }

        fprintf_s(pFile, "\n");
    }

    fclose(pFile);
}

void CKinectManager::Draw()
{
    OGLDebugRender dRender;

	for (unsigned int i = 0; i < this->m_pJoinsDrawOrder.size() && this->m_pSkeletonsPosition.size() != 0; i += 2)
    {
        dRender.drawLine(this->m_JoinsInformation[this->m_pJoinsDrawOrder[i]], this->m_JoinsInformation[this->m_pJoinsDrawOrder[i + 1]], OGLVector4f(1.0f, 0.0f, 0.0f));
    }
}

void CKinectManager::DrawAllSkeletons(void)
{
    OGLDebugRender dRender;

    for (unsigned int i = 0; i < this->m_pJointsPosition.size(); i++) for (unsigned int j = 0; j < this->m_pJoinsDrawOrder.size(); j += 2)
    {
        dRender.drawLine(this->m_pJointsPosition[i][this->m_pJoinsDrawOrder[j]], this->m_pJointsPosition[i][this->m_pJoinsDrawOrder[j + 1]], *this->m_pSkeletonsColor[i]);
    }
}

void CKinectManager::DrawSkeleton(void)
{
    OGLDebugRender dRender;

    for (unsigned int j = 0; j < this->m_pJoinsDrawOrder.size() && (unsigned int) this->m_KBase < this->m_pJointsPosition.size(); j += 2)
    {
        dRender.drawLine(this->m_pJointsPosition[this->m_KBase][this->m_pJoinsDrawOrder[j]], this->m_pJointsPosition[this->m_KBase][this->m_pJoinsDrawOrder[j + 1]], *this->m_pSkeletonsColor[this->m_KBase]);
    }
}

void CKinectManager::ArithmeticAverage(void)
{
    memset(this->m_JoinsInformation, 0, sizeof(OGLVector4f) * 20);

    for (unsigned int i = 0; i < this->m_pJointsPosition.size(); i++) for (int j = 0; j < 20; j++)
    {
        this->m_JoinsInformation[j] = this->m_JoinsInformation[j] + this->m_pJointsPosition[i][j];
    }

    for (int i = 0; i < 20; i++)
    {
        this->m_JoinsInformation[i] = this->m_JoinsInformation[i] / (float) this->m_pJointsPosition.size();
    }

}

void CKinectManager::BestPointAritmeticAverageWeight(void)
{
    float weightDiv = -1.0f;
    memset(this->m_JoinsInformation, 0, sizeof(OGLVector4f) * 20);
    std::vector<float> weight(this->m_pSkeletonAngles.size(), 0.0f);

    for (unsigned int i = 1; i < weight.size() + 1; i++)
    {
        weight[i - 1] = 1.0f / std::powf((float) i, 3);
        weightDiv += weight[i - 1];
    }

    for (unsigned int i = 1; i < this->m_pJointsPosition.size(); i++)
    {
        OGLMatrix4f mt1; mt1.setTranslation(-this->m_pSkeletonsPosition[i]->x, -this->m_pSkeletonsPosition[i]->y, -this->m_pSkeletonsPosition[i]->z);
        OGLMatrix4f mt2; mt2.setTranslation(this->m_pSkeletonsPosition[0]->x, this->m_pSkeletonsPosition[0]->y, this->m_pSkeletonsPosition[0]->z);
        OGLMatrix4f mr1; mr1.setYRotation(-(*this->m_pSkeletonAngles[0] - *this->m_pSkeletonAngles[i]) * 3.141592f / 180.0f);
       
        for (int j = 0; j < 20; j++)
        {
            this->m_pJointsPosition[i][j] = mt2 * mr1 * mt1 * this->m_pJointsPosition[i][j];
        }
    }

    for (unsigned int i = 0; this->m_pSkeletonAngles.size() >= 2 && i < this->m_pSkeletonAngles.size() - 1; i++)
    {
        if (abs(*this->m_pSkeletonAngles[i]) <= abs(*this->m_pSkeletonAngles[i + 1])) continue;
        if(this->m_KBase == i) this->m_KBase = i + 1;

        OGLVector4f *aux = this->m_pJointsPosition[i];
        this->m_pJointsPosition[i] = this->m_pJointsPosition[i + 1];
        this->m_pJointsPosition[i + 1] = aux;

        aux = this->m_pSkeletonsColor[i];
        this->m_pSkeletonsColor[i] = this->m_pSkeletonsColor[i + 1];
        this->m_pSkeletonsColor[i + 1] = aux;
    }

    for (unsigned int i = 0; i < this->m_pJointsPosition.size(); i++) for (int j = 0; j < 20; j++)
    {
        this->m_JoinsInformation[j] = this->m_JoinsInformation[j] + this->m_pJointsPosition[i][j] * weight[i] * ((i == 0) ? 1 : weightDiv);
    }        
}

void CKinectManager::BestPointAritmeticAverage(void)
{
    memset(this->m_JoinsInformation, 0, sizeof(OGLVector4f) * 20);

    for (unsigned int i = 1; i < this->m_pJointsPosition.size(); i++)
    {
        OGLMatrix4f mt1; mt1.setTranslation(-this->m_pSkeletonsPosition[i]->x, -this->m_pSkeletonsPosition[i]->y, -this->m_pSkeletonsPosition[i]->z);
        OGLMatrix4f mt2; mt2.setTranslation(this->m_pSkeletonsPosition[0]->x, this->m_pSkeletonsPosition[0]->y, this->m_pSkeletonsPosition[0]->z);
        OGLMatrix4f mr1; mr1.setYRotation(-(*this->m_pSkeletonAngles[0] - *this->m_pSkeletonAngles[i]) * 3.141592f / 180.0f);

        for (int j = 0; j < 20; j++)
        {
            this->m_pJointsPosition[i][j] = mt2 * mr1 * mt1 * this->m_pJointsPosition[i][j];
        }
    }

    for (unsigned int i = 0; i < this->m_pJointsPosition.size(); i++) for (int j = 0; j < 20; j++)
    {
        this->m_JoinsInformation[j] = this->m_JoinsInformation[j] + this->m_pJointsPosition[i][j];
    }

    for (int i = 0; i < 20; i++)
    {
        this->m_JoinsInformation[i] = this->m_JoinsInformation[i] / (float) this->m_pJointsPosition.size();
    }
}

void CKinectManager::BestAngle(void)
{

    for (unsigned int i = 1; i < this->m_pJointsPosition.size(); i++)
    {
        OGLMatrix4f mt1; mt1.setTranslation(-this->m_pSkeletonsPosition[i]->x, -this->m_pSkeletonsPosition[i]->y, -this->m_pSkeletonsPosition[i]->z);
        OGLMatrix4f mt2; mt2.setTranslation(this->m_pSkeletonsPosition[0]->x, this->m_pSkeletonsPosition[0]->y, this->m_pSkeletonsPosition[0]->z);
        OGLMatrix4f mr1; mr1.setYRotation(-(*this->m_pSkeletonAngles[0] - *this->m_pSkeletonAngles[i]) * 3.141592f / 180.0f);

        for (int j = 0; j < 20; j++)
        {
            this->m_pJointsPosition[i][j] = mt2 * mr1 * mt1 * this->m_pJointsPosition[i][j];
        }
    }

    for (unsigned int i = 0; this->m_pSkeletonAngles.size() >= 2 && i < this->m_pSkeletonAngles.size() - 1; i++)
    {
        if (abs(*this->m_pSkeletonAngles[i]) <= abs(*this->m_pSkeletonAngles[i + 1])) continue;
        if(this->m_KBase == i) this->m_KBase = i + 1;

        OGLVector4f *aux = this->m_pJointsPosition[i];
        this->m_pJointsPosition[i] = this->m_pJointsPosition[i + 1];
        this->m_pJointsPosition[i + 1] = aux;

        aux = this->m_pSkeletonsColor[i];
        this->m_pSkeletonsColor[i] = this->m_pSkeletonsColor[i + 1];
        this->m_pSkeletonsColor[i + 1] = aux;
    }

    for (int i = 0; i < 20 && this->m_pJointsPosition.size() > 0; i++)
    {
        this->m_JoinsInformation[i] = this->m_pJointsPosition[0][i];
    }
}

int *CKinectManager::getImage(void)
{
	return((this->m_Kinects.size() != 0)? this->m_Kinects[0]->getImage() : NULL);
}
