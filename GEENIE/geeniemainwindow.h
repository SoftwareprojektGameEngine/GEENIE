#ifndef GEENIEMAINWINDOW_H
#define GEENIEMAINWINDOW_H

#include <QMainWindow>
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

    QTextDocument* scriptEditorDocument();

protected:
    void closeEvent(QCloseEvent* event);

signals:
    void saveSession();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GEENIEMainWindow *ui;
};

#endif // GEENIEMAINWINDOW_H
