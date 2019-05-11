#ifndef CHECKBOXLIST_H
#define CHECKBOXLIST_H

#include <QAbstractListModel>

class CheckBoxList : public QAbstractListModel
{
    Q_OBJECT

    //NOTA IMPORTANTE: Esto deberia funciona pero hay un bug en Linux.
    //Check Box in QComboBox is not drawn in case of "Fusion" Style
    //https://bugreports.qt.io/browse/QTBUG-60310
public:
    //constructor
    explicit CheckBoxList(QStringList *itemList, QObject *parent = Q_NULLPTR);
    ~CheckBoxList() override = default;
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    QStringList m_itemList;
};

#endif // CHECKBOXLIST_H
