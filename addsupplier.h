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
    Q_PROPERTY(QStringList actividadList MEMBER actividadList NOTIFY actividadListChanged)
    Q_PROPERTY(QStringList paisList MEMBER paisList NOTIFY paisListChanged)
    Q_PROPERTY(QStringList formaPagoList MEMBER formaPagoList NOTIFY formaPagoListChanged)
    ///////////////////////CONTACTOS////////////////////////////////////
    Q_PROPERTY(QStringList areaList MEMBER areaList NOTIFY areaListChanged)
    Q_PROPERTY(QStringList puestoList MEMBER puestoList NOTIFY puestoListChanged)
    ///////////////////////PRODUCTOS////////////////////////////////////
    Q_PROPERTY(QStringList tipoList MEMBER tipoList NOTIFY tipoListChanged)
    Q_PROPERTY(QStringList materialList MEMBER materialList NOTIFY materialListChanged)
    Q_PROPERTY(QStringList serieList MEMBER serieList NOTIFY serieListChanged)
    Q_PROPERTY(QStringList aleacionList MEMBER aleacionList NOTIFY aleacionListChanged)
    Q_PROPERTY(QStringList templeList MEMBER templeList NOTIFY templeListChanged)
    Q_PROPERTY(QStringList acabadoList MEMBER acabadoList NOTIFY acabadoListChanged)

public:
    AddSupplier(const AddSupplier &other) = delete;
    AddSupplier operator=(const AddSupplier &other) = delete;
    ~AddSupplier();
    static void createComponent(void);
    Q_INVOKABLE void textValueToBackEnd(QString key, QString value);
    Q_INVOKABLE void fillComboBoxesFromDb(QString tab);
    Q_INVOKABLE void fillDependentComboBoxFromDb(QString comboBox, QString value);
public slots:
    bool onAceptarButton(QString tab);
    void onCancelarButton(void);
    void onGuardarButton(QString tab);
    void onFormFieldUpdated(QString field, QString value);
    //////////////////////////////////////////////////////////////////////////////////////////////////////

private:
    explicit AddSupplier(QObject *parent = Q_NULLPTR); //Private construstror (Singleton class)
    static void registerSingleton(void);
    //Members
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
    QStringList tipoList;
    QStringList materialList;
    QStringList serieList;
    QStringList serieListFija;
    QStringList aleacionList;
    QStringList templeList;
    QStringList acabadoList;

    QMap <QString, QString> formField;
    QErrorMessage *errorMessage = Q_NULLPTR;

    QStandardItemModel *modelo = Q_NULLPTR;
    QStandardItem *iItem1 = Q_NULLPTR;
    QStandardItem *iItem2 = Q_NULLPTR;

signals:
    void closeQmlInstance(void);
    void clearFormFields(QVariant tab);
    void clearFormFields(QString tab);
    //Notify signals
    void formFieldUpdated(QString field, QString value);
    void actividadListChanged(void);
    void paisListChanged(void);
    void formaPagoListChanged(void);
    void areaListChanged(void);
    void puestoListChanged(void);
    void tipoListChanged(void);
    void materialListChanged(void);
    void serieListChanged(void);
    void aleacionListChanged(void);
    void templeListChanged(void);
    void acabadoListChanged(void);
};

#endif // ADDSUPPLIER_H
