#ifndef NAMEWINDOW_H
#define NAMEWINDOW_H
#include "connectwindow.h"
#include <QDialog>

namespace Ui {
class nameWindow;
}

class nameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit nameWindow(QWidget *parent = 0);
    ~nameWindow();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::nameWindow *ui;
    connectWindow *connectW;
};

#endif // NAMEWINDOW_H
