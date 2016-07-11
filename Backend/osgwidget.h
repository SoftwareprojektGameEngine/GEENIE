#ifndef OSGWIDGET_H
#define OSGWIDGET_H

#include "backend_global.h"
#include "enginewrapper.h"

#include <QOpenGLWidget>
#include <QTimer>

#include <osg/ref_ptr>

#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>

#include "osgwrapper.h"

//!OSGWidget class. OpenScenegraph widget for Qt.
class BACKEND_EXPORT OSGWidget : public QOpenGLWidget, public EngineWidgetWrapper {
    Q_OBJECT
public:
    //! Constructor, which initializes the object.
    OSGWidget(OSGWrapper* wrapper = nullptr, QWidget* parentWidget = nullptr, Qt::WindowFlags flags = 0);

    //!Destructor, which cleans the used storage of the object.
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

  virtual void paintEvent( QPaintEvent* paintEvent );
  //!Draws the scene in to the window.
  virtual void paintGL();
    //!Changes the size of the rendering frame.
  virtual void resizeGL( int width, int height );

  virtual void keyPressEvent( QKeyEvent* event );
  virtual void keyReleaseEvent( QKeyEvent* event );

  virtual void mouseMoveEvent( QMouseEvent* event );
  virtual void mousePressEvent( QMouseEvent* event );
  virtual void mouseReleaseEvent( QMouseEvent* event );
  virtual void wheelEvent( QWheelEvent* event );

  virtual bool event( QEvent* event );

    //Initializes open GL.
    //virtual void initializeGL();
  virtual void onResize(int width, int height);

private:
    osgGA::EventQueue* getEventQueue() const;

    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> graphicsWindow_;
    osg::ref_ptr<osgViewer::CompositeViewer> viewer_;
    QTimer heartbeat;
    Scene* scene;
    QHash<QUuid, osg::Node*> nodeMap;
    osg::ref_ptr<osg::Node> rootNode;
    OSGWrapper* wrapper;

    osg::Node* buildNode(Entity* entity);
};

#endif // OSGWIDGET_H
