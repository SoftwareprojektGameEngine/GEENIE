#ifndef ENTITIEVERVALTUNG_H
#define ENTITIEVERVALTUNG_H

#include <QWidget>

namespace Ui {
class Entitievervaltung;
}

class Entitievervaltung : public QWidget
{
    Q_OBJECT

public:
    explicit Entitievervaltung(QWidget *parent = 0);
    ~Entitievervaltung();

private:
    Ui::Entitievervaltung *ui;
};

#endif // ENTITIEVERVALTUNG_H
