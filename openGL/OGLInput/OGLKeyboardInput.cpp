#include "./OGLKeyboardInput.h"

OGLKeyboardInput::OGLKeyboardInput(void)
{
}

OGLKeyboardInput::~OGLKeyboardInput(void)
{
    this->intKeys.clear();
}

void OGLKeyboardInput::addKey(const std::string &name, unsigned int key)
{
    this->intKeys[name][key] = false;
}

void OGLKeyboardInput::update()
{
    for(IntKeysMap::iterator it = this->intKeys.begin(); it != this->intKeys.end(); it++)
    {
        it->second.begin()->second = (GetAsyncKeyState(it->second.begin()->first)) ? true : false;
    }
}

bool OGLKeyboardInput::isKeyPressed(const std::string &name)
{
    bool down = false;
    IntKeysMap::iterator it = this->intKeys.find(name);

    down = (it != this->intKeys.end()) ? it->second.begin()->second : false;
    return(down);
}
