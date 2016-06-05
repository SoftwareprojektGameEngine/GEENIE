#ifndef GRAPHICSWINDOWEX_H
#define GRAPHICSWINDOWEX_H

#include "osgViewer/GraphicsWindow"

//!Extends the osgViewer::GraphicsWindow class.
class GraphicsWindowEx : public osgViewer::GraphicsWindow {
public:
    //!Constructor, which stores a traits object and initializes the object.
    GraphicsWindowEx(osg::GraphicsContext::Traits* traits);
    //!Constructor, which intializes a traits object and initializes the object.
    GraphicsWindowEx(int x, int y, int width, int height);

    //!Initializes a stackex object.
    void init();

    //!Tests if the input Object, is an instance with type GraphicsWindowEx. Returns true if it is.
    virtual bool isSameKindAs(const osg::Object* object) const { return dynamic_cast<const GraphicsWindowEx *>(object) != 0; }
    //!Returns an empty string.;
    virtual const char* libraryName() const { return ""; }
    //!Returns a const char*, which contains the name of the Class.
    virtual const char* className() const { return "GraphicsWindowEx"; }

    //!Dummy implementation, assume that graphics context is "always" current and valid. Returns true.
    virtual bool valid() const { return true; }
    //Dummy implementation, assume that graphics context is "always" current and valid. Returns true.
    virtual bool realizeImplementation() { return true; }
    //Dummy implementation, assume that graphics context is "always" current and valid. Returns true.
    virtual bool isRealizedImplementation() const  { return true; }
    //Dummy implementation, assume that graphics context is "always" current and valid. Returns true.
    virtual void closeImplementation() {}
    //Dummy implementation, assume that graphics context is "always" current and valid. Returns true.
    virtual bool makeCurrentImplementation() { return true; }
    //Dummy implementation, assume that graphics context is "always" current and valid. Returns true.
    virtual bool releaseContextImplementation() { return true; }
    //Dummy implementation, assume that graphics context is "always" current and valid. Returns true.
    virtual void swapBuffersImplementation() {}
    //Dummy implementation, assume that graphics context is "always" current and valid. Returns true.
    virtual void grabFocus() {}
    //Dummy implementation, assume that graphics context is "always" current and valid. Returns true.
    virtual void grabFocusIfPointerInWindow() {}
    //Dummy implementation, assume that graphics context is "always" current and valid. Returns true.
    virtual void raiseWindow() {}
};

#endif // GRAPHICSWINDOWEX_H
