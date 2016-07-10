#ifndef ADDENTITYDIALOG_H
#define ADDENTITYDIALOG_H

#include <QDialog>

namespace Ui {
class AddEntityDialog;
}

/*!
 * \class AddEntityDialog addentitydialog.h
 * \brief The AddEntityDialog class
 */

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

    //! Get entity-name.
    /*!
     * \return A QString of the current entity-name.
     */
    QString name(){return _name;}

private slots:
    //! Slot for the create-button.
    /*!
      If the selected name of the new entity is not empty, it will be created.
     */
    void on_pushButton_clicked();

    //! Slot for the cancel-button.
    /*!
      Will be called when the cancel-button is clicked. Aborts the creation of a new entity.
     */
    void on_pushButton_2_clicked();

private:
    //! Name variable.
    /*!
      Stores the private name of the entity. Is a QString.
     */
    QString _name;

    //! UI variable.
    /*!
      Stores the AddEntityDialog ui. Is private.
     */
    Ui::AddEntityDialog *ui;
};

#endif // ADDENTITYDIALOG_H
