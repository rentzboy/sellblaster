#ifndef SQLITEDELEGATE_H
#define SQLITEDELEGATE_H

#include <QModelIndex>
#include <QPixmap>
#include <QSize>
#include <QStyledItemDelegate>

QT_FORWARD_DECLARE_CLASS(QPainter)

class checkBoxDelegate : public QStyledItemDelegate
{
public:
    explicit checkBoxDelegate(QObject *parent);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

private:
    QPixmap star;
};

#endif // SQLITEDELEGATE_H
