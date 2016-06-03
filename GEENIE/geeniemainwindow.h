#ifndef GEENIEMAINWINDOW_H
#define GEENIEMAINWINDOW_H

#include <QMainWindow>
#include "scripthighlighter.h"
#include "logger.h"

class QTextDocument;
class Project;

namespace Ui {
class GEENIEMainWindow;
}

class GEENIEMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GEENIEMainWindow(QWidget *parent = 0);
    ~GEENIEMainWindow();

    void setScriptType(Highlighter::Types type);
    void setScript(QString& script);

    QTextDocument* scriptEditorDocument();

protected:
    void closeEvent(QCloseEvent* event);

signals:
    void saveSession();
    void changeScriptType(Highlighter::Types);

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_actionExit_triggered();

    /*!
     * \fn void on_openScriptBtn_clicked()
     * \brief Load script on button click
     * \bug https://bugreports.qt.io/browse/QTBUG-52618
     */
    void on_openScriptBtn_clicked();

    /*!
     * \fn void on_saveScriptBtn_clicked()
     * \brief Save script on button click
     * \bug https://bugreports.qt.io/browse/QTBUG-52618
     */
    void on_saveScriptBtn_clicked();

private:
    Ui::GEENIEMainWindow *ui;
};

#endif // GEENIEMAINWINDOW_H
