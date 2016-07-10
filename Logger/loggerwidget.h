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

/*!
 * \brief The LoggerWidget class is the GUI-element for the logger, which displays all messages and controls
 */
class LOGGERSHARED_EXPORT LoggerWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor
     * \param parent
     */
    explicit LoggerWidget(QWidget *parent = 0);
    ~LoggerWidget();

    /*!
     * \brief Creates a new message
     * \param msg
     * \param type
     */
    void newMessage(const QString& msg, logger::MessageType type) const;

signals:
    /*!
     * \brief Signals when the filtering through the comboboxes has changed.
     * \param debug
     * \param error
     * \param warning
     * \param info
     */
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
