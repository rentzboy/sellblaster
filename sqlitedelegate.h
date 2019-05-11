#ifndef SQLITEDELEGATE_H
#define SQLITEDELEGATE_H

#include <QModelIndex>
#include <QPixmap>
#include <QSize>
#include <QStyledItemDelegate>
#include <QItemSelectionModel>

QT_FORWARD_DECLARE_CLASS(QPainter)

class SqliteDelegate : public QStyledItemDelegate
{
public:
    explicit SqliteDelegate(QObject *parent);
    ~SqliteDelegate() override = default;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) override;

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
};

#endif // SQLITEDELEGATE_H
