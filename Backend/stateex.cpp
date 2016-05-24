#include "stateex.h"

StateEx::StateEx() :
    defaultFbo(0)
{
}

void StateEx::setDefaultFbo(GLuint fbo)
{
    defaultFbo = fbo;
}

GLuint StateEx::getDefaultFbo() const
{
    return defaultFbo;
}
