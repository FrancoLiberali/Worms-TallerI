#ifndef CONFIGARMAS_H
#define CONFIGARMAS_H

#include <QDialog>
#include "yamlparser.h"
#include "registro.h"

namespace Ui {
class ConfigArmas;
}

class ConfigArmas : public QDialog
{
    Q_OBJECT

public:
    // Ventana que configura las armas disponibles en el juego.
    explicit ConfigArmas(Registro& registro, QWidget *parent = 0);
    ~ConfigArmas();

private slots:
    // Habilita o deshabilita el arma.
    void on_checkBox_stateChanged(int arg1);
    // Modifica la municion del arma.
    void on_spinBox_valueChanged(const QString &arg1);
    // Selecciona un arma.
    // Actualiza sus caracteristicas.
    void on_comboBox_currentIndexChanged(const QString &arg1);
    // Guarda los cambios realizados.
    void on_buttonBox_accepted();
    // Cancela los cambios realizados.
    void on_buttonBox_rejected();

    void on_checkBox_2_stateChanged(int arg1);

private:
    Ui::ConfigArmas *ui;
    Registro& registro;
};

#endif // CONFIGARMAS_H
