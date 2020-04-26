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
    Q_PROPERTY(QVariantMap empresaTabField MEMBER empresaTabField NOTIFY empresaTabFieldChanged)
    Q_PROPERTY(QVariantMap contactoTabField MEMBER contactoTabField NOTIFY contactoTabFieldChanged)
    Q_PROPERTY(QVariantMap productoTabField MEMBER productoTabField NOTIFY productoTabFieldChanged)
    Q_PROPERTY(QVariantMap servicioTabField MEMBER servicioTabField NOTIFY servicioTabFieldChanged)
    Q_PROPERTY(QVariantMap toogleValue MEMBER toogleValue NOTIFY toogleValueChanged)

public:
    AddSupplier(const AddSupplier &other) = delete;
    AddSupplier operator=(const AddSupplier &other) = delete;
    ~AddSupplier();
    static AddSupplier* createComponent(void);

    Q_INVOKABLE void textValueToBackEnd(QString tab, QString fieldName, QString text);
    Q_INVOKABLE void textListToBackEnd(QString fieldName, QString text, bool value);
    Q_INVOKABLE void toogleAllValues(QString comboBox);
    Q_INVOKABLE void fillComboBoxesFromDb(QString tab);

public slots:
    bool onAceptarButton(QString tab);
    void onCancelarButton(void);
    void onGuardarButton(QString tab);
    void onRelatedFieldUpdated(QString fieldName);
    void deleteUniqueInstance(void);

private:
    explicit AddSupplier(QObject *parent = Q_NULLPTR); //Private construstror (Singleton class)
    static void registerSingleton(void);
    void fillRelatedComboBoxFromDb(QString comboBox);
    void fillRelatedComboCheckBoxFromDb(QString comboBox);
    void uncheckAllValues(QString comboBox);
    void clearSelectionList(QString comboBox);
    bool sanitationCheck(QString tab);
    void resetFields(QString tab);
    void resetComboBox(QString fieldName);
    //Getters & Setters
    void setEmpresaTabField(const QString key, const QString value);
    void setContactoTabField(const QString key, const QString value);
    void setProductoTabField(const QString key, const QString value);
    void setServicioTabField(const QString key, const QString value);
    //Attributes
    static QQmlApplicationEngine *engine;
    static AddSupplier *uniqueInstance;
    static int typeId;
    QVariantMap empresaTabField = {{"empresa", ""}, {"holding", ""}, {"web", ""}, {"panjiba", ""},
                           {"maps", ""}, {"ciudad", ""}, {"postcode", ""}, {"moq", ""}, {"notasEmpresa", ""},
                           {"pais", ""}, {"actividad", ""}, {"formaPago", ""}};
    QVariantMap contactoTabField = {{"nombre", ""}, {"apellido", ""},{"email", ""}, {"telefono", ""},
                           {"movil", ""}, {"notasContacto", ""}, {"area", ""}, {"puesto", ""}};
    QVariantMap productoTabField = {{"tipo", ""}, {"material", ""}, {"espesorMin", ""}, {"espesorMax", ""},
                           {"diametroMin", ""}, {"diametroMax", ""}, {"largoMin", ""}, {"largoMax", ""},
                           {"diametroIntMin", ""}, {"diametroIntMax", ""}, {"diametroExtMin", ""}, {"diametroExtMax", ""}};
    QVariantMap servicioTabField = {{"espesorMin1", ""}, {"espesorMax1", ""}, {"anchoMin1", ""}, {"anchoMax1", ""},
                           {"espesorMin2", ""}, {"espesorMax2", ""}, {"anchoMin2", ""}, {"anchoMax2", ""},
                           {"espesorMin3", ""}, {"espesorMax3", ""}, {"anchoMin3", ""}, {"anchoMax3", ""}, {"catalogo", ""}};
    QVariantMap toogleValue = {{"serie", false}, {"aleacion", false}, {"temple", false}, {"acabado", false},
                           {"anchoBobina", false}, {"diametroIntBobina", false}, {"formatoChapa", false}, {"servicios", false}};
    QMap<int, QVariant> paisList;
    QMap<int, QVariant> actividadList;
    QMap<int, QVariant> formaPagoList;
    QMap<int, QVariant> areaList;
    QMap<int, QVariant> puestoList;
    QMap<int, QVariant> tipoList;
    QMap<int, QVariant> materialList;
    QMap<int, QVariant> serieList;
    QStringList serieIndexList;
    QStringList serieSelectionList;
    QMap<int, QVariant> aleacionList;
    QMap<int, QVariant> aleacionListMaterial;
    QStringList aleacionSelectionList;
    QMap<int, QVariant> templeList;
    QStringList templeSelectionList;
    QMap<int, QVariant> acabadoList;
    QStringList acabadoSelectionList;
    QMap<int, QVariant> formatoList; //Compartido por los comboBoxes "Formato" (chapas/planchas) y "Ancho" (bobinas)
    QStringList formatoChapaSelectionList;
    QStringList formatoBobinaSelectionList;
    QMap<int, QVariant> idBobinaList;
    QStringList idBobinaSelectionList;
    QMap<int, QVariant> servicioList;
    QStringList servicioSelectionList;
    QString aleacionRadioButton = "Werkstoff"; //valor inicial
    QErrorMessage *errorMessage = Q_NULLPTR;

signals:
    //Connect signals
    void closingQmlInstance(void);
    void relatedFieldUpdated(QString fieldName);
    //Notify signals
    void toogleValueChanged(void);
    void empresaTabFieldChanged(void);
    void contactoTabFieldChanged(void);
    void productoTabFieldChanged(void);
    void servicioTabFieldChanged(void);
};

#endif // ADDSUPPLIER_H
