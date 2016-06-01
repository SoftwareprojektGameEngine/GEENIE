#ifndef ENTITIEVERVALTUNG_H
#define ENTITIEVERVALTUNG_H

#include <QWidget>

namespace Ui {
class Entitievervaltung;
}

/*!
 * \class Entitievervaltung entitivervaltung.h
 * \brief The Entitievervaltung class
 */

class Entitievervaltung : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \fn explicit Entitievervaltung(QWidget* parent)
     * \brief Constructor
     * \param parent
     */
    explicit Entitievervaltung(QWidget *parent = 0);
    /*!
     * \fn ~Entitievervaltung();
     * \brief Destructor
     */
    ~Entitievervaltung();

private:
    Ui::Entitievervaltung *ui;
};

#endif // ENTITIEVERVALTUNG_H
