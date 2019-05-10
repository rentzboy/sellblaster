#ifndef SQLITEMODEL_H
#define SQLITEMODEL_H

#include <QWidget>
#include <QAbstractTableModel>
#include <QStyleOptionViewItem>

class QSqlTableModel;

class sqliteModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    //constructors
    explicit sqliteModel(QObject *parent = Q_NULLPTR, QSqlTableModel *model= Q_NULLPTR);
    ~sqliteModel() override = default;
    //members to reimplement
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
    //Adaptator: permite customizar la salida de datos en el TableView sin almacenar nada
    //pues los datos están en el modelo original (aqui solo se guarda un puntero del modelo de datos)
    //Siempre es mejor hacer los cambios en un adaptador (child-theme en wp) que sobre el modelo original
    QSqlTableModel *adaptor = Q_NULLPTR;
};

#endif // SQLITEMODEL_H
