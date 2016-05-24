#ifndef CULLVISITOREX_H
#define CULLVISITOREX_H

#include "osgUtil/CullVisitor"

class CullVisitorEx : public osgUtil::CullVisitor {
public:
    META_NodeVisitor(Ex, CullVisitorEx)

    CullVisitorEx();
    CullVisitorEx(const CullVisitorEx& cv);
    CullVisitorEx* clone() const;

    virtual void apply(osg::Camera& camera);
};

#endif // CULLVISITOREX_H
