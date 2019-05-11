#include "sqlitedelegate.h"
#include <QtWidgets>
#include "mapperdbmanagement.h"
#include "databasemanagement.h"

//CONSTRUCTORS
SqliteDelegate::SqliteDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

//MEMBERS
void SqliteDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 0)
    {
        //Setting up checkbox's size and position
        QStyleOptionButton checkboxstyle;
        checkboxstyle.initFrom(option.widget); //good style practise

        //Returns the sub-area for the given Sub-Element as described in the provided style option.
        //The returned rectangle is defined in screen coordinates.
        QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &option);
        checkboxstyle.rect = option.rect;
        checkboxstyle.rect.setLeft(option.rect.x() + option.rect.width()/2 - checkbox_rect.width()/2);

        bool data = index.model()->data(index, Qt::DisplayRole).toBool();

        if(data)
            checkboxstyle.state = QStyle::State_On | QStyle::State_Enabled;
        else
            checkboxstyle.state = QStyle::State_Off | QStyle::State_Enabled;

        //Finally draw the checkbox
        QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkboxstyle, painter);
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
QSize SqliteDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index) + QSize(1, 1); //using standard implementation
}
bool SqliteDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                                                       const QModelIndex &index)
{
    //Esto es simplemente para eliminar el warning x no usar option
    QStyleOptionViewItem tmp;
    tmp.features = option.features;

     if (index.column() == 0)
     {
         if ((event->type() == QEvent::MouseButtonPress))
         {
             QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
             if(mouse_event->button() == Qt::LeftButton)
             {
                 bool checked = index.model()->data(index, Qt::DisplayRole).toBool();
                 return model->setData(index, !checked, Qt::EditRole);
             }
             else return false;
         }
         else return false;
     }
     else
     {
         if (event->type() == QEvent::MouseButtonDblClick)
         {
             int selectedRow = index.row();
             auto mapper = new MapperDbManagement(selectedRow, static_cast<DatabaseManagement*>(this->parent()));
             mapper->show();
             return true;
         }
         else return false;
     }
}
QWidget *SqliteDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::createEditor(parent, option, index); //using standard implementation
}
