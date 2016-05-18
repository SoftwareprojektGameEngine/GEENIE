#ifndef SCRIPTWINDOW_H
#define SCRIPTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ScriptWindow;
}

class ScriptWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScriptWindow(QWidget *parent = 0);
    ~ScriptWindow();

private:
    Ui::ScriptWindow *ui;
};

#endif // SCRIPTWINDOW_H
