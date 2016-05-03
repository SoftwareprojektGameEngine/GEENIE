#include "loggerwidget.h"
#include "ui_loggerwidget.h"
#include <QDateTime>
#include <QDebug>
#include "loggerlistitem.h"

LoggerWidget::LoggerWidget(QWidget *parent) :
    QWidget(parent),
    _debugChecked(true),
    _errorChecked(true),
    _warningChecked(true),
    _infoChecked(true),
    _filterModel(new LoggerFilterModel(this)),
    _msgModel(new LoggerListModel(this)),
    ui(new Ui::LoggerWidget)
{
    ui->setupUi(this);

    _filterModel->setSourceModel(_msgModel);
    ui->msgConsole->setModel(_filterModel);

    ui->debugCheckBox->setChecked(true);
    ui->errorCheckBox->setChecked(true);
    ui->warningCheckBox->setChecked(true);
    ui->infoCheckBox->setChecked(true);

    connect(this,SIGNAL(filterChanged(bool,bool,bool,bool)),_filterModel,SLOT(filterChanged(bool,bool,bool,bool)));
}

LoggerWidget::~LoggerWidget()
{
    delete ui;
}

void LoggerWidget::newMessage(const QString &msg, logger::MessageType type) const
{
    QString color = QString();
    QString stringType = QString();
    switch(type)
    {
    case logger::MessageType::DEBUG:
    {
        stringType = QString("DEBUG");
        color = QString("#459A06");
        break;
    }
    case logger::MessageType::ERROR:
    {
        stringType = QString("ERROR");
        color = QString("#CC0000");
        break;
    }
    case logger::MessageType::WARNING:
    {
        stringType = QString("WARNING");
        color = QString("#AAA000");
        break;
    }
    case logger::MessageType::INFO:
    {
        stringType = QString("INFO");
        color = QString("White");
        break;
    }
    default:
    {

    }
    }

    QString message = QString("%1 - %2 [%3] %4")
            .arg(QDateTime::currentDateTime().toString(QString("yyyy-MM-dd hh:mm:ss")))
            .arg(color)
            .arg(stringType)
            .arg(msg);

    //QStandardItem* msgItem = new QStandardItem(message);

    _msgModel->append(new LoggerListItem(msg,QDateTime::currentDateTime(),type));

}

void LoggerWidget::on_debugCheckBox_toggled(bool checked)
{
    _debugChecked = checked;
    filter();
}

void LoggerWidget::on_errorCheckBox_toggled(bool checked)
{
    _errorChecked = checked;
    filter();
}

void LoggerWidget::on_warningCheckBox_toggled(bool checked)
{
    _warningChecked = checked;
    filter();
}

void LoggerWidget::on_infoCheckBox_toggled(bool checked)
{
    _infoChecked = checked;
    filter();
}

void LoggerWidget::filter()
{
    emit filterChanged(_debugChecked,_errorChecked,_warningChecked,_infoChecked);
}
