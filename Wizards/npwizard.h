#ifndef NPWIZARD_H
#define NPWIZARD_H

#include <QMainWindow>

namespace Ui {
class NPWizard;
}

class NPWizard : public QMainWindow
{
    Q_OBJECT

public:
    explicit NPWizard(QWidget *parent = 0);
    ~NPWizard();

private:
    Ui::NPWizard *ui;
};

#endif // NPWIZARD_H
