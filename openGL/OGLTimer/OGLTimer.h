#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <Windows.h>

class OGLTimer
{
	private:
		LARGE_INTEGER m_timeFreq;
		LARGE_INTEGER m_lastTime;
		LARGE_INTEGER m_actualTime;

        double m_gameFps;
        double m_gameTime;

        double m_frameTime;
        double m_totalFrameTime;

        double m_speedFactor;
        std::map<std::string, double> m_pObjectTimer;

        unsigned int m_fpsLimit;
        unsigned int m_framesCount;

        void updateFps          (void);
        void updateTimer        (void);
        void updateObjectTimer  (void);

	public:
		OGLTimer				(unsigned int fpsControl);
		~OGLTimer				();

		void	update			(void);
        
        double  getFps              (void);
        double  getSpeedFactor      (void);
        double	getFrameTimeInMs	(void);

        bool    endOfTime       (const std::string &object, double ms);
};
