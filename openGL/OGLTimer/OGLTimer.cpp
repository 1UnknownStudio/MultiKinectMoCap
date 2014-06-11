#include "./OGLTimer.h"
#include <cstdio>

OGLTimer::OGLTimer(unsigned int fpsControl)
{
    QueryPerformanceCounter(&this->m_lastTime);
    QueryPerformanceFrequency(&this->m_timeFreq);

    this->m_fpsLimit    = fpsControl;
    this->m_speedFactor = 1.0;
    
    this->m_actualTime.QuadPart = 0L;
    this->m_timeFreq.QuadPart = 0L;

    this->m_framesCount = 0;
    this->m_totalFrameTime = 0;
}

OGLTimer::~OGLTimer(void)
{
    this->m_pObjectTimer.clear();
}

void OGLTimer::updateTimer(void)
{
    QueryPerformanceCounter(&this->m_actualTime);
    QueryPerformanceFrequency(&this->m_timeFreq);

    this->m_frameTime = (double) (this->m_actualTime.QuadPart - this->m_lastTime.QuadPart) / (double) this->m_timeFreq.QuadPart;
    this->m_gameTime =  (double) this->m_actualTime.QuadPart / (double) this->m_timeFreq.QuadPart;

    this->m_speedFactor = this->m_fpsLimit / (1.0 / this->m_frameTime);
    if(this->m_speedFactor <= 0.0) this->m_speedFactor = 1.0;

    this->m_lastTime  = this->m_actualTime;
}

void OGLTimer::updateFps(void)
{
   
    this->m_framesCount++;
    this->m_totalFrameTime += this->m_frameTime;
    this->m_gameFps = this->m_framesCount / this->m_totalFrameTime;

    if(this->m_totalFrameTime * 1000.0 > 1000.0)
    {
         this->m_framesCount = 0;
         this->m_totalFrameTime = 0.0;
    }
}

void OGLTimer::updateObjectTimer(void)
{
    std::vector<std::map<std::string, double>::iterator> its;

    for(std::map<std::string, double>::iterator it = this->m_pObjectTimer.begin(); it != this->m_pObjectTimer.end(); it++)
    {
        if(this->m_gameTime >= it->second) its.push_back(it);
    }

    for(unsigned int i = 0; i < its.size(); i++)
    {
        this->m_pObjectTimer.erase(its.at(i));
    }
}

void OGLTimer::update(void)
{
    this->updateTimer();

    this->updateFps();
    this->updateObjectTimer();
}

bool OGLTimer::endOfTime(const std::string &object, double ms)
{
    bool isEndOfTimer = false;
    std::map<std::string, double>::iterator it = this->m_pObjectTimer.find(object);

    if(it == this->m_pObjectTimer.end())
    {
        this->m_pObjectTimer.insert(std::pair<std::string, double>(object, this->m_gameTime + ms));
        isEndOfTimer = true;
    }

    return(isEndOfTimer);
}

double OGLTimer::getFrameTimeInMs(void)
{
    return(this->m_frameTime * 1000.0);
}

double OGLTimer::getSpeedFactor(void)
{
    return(this->m_speedFactor);
}

double OGLTimer::getFps(void)
{
    return(this->m_gameFps);
}
