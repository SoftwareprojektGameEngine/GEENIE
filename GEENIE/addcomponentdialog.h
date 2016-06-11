#ifndef ADDCOMPONENTDIALOG_H
#define ADDCOMPONENTDIALOG_H

#include <QDialog>


namespace Ui {
class AddComponentDialog;
}

class Component;

class AddComponentDialog : public QDialog
{
    Q_OBJECT

public:
    //! Constructor.
    /*!
      \param parent The parent widget.
     */
    explicit AddComponentDialog(QWidget *parent = 0);
    //! Deconstructor.
    /*!
     * The dialog is deleted here.
     */
    ~AddComponentDialog();

    //! Get component.
    /*!
     * \return Component.
     */
    Component* component();

private slots:
    //! Slot for the Create-Button.
    /*!
      A component for the actual Entity will be created.
     */
    void on_createBtn_clicked();

    //! Slot for the Cancel-Button.
    /*!
      Cancels assigning a Component to the selected Entity.
     */
    void on_cancelBtn_clicked();

private:
    //! UI Variable.
    /*!
      Private Variable stores the AddComponentDialog-UI.
     */
    Ui::AddComponentDialog *ui;

    //! Component Variable.
    /*!
      Private Variable stores the actual Component.
     */
    Component* _component;
};

#endif // ADDCOMPONENTDIALOG_H
