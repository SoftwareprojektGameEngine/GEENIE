#ifndef RENDERSTAGEEX_H
#define RENDERSTAGEEX_H

#include "osgUtil/RenderStage"

class RenderStageEx : public osgUtil::RenderStage {
public:
    RenderStageEx();
    //!osgUtil::RenderStage::drawInner(...)
    void drawInner(osg::RenderInfo &renderInfo, osgUtil::RenderLeaf*& previous, bool &doCopyTexture);
};

#endif // RENDERSTAGEEX_H
