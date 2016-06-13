#ifndef ADDCOMPONENTDIALOG_H
#define ADDCOMPONENTDIALOG_H

#include <QDialog>
#include <QUuid>
struct ASSET_DATA
{
    QString name;
    QUuid id;
};

namespace Ui {
class AddComponentDialog;
}

class Component;

/*!
 * \class AddComponentDialog addcomponentdialog.h
 * \brief The AddComponentDialog class
 */

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
     * \return Component The actual Component.
     */
    Component* component();
    void SetAssetList(QList<ASSET_DATA>);
private slots:
    //! Slot for the create-button.
    /*!
      A component for the actual entity will be created.
     */
    void on_createBtn_clicked();

    //! Slot for the cancel-button.
    /*!
      Cancels assigning a component to the selected entity.
     */
    void on_cancelBtn_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

signals:
    void LoadAssetList(AddComponentDialog* ,int);
private:
    //! UI variable.
    /*!
      Private variable stores the AddComponentDialog-ui.
     */
    Ui::AddComponentDialog *ui;

    //! Component variable.
    /*!
      Private variable stores the actual component.
     */
    Component* _component;
};

#endif // ADDCOMPONENTDIALOG_H
