#include <QCheckBox>
#include <QDebug>
#include <QSqlTableModel>
#include <QCheckBox>
#include "sqlitemodel.h"

//CONSTRUCTORS
sqliteModel::sqliteModel(QObject *parent, QSqlTableModel *model): QAbstractTableModel(parent), adaptor(model) {}

//MEMBER FUNCTIONS
int sqliteModel::rowCount(const QModelIndex &parent) const
{
    //Una tabla solo tiene que devolver elementos cuando parent is NOT valid (parent = root)
    if (parent.isValid())
        return 0;
    else return adaptor->rowCount();
}
int sqliteModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    else return adaptor->columnCount();
}
QVariant sqliteModel::data(const QModelIndex &index, int role) const
{
    //se llama una vez para cada uno de los 15 roles de cada ModelIndex
    //para recuperar los valores de todos los roles de cada celda
    int column = index.column();

    switch (role) {
        case Qt::DisplayRole:
            if(column == 1) return QVariant(); //Return an invalid QVariant instead of returning 0 when there's nothing to return
            break;
        case Qt::DecorationRole:
            break;
        case Qt::CheckStateRole:
            if(column == 1)
            {
                if(adaptor->data(index, Qt::DisplayRole).toInt() == 0)
                    return Qt::Unchecked;
                else return Qt::Checked;
            }
          break;
    case Qt::TextAlignmentRole:
        if (column == 1)
            return Qt::AlignRight + Qt::AlignVCenter;
        break;
    }
    return adaptor->data(index, role); //for all the rest not defined (not return) in the switch/case
}
bool sqliteModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    /* Used to modify the item of data associated with a specified model index. To be able to accept user input, provided by user interface elements, this function must handle data associated with Qt::EditRole. The implementation may also accept data associated with many different kinds of roles specified by Qt::ItemDataRole. After changing the item of data, models must emit the dataChanged() signal to inform other components of the change.*/

    //IMPORTANTE: NO HE COMPROBADO QUE ESTÉ BIEN Y FUNCIONE

    int column = index.column();

    if(column == 1)
    {
        if (role == Qt::CheckStateRole)
        {
            if(index.data(Qt::CheckStateRole) == Qt::Checked)
           {
               //user has checked item
               this->setData(index, 1, role);
               emit dataChanged(index,index);
               return true;
           }
           else
           {
                //user has unchecked item
                this->setData(index, 0, role);
                emit dataChanged(index,index);
                return true;
           }
        }
        return false; // ??
    }
    this->setData(index, value, role); //default implementation
    return true;
}
Qt::ItemFlags sqliteModel::flags(const QModelIndex &index) const
{
    //Must return an appropriate combination of flags for each item.
     Qt::ItemFlags flags = adaptor->flags(index);
     int column = index.column();
    if (column == 1)
        return flags |= Qt::ItemIsUserCheckable; //NOT Qt::ItemIsSelectable | Qt::ItemIsEditable
    else return flags |= Qt::ItemIsEnabled;
    //else return adaptor->flags(index);
}
