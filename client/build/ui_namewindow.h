/********************************************************************************
** Form generated from reading UI file 'namewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAMEWINDOW_H
#define UI_NAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_nameWindow
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *nameLine;
    QGridLayout *gridLayout;
    QToolButton *btn_cancelar;
    QToolButton *btn_ok;

    void setupUi(QDialog *nameWindow)
    {
        if (nameWindow->objectName().isEmpty())
            nameWindow->setObjectName(QStringLiteral("nameWindow"));
        nameWindow->resize(445, 182);
        formLayout = new QFormLayout(nameWindow);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(nameWindow);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(4, QFormLayout::FieldRole, label);

        nameLine = new QLineEdit(nameWindow);
        nameLine->setObjectName(QStringLiteral("nameLine"));

        formLayout->setWidget(5, QFormLayout::FieldRole, nameLine);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btn_cancelar = new QToolButton(nameWindow);
        btn_cancelar->setObjectName(QStringLiteral("btn_cancelar"));

        gridLayout->addWidget(btn_cancelar, 0, 0, 1, 1);

        btn_ok = new QToolButton(nameWindow);
        btn_ok->setObjectName(QStringLiteral("btn_ok"));

        gridLayout->addWidget(btn_ok, 0, 1, 1, 1);


        formLayout->setLayout(6, QFormLayout::FieldRole, gridLayout);


        retranslateUi(nameWindow);

        QMetaObject::connectSlotsByName(nameWindow);
    } // setupUi

    void retranslateUi(QDialog *nameWindow)
    {
        nameWindow->setWindowTitle(QApplication::translate("nameWindow", "Dialog", 0));
        label->setText(QApplication::translate("nameWindow", "Ingrese su nombre:", 0));
        btn_cancelar->setText(QApplication::translate("nameWindow", "Cancelar", 0));
        btn_ok->setText(QApplication::translate("nameWindow", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class nameWindow: public Ui_nameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAMEWINDOW_H
