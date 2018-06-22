/********************************************************************************
** Form generated from reading UI file 'connectwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTWINDOW_H
#define UI_CONNECTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_connectWindow
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *ipLine;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *portLine;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *connectWindow)
    {
        if (connectWindow->objectName().isEmpty())
            connectWindow->setObjectName(QStringLiteral("connectWindow"));
        connectWindow->resize(400, 300);
        gridLayout_2 = new QGridLayout(connectWindow);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(connectWindow);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        ipLine = new QLineEdit(connectWindow);
        ipLine->setObjectName(QStringLiteral("ipLine"));

        horizontalLayout->addWidget(ipLine);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(connectWindow);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        portLine = new QLineEdit(connectWindow);
        portLine->setObjectName(QStringLiteral("portLine"));

        horizontalLayout_2->addWidget(portLine);


        verticalLayout->addLayout(horizontalLayout_2);

        pushButton = new QPushButton(connectWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(connectWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(verticalLayout, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 0, 1, 1);


        retranslateUi(connectWindow);

        QMetaObject::connectSlotsByName(connectWindow);
    } // setupUi

    void retranslateUi(QDialog *connectWindow)
    {
        connectWindow->setWindowTitle(QApplication::translate("connectWindow", "Dialog", 0));
        label_2->setText(QApplication::translate("connectWindow", "IP:", 0));
        label->setText(QApplication::translate("connectWindow", "Puerto:", 0));
        pushButton->setText(QApplication::translate("connectWindow", "Conectar", 0));
        pushButton_2->setText(QApplication::translate("connectWindow", "Cancelar", 0));
    } // retranslateUi

};

namespace Ui {
    class connectWindow: public Ui_connectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTWINDOW_H
