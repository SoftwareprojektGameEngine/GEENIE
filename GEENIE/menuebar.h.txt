#ifndef MENUEBAR_H
#define MENUEBAR_H

#include <QMainWindow>

namespace Ui {
class Menuebar;
}

class Menuebar : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menuebar(QWidget *parent = 0);
    ~Menuebar();

private:
    Ui::Menuebar *ui;
};

#endif // MENUEBAR_H
