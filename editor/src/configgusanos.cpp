#include "configgusanos.h"
#include "ui_configgusanos.h"

#define MIN_VIDA 0
#define MAX_VIDA 10000

ConfigGusanos::ConfigGusanos(Registro &registro, QWidget *parent) :
    ui(new Ui::ConfigGusanos), registro(registro), QDialog(parent)
{
    ui->setupUi(this);

    // Setear la vida default.
    ui->spinBox->setValue(VIDA_DEFAULT);
    // Setear rango de vida disponible.
    ui->spinBox->setRange(MIN_VIDA, MAX_VIDA);
}

ConfigGusanos::~ConfigGusanos()
{
    delete ui;
}

void ConfigGusanos::on_buttonBox_accepted()
{
    int vida = ui->spinBox->value();
    this->registro.set_vida_gusanos(vida);
    ui->spinBox->setValue(vida);
}

void ConfigGusanos::on_buttonBox_rejected()
{
    close();
}
