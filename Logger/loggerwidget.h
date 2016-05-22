#ifndef LOGGERWIDGET_H
#define LOGGERWIDGET_H

#include <QWidget>
#include "logger_global.h"
#include "loggerlistmodel.h"
#include "loggerfiltermodel.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

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

signals:
    void filterChanged(bool debug, bool error, bool warning, bool info);

private slots:
    void on_debugCheckBox_toggled(bool checked);

    void on_errorCheckBox_toggled(bool checked);

    void on_warningCheckBox_toggled(bool checked);

    void on_infoCheckBox_toggled(bool checked);

private:

    void filter();

    bool _debugChecked;
    bool _errorChecked;
    bool _warningChecked;
    bool _infoChecked;

    LoggerFilterModel* _filterModel;
    //QStandardItemModel* _msgModel;
    LoggerListModel* _msgModel;

    Ui::LoggerWidget *ui;
};

#endif // LOGGERWIDGET_H
