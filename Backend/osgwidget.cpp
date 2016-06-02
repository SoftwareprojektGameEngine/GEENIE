#include "osgwidget.h"
#include "cullvisitorex.h"
#include "graphicswindowex.h"
#include "viewerex.h"
#include "stateex.h"
#include "components.h"
#include "osg/PositionAttitudeTransform"
#include "osg/Texture2D"

OSGWidget::OSGWidget(OSGWrapper* wrapper, QWidget *parentWidget, Qt::WindowFlags flags) : QOpenGLWidget(parentWidget, flags), nodeMap() {
    this->wrapper = wrapper;
    this->scene = nullptr;

    // setup our custon CullVisitor
    CullVisitorEx* cve = new CullVisitorEx();
    osgUtil::CullVisitor::prototype() = cve;

    // ...
    graphicsWindow = new GraphicsWindowEx(0, 0, width(), height());
    viewer = new ViewerEx();
    viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);

    // setup camera basics
    viewer->getCamera()->setViewport(0, 0, width(), height());
    viewer->getCamera()->setGraphicsContext(graphicsWindow);
    viewer->getCamera()->setClearMask(GL_COLOR_BUFFER_BIT);
    viewer->getCamera()->setClearColor(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

    // setup timer
    connect(&heartbeat, SIGNAL(timeout()), this, SLOT(update()), Qt::QueuedConnection);
    heartbeat.start(10);
}

OSGWidget::~OSGWidget() {
}

QWidget* OSGWidget::GetWidget() {
    return static_cast<QWidget*>(this);
}

bool OSGWidget::SetCamera(const Vector &eye, const Vector& center, const Vector &up) {
    viewer->getCamera()->setViewMatrixAsLookAt(osg::Vec3d(eye.x, eye.y, eye.z), osg::Vec3d(center.x, center.y, center.z), osg::Vec3d(up.x, up.y, up.z));

    return true;
}

bool OSGWidget::BuildSceneGraph(Scene* scene) {
    if (this->scene != nullptr) {
        this->nodeMap.clear();
    }

    this->scene = scene;
    return this->UpdateSceneGraph();
}

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
            QUuid modelID = static_cast<ModelComponent*>(component)->GetModel();
            osg::Geode* model = this->wrapper->models.value(modelID, nullptr);

            if(model != nullptr) {
                group->addChild(model);
            }
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

            if (lightComp->GetLightSourceType() & AMBIENT) {
                Color ambientColor = lightComp->GetAmbientColor();
                light->setAmbient(osg::Vec4(ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a));
            }

            if (lightComp->GetLightSourceType() & DIFFUSE) {
                Color diffuseColor = lightComp->GetDiffuseColor();
                light->setDiffuse(osg::Vec4(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a));
            } else if(lightComp->GetLightSourceType() & SPOT) {
                Vector direction = lightComp->GetSpotlightDirection();
                light->setDirection(osg::Vec3(direction.x, direction.y, direction.z));
                Color diffuseColor = lightComp->GetDiffuseColor();
                light->setDiffuse(osg::Vec4(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a));
            }

            if (lightComp->GetLightSourceType() & SPECULAR) {
                Color specularColor = lightComp->GetSpecularColor();
                light->setSpecular(osg::Vec4(specularColor.r, specularColor.g, specularColor.b, specularColor.a));
            }

            lightSource->setLight(light);
            group->addChild(lightSource);
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
            group->addChild(subEntityNode);
        }
    }

    return rootNode;
}

bool OSGWidget::UpdateSceneGraph() {
    // TODO: fix memory leak
    if(this->scene == nullptr) return true;

    osg::Group* newRootNode = new osg::Group;

    auto iter = this->scene->GetEntities();
    while(iter.hasNext()) {
    //foreach(Entity* entity, this->scene->GetEntities()) {
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

    viewer->setSceneData(this->rootNode.get());

    return true;
}

void OSGWidget::initializeGL() {
    viewer->realize();
}

void OSGWidget::paintGL() {
    if (!isEnabled() || !isVisible()) return;

    // setup graphicsWindow to render to the widgets FBO
    static_cast<StateEx*>(graphicsWindow->getState())->setDefaultFbo(defaultFramebufferObject());

    // render frame
    viewer->frame();
}

void OSGWidget::resizeGL(int width, int height) {
    graphicsWindow->getEventQueue()->windowResize(0, 0, width, height);
    graphicsWindow->resized(0, 0, width, height);
}
