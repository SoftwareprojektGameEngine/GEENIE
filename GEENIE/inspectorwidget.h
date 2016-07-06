#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H
#include "geenie.h"

#include <QWidget>

namespace Ui {
class InspectorWidget;
}

/*!
 * \brief The InspectorWidget class for displaying entity and component properties.
 */

class InspectorWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor
     * \param parent
     */
    explicit InspectorWidget(QWidget *parent = 0);
    ~InspectorWidget();
    /*!
     * \brief Fills the tree view recursively with data from an entity
     * \param entity
     * \param sub
     */
    void FillTree(Entity* entity, bool sub = false);

signals:
    /*!
     * \brief Signals if an entity was renamed
     * \param id
     * \param name
     */
    void RenameEntity(QUuid id, QString name);
    /*!
     * \brief Signals if an component was modified
     * \param id
     * \param parentId
     * \param component
     */
    void ModifyComponent(QUuid id, QUuid parentId, Component* component);

public slots:
    /*!
     * \brief Workaround for automatic size. Resizes the widget to the parameters
     * \param h
     * \param w
     */
    void resizeSlot(int h, int w);

private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

private:
    Ui::InspectorWidget *ui;
    QTreeWidget *t;
    void SetHeaderText(QString, QString);
    void InitializeTree();
    QTreeWidgetItem* VectorToItem(Vector v);
    QTreeWidgetItem* ColorToItem(Color c);
};

#endif // INSPECTORWIDGET_H

