#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>

namespace Ui {
class NewDialog;
}

/*!
 * \class NewDialog newdialog.h
 * \brief The NewDialog class. Is for the new-button in the toolbar.
 */

class NewDialog : public QDialog
{
    Q_OBJECT

public:

    //! Constructor.
    /*!
     * Creates a new dialog.
     * \param parent The parent widget.
     * \param projectConfigured Is the project empty or does it have a scene (is configured)?
     */

    explicit NewDialog(QWidget *parent = 0, bool projectConfigured = false);

    //! Deconstructor.
    /*!
     * Deletes the dialog.
     */

    ~NewDialog();

    //! Is used as an intermediate variable.

    bool type(){return _type;}

private slots:

    //! Slot for the next-button.
    /*!
     * The user can create a new scene or a new project.
     */

    void on_pushButton_clicked();

    //! Slot for the cancel-button.
    /*!
     * Cancels the creation.
     */

    void on_pushButton_2_clicked();

private:

    //! Private variable that stores the newdialog ui.

    Ui::NewDialog *ui;

    //! Private intermediate variable.

    bool _type;
};

#endif // NEWDIALOG_H
