#ifndef GEENIEMAINWINDOW_H
#define GEENIEMAINWINDOW_H

#include <QMainWindow>
#include "scripthighlighter.h"
#include "logger.h"

class QTextDocument;

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::GEENIEMainWindow *ui;
};

#endif // GEENIEMAINWINDOW_H
