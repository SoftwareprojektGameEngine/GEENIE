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

    void on_openScriptBtn_clicked();

private:
    Ui::GEENIEMainWindow *ui;
};

#endif // GEENIEMAINWINDOW_H
