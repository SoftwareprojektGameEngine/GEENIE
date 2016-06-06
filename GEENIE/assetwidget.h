#ifndef ASSETWIDGET_H
#define ASSETWIDGET_H

#include <QWidget>

namespace Ui {
class AssetWidget;
}

#include "assets.h"

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

    void clear();
    void AddAsset(Asset* asset);

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

signals:
    void DeleteAsset(QUuid id);
    void AddAssetToProject(QString, AssetType);
};

#endif // ASSETWINDOW_H
