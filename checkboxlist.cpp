#include "checkboxlist.h"
#include <QColor>
#include <QBrush>

//CONSTRUCTOR
checkBoxList::checkBoxList(QStringList *itemList, QObject *parent) : QAbstractListModel(parent), m_itemList(*itemList)  {}

//PUBLIC MEMBERS
int checkBoxList::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_itemList.count();
}
QVariant checkBoxList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return m_itemList.value(index.row());
    case Qt::CheckStateRole:
        return Qt::Checked; //actualizarlo junto a setData()
    case Qt::ToolTipRole:
        return "Esto no funciona";
    case Qt::BackgroundRole:
        return QBrush(QColor(255, 0, 0, 127), Qt::SolidPattern);
    default:
        return QVariant();
    }
}
bool checkBoxList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //PENDING -está tal como se crea en la template de Qt-
    if (data(index, role) != value)
    {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}
Qt::ItemFlags checkBoxList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}
