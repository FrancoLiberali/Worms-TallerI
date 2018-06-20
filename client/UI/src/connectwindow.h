#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H
#include "mapwindow.h"
#include <QDialog>

namespace Ui {
class connectWindow;
}

class connectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit connectWindow(QWidget *parent = 0);
    ~connectWindow();

private:
    Ui::connectWindow *ui;
    mapWindow *mapW;
};

#endif // CONNECTWINDOW_H
