#include "inspectorwidget.h"
#include "ui_inspectorwidget.h"
#include <QVBoxLayout>
#include <QDebug>

InspectorWidget::InspectorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InspectorWidget)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout(ui->scrollAreaWidgetContents));
}

InspectorWidget::~InspectorWidget()
{
    delete ui;
}

void InspectorWidget::addWidget(QWidget *widget)
{
    widget->setParent(ui->scrollAreaWidgetContents);
    widget->setGeometry(widget->x(),widget->y(),ui->scrollAreaWidgetContents->width(),widget->height());
    ui->scrollAreaWidgetContents->layout()->addWidget(widget);
}
void InspectorWidget::removeWidget(QWidget* widget)
{
    ui->scrollAreaWidgetContents->layout()->removeWidget(widget);
}

void InspectorWidget::resizeSlot(int h, int w)
{
    setGeometry(this->x(),this->y(),w,h);
}
