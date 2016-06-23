#ifndef OSGWIDGET_H
#define OSGWIDGET_H

#include "backend_global.h"
#include "enginewrapper.h"

#include <QOpenGLWidget>

#include <osg/ref_ptr>

#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>

#include "osgwrapper.h"

class BACKEND_EXPORT OSGWidget : public QOpenGLWidget, public EngineWidgetWrapper {
    Q_OBJECT
public:
    OSGWidget(OSGWrapper* wrapper = nullptr, QWidget* parentWidget = nullptr, Qt::WindowFlags flags = 0);
    virtual ~OSGWidget();

    QWidget* GetWidget();
    bool SetCamera(const Vector& eye, const Vector& center, const Vector& up);
    bool BuildSceneGraph(Scene* scene);
    bool UpdateSceneGraph();

protected:

  virtual void paintEvent( QPaintEvent* paintEvent );
  virtual void paintGL();
  virtual void resizeGL( int width, int height );

  virtual void keyPressEvent( QKeyEvent* event );
  virtual void keyReleaseEvent( QKeyEvent* event );

  virtual void mouseMoveEvent( QMouseEvent* event );
  virtual void mousePressEvent( QMouseEvent* event );
  virtual void mouseReleaseEvent( QMouseEvent* event );
  virtual void wheelEvent( QWheelEvent* event );

  virtual bool event( QEvent* event );

private:

  virtual void onHome();
  virtual void onResize( int width, int height );

  osgGA::EventQueue* getEventQueue() const;

  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> graphicsWindow_;
  osg::ref_ptr<osgViewer::CompositeViewer> viewer_;

private:
    //QTimer heartbeat;
    Scene* scene;
    QHash<QUuid, osg::Node*> nodeMap;
    osg::ref_ptr<osg::Node> rootNode;
    OSGWrapper* wrapper;

    osg::Node* buildNode(Entity* entity);
};

#endif // OSGWIDGET_H
