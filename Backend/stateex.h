#ifndef STATEEX_H
#define STATEEX_H

#include "osg/State"

class StateEx : public osg::State {
public:
    StateEx();

    void setDefaultFbo(GLuint fbo);
    GLuint getDefaultFbo() const;

protected:
    GLuint defaultFbo;
};

#endif // STATEEX_H
