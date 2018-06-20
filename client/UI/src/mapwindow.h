#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QDialog>

namespace Ui {
class mapWindow;
}

class mapWindow : public QDialog
{
    Q_OBJECT

public:
    explicit mapWindow(QWidget *parent = 0);
    ~mapWindow();

private slots:
    void on_crearPartidaButton_clicked();

    void on_unirseButton_clicked();

private:
    Ui::mapWindow *ui;
};

#endif // MAPWINDOW_H
