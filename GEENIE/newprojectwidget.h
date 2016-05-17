#ifndef NEWPROJECTWIDGET_H
#define NEWPROJECTWIDGET_H

#include <QWidget>

namespace Ui {
class NewProjectWidget;
}

class NewProjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NewProjectWidget(QWidget *parent = 0);
    ~NewProjectWidget();

private:
    Ui::NewProjectWidget *ui;
};

#endif // NEWPROJECTWIDGET_H
