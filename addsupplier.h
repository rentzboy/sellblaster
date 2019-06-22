#ifndef ADDSUPPLIER_H
#define ADDSUPPLIER_H

#include <QObject>
#include <QAbstractButton>
#include <QErrorMessage>
#include <QMap>
#include <QStandardItemModel>
#include <QQuickView>
#include <QQmlApplicationEngine>

class AddSupplier : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("name", "newSupplierObject")
    ///////////////////////EMPRESA////////////////////////////////////
    Q_PROPERTY(QStringList actividadList MEMBER actividadList)
    Q_PROPERTY(QStringList paisList MEMBER paisList)
    Q_PROPERTY(QStringList formaPagoList MEMBER formaPagoList)
    ///////////////////////CONTACTOS////////////////////////////////////
    Q_PROPERTY(QStringList areaList MEMBER areaList)
    Q_PROPERTY(QStringList puestoList MEMBER puestoList)

public:
    AddSupplier(const AddSupplier &other) = delete;
    AddSupplier operator=(const AddSupplier &other) = delete;
    ~AddSupplier() = default;
    static void createComponent(void);
    Q_INVOKABLE void textValueToBackEnd(QString key, QString value);

public slots:
    void onAceptarButton(QString tab);
    void onCancelarButton(QString tab);
    void onGuardarButton(QString tab);
    //////////////////////////////////////////////////////////////////////////////////////////////////////

private:
    explicit AddSupplier(QObject *parent = Q_NULLPTR); //Private construstror (Singleton class)
    static void registerSingleton(void);
    //Members
    void fillComboBoxWithCheckBoxFromDb(void);
    void fillComboBoxesFromDb(void);
    bool sanitationCheck(QString tab);
    void resetFields(QString tab);
    //Attributes
    static QQmlApplicationEngine *engine;
    static AddSupplier *uniqueInstance;
    static int typeId;
    QStringList paisList;
    QStringList actividadList;
    QStringList formaPagoList;
    QStringList areaList;
    QStringList puestoList;

    QMap <QString, QString> formField;
    QErrorMessage *errorMessage = Q_NULLPTR;

    QStandardItemModel *modelo = Q_NULLPTR;
    QStandardItem *iItem1 = Q_NULLPTR;
    QStandardItem *iItem2 = Q_NULLPTR;

signals:
    void closeQmlInstance(void);
    void clearFormFields(QVariant tab);
};

#endif // ADDSUPPLIER_H
