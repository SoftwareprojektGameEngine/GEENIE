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

    /*!
     * \brief objectDeleted
     * \param object
     */
    virtual void objectDeleted(void* object);
    //!Sets Render Stage of CullVisitor.
    void setRenderStage(osgUtil::CullVisitor* cullVisitor, osgUtil::RenderStage* renderStage);
    //!Returns the RenderStage of the CullVisito.
    osgUtil::RenderStage* getRenderStage(osgUtil::CullVisitor* cullVisitor);

    //!Resizes the GL-Object-Buffers.
    virtual void resizeGLObjectBuffers(unsigned int maxSize);
    //!Cleans the used storage of the GL Objects.
    virtual void releaseGLObjects(osg::State* state = nullptr) const;

private:
    typedef std::map<osgUtil::CullVisitor*, osg::ref_ptr<osgUtil::RenderStage> > RenderStageMap;

    OpenThreads::Mutex _mutex;
    RenderStageMap _renderStageMap;
};

#endif // RENDERSTAGECACHEEX_H
