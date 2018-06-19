/********************************************************************************
** Form generated from reading UI file 'configgusanos.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGGUSANOS_H
#define UI_CONFIGGUSANOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigGusanos
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ConfigGusanos)
    {
        if (ConfigGusanos->objectName().isEmpty())
            ConfigGusanos->setObjectName(QStringLiteral("ConfigGusanos"));
        ConfigGusanos->resize(400, 101);
        widget = new QWidget(ConfigGusanos);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(40, 20, 321, 59));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        verticalLayout->addWidget(spinBox);


        horizontalLayout->addLayout(verticalLayout);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        retranslateUi(ConfigGusanos);
        QObject::connect(buttonBox, SIGNAL(accepted()), ConfigGusanos, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ConfigGusanos, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConfigGusanos);
    } // setupUi

    void retranslateUi(QDialog *ConfigGusanos)
    {
        ConfigGusanos->setWindowTitle(QApplication::translate("ConfigGusanos", "Dialog", 0));
        label->setText(QApplication::translate("ConfigGusanos", "Vida:", 0));
    } // retranslateUi

};

namespace Ui {
    class ConfigGusanos: public Ui_ConfigGusanos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGGUSANOS_H
