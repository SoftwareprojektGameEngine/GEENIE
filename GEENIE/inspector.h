#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

namespace Ui {
class Inspector;
}

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(QWidget *parent = 0);
    ~Inspector();

private:
    Ui::Inspector *ui;
};

#endif // INSPECTOR_H
