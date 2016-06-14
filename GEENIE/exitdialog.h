#ifndef EXITDIALOG_H
#define EXITDIALOG_H

#include <QDialog>

namespace Ui {
class ExitDialog;
}

/*!
 * \class ExitDialog exitdialog.h
 * \brief The ExitDialog class
 */

class ExitDialog : public QDialog
{
    Q_OBJECT

public:

    //! Constructor.
    /*!
     * Creates the ui.
     * \param parent The parent-widget.
     */
    explicit ExitDialog(QWidget *parent = 0);

    //! Deconstructor
    /*!
     * Deletes the ui.
     */
    ~ExitDialog();

private slots:

    //! Slot for the yes-button.
    /*!
     * Returns back to GEENIE.
     */

    void on_pushButton_clicked();

    //! Slot for the no-Button.
    /*!
     * Go back to windows.
     */

    void on_pushButton_2_clicked();

private:

    //! UI variable.
    /*!
     * Stores the actual ui in a private variable.
     */

    Ui::ExitDialog *ui;
};

#endif // EXITDIALOG_H
