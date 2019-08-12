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
    Q_PROPERTY(QVariantMap empresaTabField MEMBER empresaTabField NOTIFY empresaTabFieldChanged)
    Q_PROPERTY(QStringList actividadList MEMBER actividadList NOTIFY actividadListChanged)
    Q_PROPERTY(QStringList paisList MEMBER paisList NOTIFY paisListChanged)
    Q_PROPERTY(QStringList formaPagoList MEMBER formaPagoList NOTIFY formaPagoListChanged)
    ///////////////////////CONTACTOS////////////////////////////////////
    Q_PROPERTY(QVariantMap contactoTabField MEMBER contactoTabField NOTIFY contactoTabFieldChanged)
    Q_PROPERTY(QStringList areaList MEMBER areaList NOTIFY areaListChanged)
    Q_PROPERTY(QStringList puestoList MEMBER puestoList NOTIFY puestoListChanged)
    ///////////////////////PRODUCTOS////////////////////////////////////
    Q_PROPERTY(QVariantMap productoTabField MEMBER productoTabField NOTIFY productoTabFieldChanged)
    Q_PROPERTY(QStringList tipoList MEMBER tipoList NOTIFY tipoListChanged)
    Q_PROPERTY(QStringList materialList MEMBER materialList NOTIFY materialListChanged)
    Q_PROPERTY(QStringList serieList MEMBER serieList NOTIFY serieListChanged)
    Q_PROPERTY(QStringList aleacionList MEMBER aleacionList NOTIFY aleacionListChanged)
    Q_PROPERTY(QStringList templeList MEMBER templeList NOTIFY templeListChanged)
    Q_PROPERTY(QStringList acabadoList MEMBER acabadoList NOTIFY acabadoListChanged)
    Q_PROPERTY(QStringList formatoList MEMBER formatoList NOTIFY formatoListChanged)
    Q_PROPERTY(QStringList idBobinaList MEMBER idBobinaList NOTIFY idBobinaListChanged)
    Q_PROPERTY(QVariantMap toogleValue MEMBER toogleValue NOTIFY toogleValueChanged)

public:
    AddSupplier(const AddSupplier &other) = delete;
    AddSupplier operator=(const AddSupplier &other) = delete;
    ~AddSupplier();
    static void createComponent(void);

    Q_INVOKABLE void textValueToBackEnd(QString tab, QString fieldName, QString text);
    Q_INVOKABLE void textListToBackEnd(QString fieldName, QString text, bool value);
    void uncheckAllValues(QString comboBox);
    Q_INVOKABLE void toogleAllValues(QString comboBox);
    Q_INVOKABLE void fillComboBoxesFromDb(QString tab);
    void fillRelatedComboBoxFromDb(QString comboBox);
    void fillRelatedComboCheckBoxFromDb(QString comboBox);

    void setEmpresaTabField(const QString key, const QString value);
    void setContactoTabField(const QString key, const QString value);
    void setProductoTabField(const QString key, const QString value);

public slots:
    bool onAceptarButton(QString tab);
    void onCancelarButton(void);
    void onGuardarButton(QString tab);
    void onRelatedFieldUpdated(QString fieldName);
    void onCloseQmlInstance(void);
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
    QMap <QString, QVariant> empresaTabField = {{"empresa", ""}, {"holding", ""}, {"web", ""}, {"panjiba", ""},
                                                 {"maps", ""}, {"ciudad", ""}, {"postcode", ""}, {"moq", ""}, {"notasEmpresa", ""},
                                                 {"pais", "España"}, {"actividad", ""}, {"formaPago", ""}};
    QMap <QString, QVariant> contactoTabField = {{"nombre", ""}, {"apellido", ""},{"email", ""}, {"telefono", ""},
                                                 {"movil", ""}, {"notasContacto", ""}, {"area", ""}, {"puesto", ""}};
    QMap <QString, QVariant> productoTabField = {{"tipo", ""}, {"material", ""}, {"espesorMin", ""}, {"espesorMax", ""},
                                                 {"diametroMin", ""}, {"diametroMax", ""}, {"largoMin", ""}, {"largoMax", ""},
                                                 {"diametroIntMin", ""}, {"diametroIntMax", ""}, {"diametroExtMin", ""}, {"diametroExtMax", ""}};
    QVariantMap toogleValue = {{"serie", false}, {"aleacion", false}, {"temple", false}, {"acabado", false},
                                                    {"anchoBobina", false}, {"diametroIntBobina", false}, {"formatoChapa", false}};
    QStringList paisList;
    QStringList actividadList;
    QStringList formaPagoList;
    QStringList areaList;
    QStringList puestoList;
    QStringList tipoList;
    QStringList materialList;
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
    QStringList formatoList; //Compartido por los comboBoxes "Formato" (chapas/planchas) y "Ancho" (bobinas)
    QStringList formatoListCompleta;
    QStringList formatoChapaSelectionList;
    QStringList formatoBobinaSelectionList;
    QStringList idBobinaList;
    QStringList idBobinaSelectionList;
    QString aleacionRadioButton = "aisi"; //valor inicial
    QErrorMessage *errorMessage = Q_NULLPTR;

signals:
    //Connect signals
    void closeQmlInstance(void);
    void relatedFieldUpdated(QString fieldName);
    //Notify signals
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
    void toogleValueChanged(void);
    void empresaTabFieldChanged(void);
    void contactoTabFieldChanged(void);
    void productoTabFieldChanged(void);
};

#endif // ADDSUPPLIER_H
