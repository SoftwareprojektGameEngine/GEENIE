#ifndef LAYOUTFORM_H
#define LAYOUTFORM_H

#include <QWidget>

namespace Ui {
class LayoutForm;
}

class LayoutForm : public QWidget
{
    Q_OBJECT

public:
    explicit LayoutForm(QWidget *parent = 0);
    ~LayoutForm();

private:
    Ui::LayoutForm *ui;
};

#endif // LAYOUTFORM_H
