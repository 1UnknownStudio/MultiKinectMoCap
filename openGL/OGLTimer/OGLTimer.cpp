#include "./OGLTimer.h"
#include <cstdio>

OGLTimer::OGLTimer(int maxFps)
{

	this->prevTime		= (float) timeGetTime() * 0.001f;
	this->deltaTime		= 0.0f;
	this->actualTime	= 0.0f;

	this->fps			= 0;
	this->auxFps		= 0;

	this->tFps			= (float) (1.0f / maxFps * 2);
	this->auxFpsTime	= 0.0f;
}

OGLTimer::~OGLTimer(void)
{
	this->objectActiveTime.clear();
}

void OGLTimer::update(void)
{

    this->actualTime = (float) timeGetTime() * 0.001f;
	this->deltaTime	 = actualTime - this->prevTime;
	
	this->auxFps++;
	this->prevTime		=  actualTime;
	this->auxFpsTime	+= this->deltaTime;

	if(this->deltaTime < this->tFps)
	{
		Sleep((unsigned int) ((this->tFps - this->deltaTime) * 1000.0f));
	}

	if(this->auxFpsTime >= 1.0f) 
	{
		this->fps			= this->auxFps;
		this->auxFps		= 0;
		this->auxFpsTime	= 0.0f;
	}

	std::map<std::string, float>::iterator it = this->objectActiveTime.begin();
	for(it = this->objectActiveTime.begin(); it != this->objectActiveTime.end(); it++)
	{
		if((it->second = it->second - this->deltaTime) <= 0)
		{
			this->objectActiveTime.erase(it);
			break;
		}
	}
}

int OGLTimer::getFps(void)
{
	return(this->fps);
}

float OGLTimer::getDeltaTime(void)
{
	return(this->deltaTime);
}

bool OGLTimer::isEndTimeObject(std::string name, float time)
{
	bool isEnd = true;

	if(this->objectActiveTime.find(name) != this->objectActiveTime.end())
	{
		isEnd = false;
	}
	else
	{
		this->objectActiveTime.insert(std::pair<std::string, float>(name, (float)time));
	}

	return(isEnd);
}
