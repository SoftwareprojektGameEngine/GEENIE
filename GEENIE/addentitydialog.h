#ifndef ADDENTITYDIALOG_H
#define ADDENTITYDIALOG_H

#include <QDialog>

namespace Ui {
class AddEntityDialog;
}

class AddEntityDialog : public QDialog
{
    Q_OBJECT

public:
    //! Constructor.
    /*!
      \param parent The parent widget.
     */
    explicit AddEntityDialog(QWidget *parent = 0);
    //! Deconstructor.
    /*!
     * The dialog is deleted here.
     */
    ~AddEntityDialog();

    //! Get Entity-Name.
    /*!
     * \return A QString of the current Entity-Name.
     */
    QString name(){return _name;}

private slots:
    //! Slot for the Create-Button.
    /*!
      If the selected Name of the new Entity is not empty, it will be created.
     */
    void on_pushButton_clicked();

    //! Slot for the Cancel-Button.
    /*!
      Will be called when the Cancel-Button is clicked. Aborts the Creation of a new Entity.
     */
    void on_pushButton_2_clicked();

private:
    //! Name Variable.
    /*!
      Stores the private Name of the Entity. Is a QString.
     */
    QString _name;

    //! UI Variable.
    /*!
      Stores the AddEntityDialog UI. Is Private.
     */
    Ui::AddEntityDialog *ui;
};

#endif // ADDENTITYDIALOG_H
