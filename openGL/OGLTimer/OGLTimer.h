#pragma once

#include <map>
#include <string>
#include <iostream>
#include <iterator>
#include <Windows.h>

class OGLTimer
{
    private:
        float prevTime;
        float deltaTime;
        float actualTime;
        std::map<std::string, float> objectActiveTime;

        int fps;
        int auxFps;
        float tFps;
        float auxFpsTime;

    public:
        OGLTimer                (int);
        ~OGLTimer               ();

        int     getFps          (void);
        void    update          (void);
        float   getDeltaTime    (void);
        bool    isEndTimeObject (std::string name, float time);
};
