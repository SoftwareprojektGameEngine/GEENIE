#ifndef RENDERSTAGECACHEEX_H
#define RENDERSTAGECACHEEX_H

#include "osgUtil/CullVisitor"
//!Extends and combines the functionality of osg::Object and osg::Observer.
class RenderStageCacheEx : public osg::Object, public osg::Observer {
public:
    //!Constructor of RenderStageCacheEx.
    RenderStageCacheEx();
    //!Copyconstructor of RenderStageCacheEx.
    RenderStageCacheEx(const RenderStageCacheEx&, const osg::CopyOp&);
    //!Cleans the used storage and ends all open threads of the RenderStageMap object.
    virtual ~RenderStageCacheEx();

    META_Object(Ex, RenderStageCacheEx)

    virtual void objectDeleted(void* object);
    void setRenderStage(osgUtil::CullVisitor* cullVisitor, osgUtil::RenderStage* renderStage);
    osgUtil::RenderStage* getRenderStage(osgUtil::CullVisitor* cullVisitor);

    virtual void resizeGLObjectBuffers(unsigned int maxSize);
    virtual void releaseGLObjects(osg::State* state = nullptr) const;

private:
    typedef std::map<osgUtil::CullVisitor*, osg::ref_ptr<osgUtil::RenderStage> > RenderStageMap;

    OpenThreads::Mutex _mutex;
    RenderStageMap _renderStageMap;
};

#endif // RENDERSTAGECACHEEX_H
