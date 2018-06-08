#include "configarmas.h"
#include "ui_configarmas.h"
#include "yamlparser.h"

ConfigArmas::ConfigArmas(Registro &registro, QWidget *parent) :
    ui(new Ui::ConfigArmas), registro(registro), QDialog(parent)

{
    ui->setupUi(this);

    YAMLParser parser;
    parser.cargarConfig(registro);

    foreach(std::string arma, registro.get_armas()) {
        ui->comboBox->addItem(QString::fromStdString(arma));
    }
}

void ConfigArmas::on_checkBox_stateChanged(int state)
{
   std::string nombre = ui->comboBox->currentText().toStdString();
   if(state == 0){
       registro.get_arma(nombre)->set_deshabilitada();
   } else {
       registro.get_arma(nombre)->set_habilitada();
   }
}

void ConfigArmas::on_spinBox_valueChanged(const QString &string)
{
     std::string nombre = ui->comboBox->currentText().toStdString();
     registro.get_arma(nombre)->set_municion(string.toStdString());
}

void ConfigArmas::on_comboBox_currentIndexChanged(const QString &string)
{
    Arma* arma = registro.get_arma(string.toStdString());
    ui->checkBox->setChecked(arma->esta_habilitada());
    if (arma->get_municion() == "infinitas") {
        ui->checkBox_2->setChecked(true);
    } else {
        ui->checkBox_2->setChecked(false);
        ui->spinBox->setValue(std::stoi(arma->get_municion()));
    }
}

void ConfigArmas::on_buttonBox_accepted()
{
    this->close();
}

void ConfigArmas::on_buttonBox_rejected()
{
    this->close();
}

void ConfigArmas::on_checkBox_2_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->spinBox->setEnabled(true);
    } else {
        ui->spinBox->setEnabled(false);
        std::string nombre = ui->comboBox->currentText().toStdString();
        registro.get_arma(nombre)->set_municion("infinitas");
    }
}

ConfigArmas::~ConfigArmas()
{
    delete ui;
}
