#ifndef CONFIGGUSANOS_H
#define CONFIGGUSANOS_H
#include "registro.h"
#include <QDialog>

#define VIDA_DEFAULT 100

namespace Ui {
class ConfigGusanos;
}

class ConfigGusanos : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigGusanos(Registro &registro, QWidget *parent = 0);
    ~ConfigGusanos();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ConfigGusanos *ui;
    Registro& registro;
};

#endif // CONFIGGUSANOS_H
