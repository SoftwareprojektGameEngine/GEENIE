#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class NewProjectDialog;
}

/*!
 * \class NewProjectDialog newprojectdialog.h
 * \brief The NewProjectDialog class.
 */

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:

    //! Constructor.
    /*!
      Creates the new-project dialog.
     * \param parent The parent widget.
     */

    explicit NewProjectDialog(QWidget *parent = 0);

    //! Deconstructor.
    /*!
     * Destroys the dialog ui.
     */

    ~NewProjectDialog();

    //! Returns the name of the current project.

    QString name(){return _name;}

    //! Returns the GEENIE-project file.

    QString file(){return _file;}

private slots:

    //! Slot for the getpath-button.
    /*!
     * Gets the path for the selected project and shows it on a lineedit.
     */

    void on_pushButton_clicked();

    //! Slot for the create-button.
    /*!
     * If all is correct the project will be saved in the selected path.
     */

    void on_pushButton_2_clicked();

    //! Slot for the cancel-button.
    /*!
     * Cancels the dialog.
     */

    void on_pushButton_3_clicked();

private:

    //! Private variable stores the name of the project.

    QString _name;

    //! Private variable stores the location of the GEENIE project file.

    QString _file;

    //! Private variable stores the dialog ui.

    Ui::NewProjectDialog *ui;
};

#endif // NEWPROJECTDIALOG_H
