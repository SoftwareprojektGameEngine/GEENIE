#ifndef LOGGERWIDGET_H
#define LOGGERWIDGET_H

#include <QWidget>
#include "logger_global.h"

namespace Ui {
class LoggerWidget;
}

class LOGGERSHARED_EXPORT LoggerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoggerWidget(QWidget *parent = 0);
    ~LoggerWidget();

    void newMessage(const QString& msg, logger::MessageType type) const;

private:
    Ui::LoggerWidget *ui;
};

#endif // LOGGERWIDGET_H
