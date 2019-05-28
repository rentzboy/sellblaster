#ifndef ADDSUPPLIER_H
#define ADDSUPPLIER_H

#include <QObject>
#include <QAbstractButton>
#include <QErrorMessage>
#include <QMap>
#include <QStandardItemModel>

class AddSupplier : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString empresa MEMBER empresa NOTIFY empresaChanged)
    Q_PROPERTY(QString holding MEMBER holding NOTIFY holdingChanged)
    Q_PROPERTY(QString actividad MEMBER actividad NOTIFY actividadChanged)
    Q_PROPERTY(QString web MEMBER web NOTIFY webChanged)
    Q_PROPERTY(QString panjiba MEMBER panjiba NOTIFY panjibaChanged)
    Q_PROPERTY(QString maps MEMBER maps NOTIFY mapsChanged)
    Q_PROPERTY(QString pais MEMBER pais NOTIFY paisChanged)
    Q_PROPERTY(QString ciudad MEMBER ciudad NOTIFY ciudadChanged)
    Q_PROPERTY(QString postcode MEMBER postcode NOTIFY postcodeChanged)
    Q_PROPERTY(QString descripcion MEMBER descripcion NOTIFY descripcionChanged)
    Q_PROPERTY(QString notasEmpresa MEMBER notasEmpresa NOTIFY notasEmpresaChanged)
    Q_PROPERTY(QString formaPago MEMBER formaPago NOTIFY formaPagoChanged)
    ///////////////////////////////////////////////////////////
    Q_PROPERTY(QString nombre MEMBER nombre NOTIFY nombreChanged)
    Q_PROPERTY(QString apellido MEMBER apellido NOTIFY apellidoChanged)
    Q_PROPERTY(QString email MEMBER email NOTIFY emailChanged)
    Q_PROPERTY(QString telefono MEMBER telefono NOTIFY telefonoChanged)
    Q_PROPERTY(QString movil MEMBER movil NOTIFY movilChanged)
    Q_PROPERTY(QString notasContactos MEMBER notasContactos  NOTIFY notasContactosChanged)
    Q_PROPERTY(QString area MEMBER area NOTIFY areaChanged)
    Q_PROPERTY(QString pueto MEMBER puesto NOTIFY puestoChanged)

signals:
    void empresaChanged();
    void holdingChanged();
    void actividadChanged();
    void webChanged();
    void panjibaChanged();
    void mapsChanged();
    void paisChanged();
    void ciudadChanged();
    void postcodeChanged();
    void descripcionChanged();
    void notasEmpresaChanged();
    void formaPagoChanged();

    void nombreChanged();
    void apellidoChanged();
    void emailChanged();
    void telefonoChanged();
    void movilChanged();
    void notasContactosChanged();
    void areaChanged();
    void puestoChanged();

public:
    AddSupplier(const AddSupplier &other) = delete;
    AddSupplier operator=(const AddSupplier &other) = delete;
    ~AddSupplier() = default;
    static void createComponent(void);

public slots:
    void onEmpresaButtonAceptarClicked(void);
    void onEmpresaButtonCancelarClicked(void);
    void onEmpresaButtonGuardarClicked(void);

private:
    explicit AddSupplier(QObject *parent = Q_NULLPTR); //Private construstror (Singleton class)
    static void registerSingleton(void);
    //Members
    void fillComboBoxWithCheckBoxFromDb(void);
    void fillComboBoxesFromDb(void);
    bool sanitationCheck(QString tag);
    void empresaApplyButton(void);
    void contactoApplyButton(void);
    //Attributes
    static AddSupplier *uniqueInstance;
    static int typeId;
    //Empresa
    QString empresa;
    QString holding;
    QString actividad;
    QString web;
    QString panjiba;
    QString maps;
    QString pais;
    QString ciudad;
    QString postcode;
    QString descripcion;
    QString notasEmpresa;
    QString formaPago;
    int moq;
    //Contactos
    QString nombre;
    QString apellido;
    QString email;
    QString telefono;
    QString movil;
    QString notasContactos;
    QString area;
    QString puesto;

    QMap <QString, QString> userDataFields;
    QErrorMessage *errorMessage = Q_NULLPTR;

    QStandardItemModel *modelo = Q_NULLPTR;
    QStandardItem *iItem1 = Q_NULLPTR;
    QStandardItem *iItem2 = Q_NULLPTR;
};

#endif // ADDSUPPLIER_H
