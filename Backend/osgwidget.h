#ifndef OSGWIDGET_H
#define OSGWIDGET_H

#include "backend_global.h"
#include "enginewrapper.h"
#include <QtWidgets/QOpenGLWidget>
#include "osgViewer/Viewer"
#include <QTimer>
#include "osgwrapper.h"


class BACKEND_EXPORT OSGWidget : public QOpenGLWidget, public EngineWidgetWrapper {
    Q_OBJECT
public:
    OSGWidget(OSGWrapper* wrapper = nullptr, QWidget* parentWidget = nullptr, Qt::WindowFlags flags = 0);
    ~OSGWidget();

    QWidget* GetWidget();
    bool SetCamera(const Vector& eye, const Vector& center, const Vector& up);
    bool BuildSceneGraph(Scene* scene);
    bool UpdateSceneGraph();

protected:
    virtual void initializeGL();
    virtual void paintGL();
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
