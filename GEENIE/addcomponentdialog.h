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
    void SetAssetList(QList<ASSET_DATA>);
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

    void on_comboBox_currentIndexChanged(const QString &arg1);

signals:
    void LoadAssetList(AddComponentDialog* ,int);
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
