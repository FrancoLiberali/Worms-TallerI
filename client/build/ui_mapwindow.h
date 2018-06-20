/********************************************************************************
** Form generated from reading UI file 'mapwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPWINDOW_H
#define UI_MAPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mapWindow
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QWidget *formLayoutWidget_3;
    QFormLayout *formLayout_4;
    QLabel *label_4;
    QLabel *label_5;
    QComboBox *cmb_jugadores;
    QComboBox *cmb_maps;
    QLabel *label_6;
    QLineEdit *lineNameRoom;
    QPushButton *btn_crear;
    QGroupBox *groupBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout_2;
    QLabel *label;
    QComboBox *cmb_salas;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_3;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *btn_unirse;

    void setupUi(QDialog *mapWindow)
    {
        if (mapWindow->objectName().isEmpty())
            mapWindow->setObjectName(QStringLiteral("mapWindow"));
        mapWindow->resize(522, 394);
        gridLayout = new QGridLayout(mapWindow);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_2 = new QGroupBox(mapWindow);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setFlat(false);
        formLayoutWidget_3 = new QWidget(groupBox_2);
        formLayoutWidget_3->setObjectName(QStringLiteral("formLayoutWidget_3"));
        formLayoutWidget_3->setGeometry(QRect(20, 30, 261, 131));
        formLayout_4 = new QFormLayout(formLayoutWidget_3);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        formLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(formLayoutWidget_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(formLayoutWidget_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_5);

        cmb_jugadores = new QComboBox(formLayoutWidget_3);
        cmb_jugadores->setObjectName(QStringLiteral("cmb_jugadores"));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, cmb_jugadores);

        cmb_maps = new QComboBox(formLayoutWidget_3);
        cmb_maps->setObjectName(QStringLiteral("cmb_maps"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, cmb_maps);

        label_6 = new QLabel(formLayoutWidget_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, label_6);

        lineNameRoom = new QLineEdit(formLayoutWidget_3);
        lineNameRoom->setObjectName(QStringLiteral("lineNameRoom"));

        formLayout_4->setWidget(2, QFormLayout::FieldRole, lineNameRoom);

        btn_crear = new QPushButton(groupBox_2);
        btn_crear->setObjectName(QStringLiteral("btn_crear"));
        btn_crear->setGeometry(QRect(320, 50, 121, 41));

        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox = new QGroupBox(mapWindow);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        formLayoutWidget = new QWidget(groupBox);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(20, 40, 241, 41));
        formLayout_2 = new QFormLayout(formLayoutWidget);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        cmb_salas = new QComboBox(formLayoutWidget);
        cmb_salas->setObjectName(QStringLiteral("cmb_salas"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, cmb_salas);

        formLayoutWidget_2 = new QWidget(groupBox);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(270, 40, 211, 81));
        formLayout_3 = new QFormLayout(formLayoutWidget_2);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(formLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(formLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_3);

        btn_unirse = new QPushButton(groupBox);
        btn_unirse->setObjectName(QStringLiteral("btn_unirse"));
        btn_unirse->setGeometry(QRect(40, 90, 161, 31));

        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(mapWindow);

        QMetaObject::connectSlotsByName(mapWindow);
    } // setupUi

    void retranslateUi(QDialog *mapWindow)
    {
        mapWindow->setWindowTitle(QApplication::translate("mapWindow", "Dialog", 0));
        groupBox_2->setTitle(QApplication::translate("mapWindow", "Crear un sala", 0));
        label_4->setText(QApplication::translate("mapWindow", "Mapas", 0));
        label_5->setText(QApplication::translate("mapWindow", "Jugadores", 0));
        cmb_jugadores->clear();
        cmb_jugadores->insertItems(0, QStringList()
         << QApplication::translate("mapWindow", "2", 0)
         << QApplication::translate("mapWindow", "3", 0)
         << QApplication::translate("mapWindow", "4", 0)
        );
        label_6->setText(QApplication::translate("mapWindow", "Nombre:", 0));
        btn_crear->setText(QApplication::translate("mapWindow", "Crear", 0));
        groupBox->setTitle(QApplication::translate("mapWindow", "Salas Disponibles", 0));
        label->setText(QApplication::translate("mapWindow", "       Salas        ", 0));
        label_2->setText(QApplication::translate("mapWindow", "Disponibles:", 0));
        label_3->setText(QApplication::translate("mapWindow", "En Espera:", 0));
        btn_unirse->setText(QApplication::translate("mapWindow", "unirse", 0));
    } // retranslateUi

};

namespace Ui {
    class mapWindow: public Ui_mapWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPWINDOW_H
