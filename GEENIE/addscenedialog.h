#ifndef ADDSCENEDIALOG_H
#define ADDSCENEDIALOG_H

#include <QDialog>

namespace Ui {
class AddSceneDialog;
}

/*!
 * \class AddSceneDialog addscenedialog.h
 * \brief The AddSceneDialog class
 */

class AddSceneDialog : public QDialog
{
    Q_OBJECT

public:

    //! Constructor.
    /*!
     * \param parent Needs the parent-widget.
     */
    explicit AddSceneDialog(QWidget *parent = 0);

    //! Deconstructor.
    /*!
     * Deletes the dialog.
     */
    ~AddSceneDialog();

    //!Get actual name of the scene.
    /*!
     * \return _name Returns the name in a QString.
     */
    QString name(){return _name;}

private slots:

    //! Slot for the create-button.
    /*!
     * If the entered name of the new scene is valid, it will be created, otherwise the creation will be canceled.
     */
    void on_pushButton_clicked();

    //! Slot for the cancel-button.
    /*!
      The dialog will be canceled.
     */
    void on_pushButton_2_clicked();

private:
    //! Private scene name.
    /*!
     * Stores the value of the actual scene name. Is private.
     */
    QString _name;

    //! UI variable.
    /*!
      Stores the actual ui in a private variable.
     */
    Ui::AddSceneDialog *ui;
};

#endif // ADDSCENEDIALOG_H
