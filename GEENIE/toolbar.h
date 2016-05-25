#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

namespace Ui {
class Toolbar;
}

class Toolbar : public QWidget
{
    Q_OBJECT

public:
    explicit Toolbar(QWidget *parent = 0);
    ~Toolbar();

private:
    Ui::Toolbar *ui;
};

#endif // TOOLBAR_H
