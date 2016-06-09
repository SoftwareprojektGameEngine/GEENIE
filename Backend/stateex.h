#ifndef STATEEX_H
#define STATEEX_H

#include "osg/State"

class StateEx : public osg::State {
public:
    //!Constructor, which initializes defaultFbo.
    StateEx();

    //!Sets the defaultFbo attribute.
    void setDefaultFbo(GLuint fbo);
    //!Returns the defaultFbo attribute.
    GLuint getDefaultFbo() const;

protected:
    GLuint defaultFbo;
};

#endif // STATEEX_H
