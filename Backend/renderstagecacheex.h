#ifndef RENDERSTAGECACHEEX_H
#define RENDERSTAGECACHEEX_H

#include "osgUtil/CullVisitor"

class RenderStageCacheEx : public osg::Object, public osg::Observer {
public:
    RenderStageCacheEx();
    RenderStageCacheEx(const RenderStageCacheEx&, const osg::CopyOp&);
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
