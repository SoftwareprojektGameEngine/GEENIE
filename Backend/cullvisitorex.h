#ifndef CULLVISITOREX_H
#define CULLVISITOREX_H

#include "osgUtil/CullVisitor"

//!Extents the osgUtil::CullVisitor class. Adds a new apply method.
class CullVisitorEx : public osgUtil::CullVisitor {
public:
    META_NodeVisitor(Ex, CullVisitorEx)

    CullVisitorEx(); //!Constructor which calls the constructor of osgUtils::CullVisitor.
    CullVisitorEx(const CullVisitorEx& cv); //!Copyconstructor which calls the copyconstructor of osgUtils::Cullvisitor.
    CullVisitorEx* clone() const;//!Returns a clone of the object.

    virtual void apply(osg::Camera& camera);//!Apply changes og osg::Camera settings.
};

#endif // CULLVISITOREX_H
