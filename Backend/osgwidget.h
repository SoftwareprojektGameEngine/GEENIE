#ifndef OSGWIDGET_H
#define OSGWIDGET_H

#include "backend_global.h"
#include "enginewrapper.h"
#include <QtWidgets/QOpenGLWidget>
#include "osgViewer/Viewer"
#include <QTimer>
#include "osgwrapper.h"

//!OSGWidget class. OpenScenegraph widget for Qt.
class BACKEND_EXPORT OSGWidget : public QOpenGLWidget, public EngineWidgetWrapper {
    Q_OBJECT
public:
    //! Constructor, which initializes the object.
    OSGWidget(OSGWrapper* wrapper = nullptr, QWidget* parentWidget = nullptr, Qt::WindowFlags flags = 0);
    //!Destructo,which cleans the  used storage of the object.
    ~OSGWidget();

    //!Returns and converts the object as a QWidget.
    QWidget* GetWidget();
    //!Changes the camera-position of the viewer.
    bool SetCamera(const Vector& eye, const Vector& center, const Vector& up);
    //!Transmits the changed scene to the viewer and updates the viewer.
    bool BuildSceneGraph(Scene* scene);
    //!Updates the shown scene of the viewer.
    bool UpdateSceneGraph();

protected:
    //!Initializes open GL.
    virtual void initializeGL();
    //!Draws the scene in to the window.
    virtual void paintGL();
    //!Changes the size of the rendering frame.
    virtual void resizeGL(int width, int height);


    osg::ref_ptr<osgViewer::GraphicsWindow> graphicsWindow;
    osg::ref_ptr<osgViewer::Viewer> viewer;

private:
    QTimer heartbeat;
    Scene* scene;
    QHash<QUuid, osg::Node*> nodeMap;
    osg::ref_ptr<osg::Node> rootNode;
    OSGWrapper* wrapper;

    osg::Node* buildNode(Entity* entity);
};

#endif // OSGWIDGET_H
