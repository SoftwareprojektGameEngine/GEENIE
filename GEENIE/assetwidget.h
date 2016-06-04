#ifndef ASSETWIDGET_H
#define ASSETWIDGET_H

#include <QWidget>

namespace Ui {
class AssetWidget;
}

/*!
 * \class AssetWidget assetwidget.h
 * \brief The AssetWidget class
 */

class AssetWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \fn explicit AssetWidget(QWidget *parent)
     * \brief Constructor
     * \param parent
     */
    explicit AssetWidget(QWidget *parent = 0);
    /*!
     * \fn ~AssetWidget()
     * \brief Destructor
     */
    ~AssetWidget();

    /*!
     * \fn void FillTreeView(QString _path)
     * \brief Fills asset widget with information from path
     * \param _path
     */
    void FillTreeView(QString _path);

private slots:
    /*!
     * \fn void on_LoadButton_clicked()
     * \brief slot called when load button is clicked
     */
    void on_LoadButton_clicked();

    /*!
     * \fn void on_DeleteButton_clicked()
     * \brief slot called when delete button is clicked
     */
    void on_DeleteButton_clicked();

private:
    Ui::AssetWidget *ui;
};

#endif // ASSETWINDOW_H
