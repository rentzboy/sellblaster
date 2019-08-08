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
    Q_PROPERTY(QStringList formatoList MEMBER formatoList NOTIFY formatoListChanged)
    Q_PROPERTY(QStringList idBobinaList MEMBER idBobinaList NOTIFY idBobinaListChanged)
    Q_PROPERTY(QVector <bool> checkedValue MEMBER checkedValue NOTIFY checkedValueChanged)
    //Q_PROPERTY(QVariantMap toogleValue MEMBER toogleValue NOTIFY toogleValueChanged) => no he sabido

public:
    AddSupplier(const AddSupplier &other) = delete;
    AddSupplier operator=(const AddSupplier &other) = delete;
    ~AddSupplier();
    static void createComponent(void);
    Q_INVOKABLE void textValueToBackEnd(QString fieldName, QString text);
    Q_INVOKABLE void textListToBackEnd(QString fieldName, QString text, bool value);
    void uncheckAllValues(QString comboBox);
    Q_INVOKABLE void toogleAllValues(QString comboBox);
    Q_INVOKABLE void fillComboBoxesFromDb(QString tab);
    void fillRelatedComboBoxFromDb(QString comboBox);
    void fillRelatedComboCheckBoxFromDb(QString comboBox);
public slots:
    bool onAceptarButton(QString tab);
    void onCancelarButton(void);
    void onGuardarButton(QString tab);
    void onRelatedFieldUpdated(QString fieldName);
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
    QVariantMap toogleValue = {{"serie", true}, {"aleacion", true}, {"temple", true}, {"acabado", true},
                                                    {"anchoBobina", true}, {"diametroIntBobina", true}, {"formatoChapa", true}}; //NO se utiliza
    //Lo hago con el vector pues con QVariantMap no me aclaro como utilizarlo en QML
    QVector <bool> checkedValue = {false, false, false, false, false, false, false}; //[0] = serie, [1]=aleación, ....tal como en toogleValue

    QStringList paisList;
    QStringList actividadList;
    QStringList formaPagoList;
    QStringList areaList;
    QStringList puestoList;
    QStringList tipoList; //bobina, chapa, plancha, tubo, ....
    QStringList materialList; //aluminio, inox, titanio, ....
    QStringList serieList;
    QStringList serieListCompleta;
    QStringList serieIndexList;
    QStringList serieSelectionList;
    QStringList aleacionList;
    QStringList aleacionListCompleta;
    QStringList aleacionSelectionList;
    QStringList templeList;
    QStringList templeListCompleta;
    QStringList templeSelectionList;
    QStringList acabadoList;
    QStringList acabadoListCompleta;
    QStringList acabadoSelectionList;
    QStringList formatoList; //Formatos chapas/planchas y anchos bobinas
    QStringList formatoListCompleta;
    QStringList formatoChapaSelectionList;
    QStringList formatoBobinaSelectionList;
    QStringList idBobinaList;
    QStringList idBobinaSelectionList;
    QString aleacionRadioButton = "aisi"; //valor inicial

    QMap <QString, QString> formField;
    QErrorMessage *errorMessage = Q_NULLPTR;

signals:
    void closeQmlInstance(void);
    void clearFormFields(QVariant tab);
    void clearFormFields(QString tab);
    //Notify signals
    void relatedFieldUpdated(QString fieldName);
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
    void formatoListChanged(void);
    void idBobinaListChanged(void);
    void checkedValueChanged(void);
    //void toogleValueChanged(void);
};

#endif // ADDSUPPLIER_H
