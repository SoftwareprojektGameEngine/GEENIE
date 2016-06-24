#ifndef RENAMEENTITYDIALOG_H
#define RENAMEENTITYDIALOG_H

#include <QDialog>

namespace Ui {
class RenameEntityDialog;
}

/*!
 * \class RenameEntityDialog renameentitydialog.h
 * \brief The RenameEntityDialog class.
 */

class RenameEntityDialog : public QDialog
{
    Q_OBJECT

public:

    //! Constructor.
    /*!
     * Creates the dialog for renaming an entity.
     * \param parent The parent widget.
     * \param name The new name.
     */

    explicit RenameEntityDialog(QWidget *parent = 0, QString name = QString());

    //! Destructor.
    /*!
     * Removes the dialog.
     */

    ~RenameEntityDialog();

    //! Returns the name.

    QString name();

private slots:

    //! Slot for the accept-button.
    /*!
     * If the new name is not empty, it will be assigned.
     */

    void on_pushButton_clicked();

    //! Slot for the cancel-button.
    /*!
     * Cancels the dialog.
     */

    void on_pushButton_2_clicked();

private:

    //! Private variable stores the name.

    QString _name;

    //! Private variable stores the dialog ui.

    Ui::RenameEntityDialog *ui;
};

#endif // RENAMEENTITYDIALOG_H
