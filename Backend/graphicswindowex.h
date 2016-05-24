#ifndef GRAPHICSWINDOWEX_H
#define GRAPHICSWINDOWEX_H

#include "osgViewer/GraphicsWindow"

class GraphicsWindowEx : public osgViewer::GraphicsWindow {
public:
    GraphicsWindowEx(osg::GraphicsContext::Traits* traits);
    GraphicsWindowEx(int x, int y, int width, int height);

    void init();

    virtual bool isSameKindAs(const osg::Object* object) const { return dynamic_cast<const GraphicsWindowEx *>(object) != 0; }
    virtual const char* libraryName() const { return ""; }
    virtual const char* className() const { return "GraphicsWindowEx"; }

    // dummy implementations, assume that graphics context is *always* current and valid.
    virtual bool valid() const { return true; }
    virtual bool realizeImplementation() { return true; }
    virtual bool isRealizedImplementation() const  { return true; }
    virtual void closeImplementation() {}
    virtual bool makeCurrentImplementation() { return true; }
    virtual bool releaseContextImplementation() { return true; }
    virtual void swapBuffersImplementation() {}
    virtual void grabFocus() {}
    virtual void grabFocusIfPointerInWindow() {}
    virtual void raiseWindow() {}
};

#endif // GRAPHICSWINDOWEX_H
