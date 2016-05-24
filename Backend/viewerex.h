#ifndef VIEWEREX_H
#define VIEWEREX_H

/*
 *
 */

#include "osgViewer/Viewer"

class ViewerEx : public osgViewer::Viewer {
public:
    ViewerEx();
    ViewerEx(osg::ArgumentParser& parser);
    ViewerEx(const ViewerEx& viewer, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

    virtual void setUpThreading();
};

#endif // VIEWEREX_H
