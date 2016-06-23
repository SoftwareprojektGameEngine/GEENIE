#include "osgwidget.h"
#include "cullvisitorex.h"
#include "graphicswindowex.h"
#include "viewerex.h"
#include "stateex.h"
#include "components.h"
#include "osg/PositionAttitudeTransform"
#include "osg/Texture2D"
#include <QDebug>

#include <osg/Camera>

#include <osg/DisplaySettings>
#include <osg/Geode>
#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/StateSet>

#include <osgDB/WriteFile>
#include <osgDB/ReadFile>

#include <osgGA/EventQueue>
#include <osgGA/TrackballManipulator>

#include <osgUtil/IntersectionVisitor>
#include <osgUtil/PolytopeIntersector>

#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>

#include "compositeviewerex.h"

#include <QKeyEvent>
#include <QPainter>
#include <QWheelEvent>

OSGWidget::OSGWidget(OSGWrapper* wrapper, QWidget *parentWidget, Qt::WindowFlags flags)
    : QOpenGLWidget(parentWidget, flags),
      graphicsWindow_(new osgViewer::GraphicsWindowEmbedded(this->x(), this->y(), this->width(), this->height())),
      viewer_(new CompositeViewerEx()),
      nodeMap() {
    this->wrapper = wrapper;
    this->scene = nullptr;

    osg::Camera* camera = new osg::Camera;
    camera->setViewport( 0, 0, this->width(), this->height() );
    camera->setClearColor( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
    camera->setProjectionMatrixAsPerspective( 30.f, ((float)this->width())/((float)this->height()), 1.f, 1000.f );
    camera->setGraphicsContext( graphicsWindow_ );
    camera->setViewMatrixAsLookAt(osg::Vec3d(0.0,0.0,0.0), osg::Vec3d(0.0,0.0,1.0), osg::Vec3d(0.0,1.0,0.0));

    osgViewer::View* view = new osgViewer::View;
    view->setCamera( camera );
    //view->setSceneData( osgDB::readNodeFile("D:\\Studium\\ss2016\\SWP\\GEENIE\\OpenScenegraph\\data\\avatar.osg") );
    //view->setSceneData(geode);
    view->addEventHandler( new osgViewer::StatsHandler );

    osgGA::TrackballManipulator* manipulator = new osgGA::TrackballManipulator;
    manipulator->setAllowThrow( false );

    view->setCameraManipulator( manipulator );


    viewer_->addView( view );
    viewer_->setThreadingModel( osgViewer::CompositeViewer::SingleThreaded );
    viewer_->realize();

    // This ensures that the widget will receive keyboard events. This focus
    // policy is not set by default. The default, Qt::NoFocus, will result in
    // keyboard events that are ignored.
    this->setFocusPolicy( Qt::StrongFocus );
    this->setMinimumSize( 100, 100 );

    // Ensures that the widget receives mouse move events even though no
    // mouse button has been pressed. We require this in order to let the
    // graphics window switch viewports properly.
    this->setMouseTracking( true );
    /*// setup our custon CullVisitor
    CullVisitorEx* cve = new CullVisitorEx();
    osgUtil::CullVisitor::prototype() = cve;

    // ...
    graphicsWindow = new GraphicsWindowEx(x(), y(), width(), height());
    viewer = new ViewerEx();
    viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);

    // setup camera basics
    viewer->getCamera()->setViewport(0, 0, width(), height());
    viewer->getCamera()->setGraphicsContext(graphicsWindow.get());
    viewer->getCamera()->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    viewer->getCamera()->setClearColor(osg::Vec4(1.0f, 0.0f, 0.0f, 0.0f));

    // setup timer
    connect(&heartbeat, SIGNAL(timeout()), this, SLOT(update()), Qt::QueuedConnection);
    heartbeat.start(10);*/
}

OSGWidget::~OSGWidget() {
}

void OSGWidget::paintEvent( QPaintEvent* /* paintEvent */ )
{
  this->makeCurrent();

  QPainter painter( this );
  painter.setRenderHint( QPainter::Antialiasing );

  this->paintGL();

  painter.end();

  this->doneCurrent();
}

void OSGWidget::paintGL()
{
  viewer_->frame();
}

void OSGWidget::resizeGL( int width, int height )
{
  this->getEventQueue()->windowResize( this->x(), this->y(), width, height );
  graphicsWindow_->resized( this->x(), this->y(), width, height );

  this->onResize( width, height );
}

void OSGWidget::keyPressEvent( QKeyEvent* event )
{
  QString keyString   = event->text();
  const char* keyData = keyString.toLocal8Bit().data();

  //qDebug() << "key pressed: " << keyString;

  this->getEventQueue()->keyPress( osgGA::GUIEventAdapter::KeySymbol( *keyData ) );
}

void OSGWidget::keyReleaseEvent( QKeyEvent* event )
{
  QString keyString   = event->text();
  const char* keyData = keyString.toLocal8Bit().data();

  this->getEventQueue()->keyRelease( osgGA::GUIEventAdapter::KeySymbol( *keyData ) );
}

void OSGWidget::mouseMoveEvent( QMouseEvent* event )
{
  // Note that we have to check the buttons mask in order to see whether the
  // left button has been pressed. A call to `button()` will only result in
  // `Qt::NoButton` for mouse move events.
    this->getEventQueue()->mouseMotion( static_cast<float>( event->x() ),
                                        static_cast<float>( event->y() ) );
}

void OSGWidget::mousePressEvent( QMouseEvent* event )
{
    // 1 = left mouse button
    // 2 = middle mouse button
    // 3 = right mouse button

    unsigned int button = 0;

    switch( event->button() )
    {
    case Qt::LeftButton:
      button = 1;
      break;

    case Qt::MiddleButton:
      button = 2;
      break;

    case Qt::RightButton:
      button = 3;
      break;

    default:
      break;
    }

    this->getEventQueue()->mouseButtonPress( static_cast<float>( event->x() ),
                                             static_cast<float>( event->y() ),
                                             button );
}

void OSGWidget::mouseReleaseEvent(QMouseEvent* event)
{
  // Selection processing: Store end position and obtain selected objects
  // through polytope intersection.
  // Normal processing
    // 1 = left mouse button
    // 2 = middle mouse button
    // 3 = right mouse button

    unsigned int button = 0;

    switch( event->button() )
    {
    case Qt::LeftButton:
      button = 1;
      break;

    case Qt::MiddleButton:
      button = 2;
      break;

    case Qt::RightButton:
      button = 3;
      break;

    default:
      break;
    }

    this->getEventQueue()->mouseButtonRelease( static_cast<float>( event->x() ),
                                               static_cast<float>( event->y() ),
                                               button );
}

void OSGWidget::wheelEvent( QWheelEvent* event )
{
  event->accept();
  int delta = event->delta();

  osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ?   osgGA::GUIEventAdapter::SCROLL_UP
                                                               : osgGA::GUIEventAdapter::SCROLL_DOWN;

  this->getEventQueue()->mouseScroll( motion );
}

bool OSGWidget::event( QEvent* event )
{
  bool handled = QOpenGLWidget::event( event );

  // This ensures that the OSG widget is always going to be repainted after the
  // user performed some interaction. Doing this in the event handler ensures
  // that we don't forget about some event and prevents duplicate code.
  switch( event->type() )
  {
  case QEvent::KeyPress:
  case QEvent::KeyRelease:
  case QEvent::MouseButtonDblClick:
  case QEvent::MouseButtonPress:
  case QEvent::MouseButtonRelease:
  case QEvent::MouseMove:
  case QEvent::Wheel:
    this->update();
    break;

  default:
    break;
  }

  return handled;
}

void OSGWidget::onHome()
{
  osgViewer::ViewerBase::Views views;
  viewer_->getViews( views );

  for( std::size_t i = 0; i < views.size(); i++ )
  {
    osgViewer::View* view = views.at(i);
    view->home();
  }
}

void OSGWidget::onResize( int width, int height )
{
  std::vector<osg::Camera*> cameras;
  viewer_->getCameras( cameras );

  //assert( cameras.size() == 2 );

  cameras[0]->setViewport( 0, 0, width, height );
  //cameras[1]->setViewport( width / 2, 0, width / 2, height );
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
  osgGA::EventQueue* eventQueue = graphicsWindow_->getEventQueue();

  if( eventQueue )
    return eventQueue;
  else
    throw std::runtime_error( "Unable to obtain valid event queue");
}

QWidget* OSGWidget::GetWidget() {
    return static_cast<QWidget*>(this);
}

bool OSGWidget::SetCamera(const Vector &eye, const Vector& center, const Vector &up) {
    //viewer->getCamera()->setViewMatrixAsLookAt(osg::Vec3d(eye.x, eye.y, eye.z), osg::Vec3d(center.x, center.y, center.z), osg::Vec3d(up.x, up.y, up.z));

    return true;
}

bool OSGWidget::BuildSceneGraph(Scene* scene) {
    if (this->scene != nullptr) {
        this->nodeMap.clear();
    }

    this->scene = scene;
    return this->UpdateSceneGraph();
}

static int lightNum = 0;
osg::Node* OSGWidget::buildNode(Entity* entity) {
    osg::Group* group = new osg::Group;
    osg::Node* rootNode = group;

    auto compIter = entity->GetComponents();
    while(compIter.hasNext()) {
        compIter.next();
        Component* component = compIter.value();

        switch(component->GetType()) {
        /*case POSITION_COMPONENT:
            {
                Vector pos = static_cast<PositionComponent*>(comp)->GetPosition();

                osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform();
                pat->setPosition(osg::Vec3d(pos.x, pos.y, pos.z));

                pat->addChild(rootNode);
                rootNode = pat;
            }
            break;*/
        case MODEL:
        {
            /*QUuid modelID = static_cast<ModelComponent*>(component)->GetModel();
            qDebug() << "adding model " << modelID << " to entity " << entity->GetID();
            osg::Node* model = this->wrapper->models.value(modelID, nullptr);

            if(model != nullptr) {
                const osg::BoundingSphere& loaded_bs = rootNode->getBound();
                osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform();
                pat->setPivotPoint(loaded_bs.center());
                pat->addChild(model);

                group->addChild(pat);
            } else {
                qDebug() << "model " << modelID << " not found!";
            }*/
            osg::Sphere* sphere    = new osg::Sphere( osg::Vec3( 0.f, 0.f, 0.f ), 0.25f );
            osg::ShapeDrawable* sd = new osg::ShapeDrawable( sphere );
            sd->setColor( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );
            sd->setName( "A nice sphere" );

            osg::Geode* geode = new osg::Geode;
            geode->addDrawable( sd );
            //osg::Node* node = osgDB::readNodeFile(std::string("D:\\Studium\\ss2016\\SWP\\GEENIE\\OpenScenegraph\\data\\avatar.osg"));
            //auto center = node->computeBound().center();

            //qDebug() << "node = " << ((node == nullptr) ? "NULL" : "(ptr)");
            //qDebug() << center.x() << " / " << center.y() << " / " << center.z();

            // Set material for basic lighting and enable depth tests. Else, the sphere
            // will suffer from rendering errors.
            {
              osg::StateSet* stateSet = geode->getOrCreateStateSet();
              osg::Material* material = new osg::Material;

              material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

              stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
              stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
            }

            group->addChild(geode);

        }
            break;
        case MATERIAL:
        {
            QUuid materialID = static_cast<MaterialComponent*>(component)->GetMaterial();
            osg::Material* material = wrapper->materials.value(materialID, nullptr);

            if (material != nullptr) {
                osg::StateSet* state = group->getOrCreateStateSet();
                state->setAttribute(material, osg::StateAttribute::OVERRIDE);
            }
        }
            break;
        case LIGHT:
        {
            osg::Light* light = new osg::Light();
            osg::LightSource* lightSource = new osg::LightSource();

            LightComponent* lightComp = static_cast<LightComponent*>(component);
            //qDebug() << "adding light to entity " << entity->GetID();

            if ((lightComp->GetLightSourceType() & AMBIENT) != 0) {
                //qDebug() << "adding ambient lignt";
                Color ambientColor = lightComp->GetAmbientColor();
                light->setAmbient(osg::Vec4(ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a));
            }

            if ((lightComp->GetLightSourceType() & DIFFUSE) != 0) {
                Color diffuseColor = lightComp->GetDiffuseColor();
                light->setDiffuse(osg::Vec4(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a));
            } else if((lightComp->GetLightSourceType() & SPOT) != 0) {
                Vector direction = lightComp->GetSpotlightDirection();
                light->setDirection(osg::Vec3(direction.x, direction.y, direction.z));
                Color diffuseColor = lightComp->GetDiffuseColor();
                light->setDiffuse(osg::Vec4(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a));
            }

            if ((lightComp->GetLightSourceType() & SPECULAR) != 0) {
                Color specularColor = lightComp->GetSpecularColor();
                light->setSpecular(osg::Vec4(specularColor.r, specularColor.g, specularColor.b, specularColor.a));
            }

            light->setLightNum(lightNum++);
            lightSource->setLight(light);
            group->addChild(lightSource);
            //qDebug() << "light added";
        }
            break;
        case SHADER:
            break;
        case TEXTURE:
        {
            QUuid textureID = static_cast<TextureComponent*>(component)->GetTexture();
            int textureIndex = static_cast<TextureComponent*>(component)->GetTextureIndex();
            osg::Image* image = wrapper->textures.value(textureID, nullptr);

            if (image != nullptr) {
                osg::Texture2D* texture = new osg::Texture2D();
                texture->setImage(image);

                osg::StateSet* state = group->getOrCreateStateSet();
                state->setTextureAttribute(textureIndex, texture, osg::StateAttribute::OVERRIDE);
                state->setTextureMode(textureIndex, GL_TEXTURE_2D, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
            }
        }
            break;
        case POSITION:
        {
            //qDebug() << "adding position to entity " << entity->GetID();
            Vector pos = static_cast<PositionComponent*>(component)->GetPosition();
            osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform();
            pat->setPosition(osg::Vec3d(pos.x, pos.y, pos.z));
            pat->addChild(rootNode);
            rootNode = pat;
        }
            break;
        default:
            // ignore scripts + sound
            break;
        }
    }

    auto entityIter = entity->GetSubEntities();
    while(entityIter.hasNext()) {
        entityIter.next();
        Entity* subEntity = entityIter.value();

        osg::Node* subEntityNode = buildNode(subEntity);
        if (subEntityNode != nullptr) {
            //qDebug() << "adding entity " << subEntity->GetID() << " to entity " << entity->GetID();
            group->addChild(subEntityNode);
        }
    }

    return rootNode;
}

bool OSGWidget::UpdateSceneGraph() {
    // memory leak?
    if(this->scene == nullptr) return true;
    lightNum = 0;

    osg::Group* newRootNode = new osg::Group;

    auto iter = this->scene->GetEntities();
    while(iter.hasNext()) {
        iter.next();
        Entity* entity = iter.value();

        //if(!nodeMap.contains(entity->GetID())) {
            // new entity! build nodes
        //} else if(entity->WasChanged()) {
            // changed entity! update/build nodes
        //}
        osg::Node* node = buildNode(entity);
        nodeMap.insert(entity->GetID(), node);
        newRootNode->addChild(node);
    }

    this->rootNode = newRootNode;

    //viewer->setSceneData(this->rootNode.get());

    return true;
}

/*void OSGWidget::initializeGL() {
    viewer->realize();
}

void OSGWidget::paintGL() {
    //if (!isEnabled() || !isVisible()) return;

    // setup graphicsWindow to render to the widgets FBO
    static_cast<StateEx*>(graphicsWindow->getState())->setDefaultFbo(defaultFramebufferObject());

    // render frame
    viewer->frame();
}

void OSGWidget::resizeGL(int width, int height) {
    graphicsWindow->getEventQueue()->windowResize(this->x(), this->y(), width, height);
    graphicsWindow->resized(x(), y(), width, height);

    viewer->getCamera()->setViewport(0, 0, width, height);
}
*/
