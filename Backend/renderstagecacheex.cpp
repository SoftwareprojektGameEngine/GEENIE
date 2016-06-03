#include "renderstagecacheex.h"
#include <QDebug>

RenderStageCacheEx::RenderStageCacheEx() {}

RenderStageCacheEx::RenderStageCacheEx(const RenderStageCacheEx &, const osg::CopyOp &) {
    // TODO: implement
    qDebug() << "RenderStageCacheEx copy constructor called";
}

RenderStageCacheEx::~RenderStageCacheEx() {
    for(RenderStageMap::iterator itr = _renderStageMap.begin();
        itr != _renderStageMap.end();
        ++itr)
    {
        itr->first->removeObserver(this);
    }
}

void RenderStageCacheEx::objectDeleted(void *object) {
    osg::Referenced* ref = reinterpret_cast<osg::Referenced*>(object);
    osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(ref);
    OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
    RenderStageMap::iterator itr = _renderStageMap.find(cv);
    if (itr!=_renderStageMap.end())
    {
        _renderStageMap.erase(cv);
    }
}

void RenderStageCacheEx::setRenderStage(osgUtil::CullVisitor *cullVisitor, osgUtil::RenderStage *renderStage) {
    OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
    _renderStageMap[cullVisitor] = renderStage;
    cullVisitor->addObserver(this);
}

osgUtil::RenderStage* RenderStageCacheEx::getRenderStage(osgUtil::CullVisitor *cullVisitor) {
    OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
    return _renderStageMap[cullVisitor].get();
}

void RenderStageCacheEx::resizeGLObjectBuffers(unsigned int maxSize) {
    for(RenderStageMap::const_iterator itr = _renderStageMap.begin();
        itr != _renderStageMap.end();
        ++itr)
    {
        itr->second->resizeGLObjectBuffers(maxSize);
    }
}

void RenderStageCacheEx::releaseGLObjects(osg::State *state) const {
    for(RenderStageMap::const_iterator itr = _renderStageMap.begin();
        itr != _renderStageMap.end();
        ++itr)
    {
        itr->second->releaseGLObjects(state);
    }
}
