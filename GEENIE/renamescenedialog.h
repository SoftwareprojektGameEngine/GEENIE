#ifndef RENAMESCENEDIALOG_H
#define RENAMESCENEDIALOG_H

#include <QDialog>

namespace Ui {
class RenameSceneDialog;
}

/*!
 * \class RenameSceneDialog renamescenedialog.h
 * \brief The RenameSceneDialog class.
 */

class RenameSceneDialog : public QDialog
{
    Q_OBJECT

public:

    //! Constructor.
    /*!
     * Creates a new dialog for renaming the current scene.
     * \param parent The parent widget.
     * \param name The new name.
     */

    explicit RenameSceneDialog(QWidget *parent = 0, QString name = QString());

    //! Destructor.
    /*!
     * Destroys the dialog.
     */

    ~RenameSceneDialog();

    //! Returns the name of the scene.

    QString name();

private slots:

    //! Slot for the accept-button.
    /*!
     * If the new name of the scene is not empty, it will be assigned.
     */

    void on_pushButton_clicked();

    //! Slot for the cancel-button.
    /*!
     * Cancels the dialog.
     */

    void on_pushButton_2_clicked();

private:

    //! Private variable stores the new name of the scene.

    QString _name;

    //! Private variable stores the dialog ui.

    Ui::RenameSceneDialog *ui;
};

#endif // RENAMESCENEDIALOG_H
