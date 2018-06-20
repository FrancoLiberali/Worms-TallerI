/********************************************************************************
** Form generated from reading UI file 'configarmas.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGARMAS_H
#define UI_CONFIGARMAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigArmas
{
public:
    QDialogButtonBox *buttonBox;
    QCheckBox *checkBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpinBox *spinBox;
    QCheckBox *checkBox_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *ConfigArmas)
    {
        if (ConfigArmas->objectName().isEmpty())
            ConfigArmas->setObjectName(QStringLiteral("ConfigArmas"));
        ConfigArmas->resize(378, 274);
        buttonBox = new QDialogButtonBox(ConfigArmas);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(170, 230, 166, 25));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        checkBox = new QCheckBox(ConfigArmas);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(30, 20, 91, 21));
        QFont font;
        font.setPointSize(12);
        checkBox->setFont(font);
        layoutWidget = new QWidget(ConfigArmas);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(190, 10, 122, 201));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        spinBox = new QSpinBox(layoutWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        verticalLayout->addWidget(spinBox);

        checkBox_2 = new QCheckBox(layoutWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        verticalLayout->addWidget(checkBox_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_2);


        retranslateUi(ConfigArmas);

        QMetaObject::connectSlotsByName(ConfigArmas);
    } // setupUi

    void retranslateUi(QDialog *ConfigArmas)
    {
        ConfigArmas->setWindowTitle(QApplication::translate("ConfigArmas", "Dialog", 0));
        checkBox->setText(QApplication::translate("ConfigArmas", "Hablitar", 0));
        label->setText(QApplication::translate("ConfigArmas", "Seleccionar arma:", 0));
        label_2->setText(QApplication::translate("ConfigArmas", "Municion:", 0));
        checkBox_2->setText(QApplication::translate("ConfigArmas", "Infinitas", 0));
    } // retranslateUi

};

namespace Ui {
    class ConfigArmas: public Ui_ConfigArmas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGARMAS_H
