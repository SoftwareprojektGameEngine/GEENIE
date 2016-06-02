#include "sceneeditwidget.h"
#include "ui_sceneeditwidget.h"

SceneEditWidget::SceneEditWidget(EngineWrapper* engine, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneEditWidget)
{
    ui->setupUi(this);

    this->engine = engine;
    this->engineWidget = engine->CreateWidget(this);

    engineWidget->GetWidget()->setParent(this);
    engineWidget->GetWidget()->setGeometry(this->findChild<QFrame*>(QString("frame"))->geometry());
    engineWidget->GetWidget()->setVisible(true);
}

SceneEditWidget::~SceneEditWidget()
{
    delete engineWidget;
    delete ui;
}
