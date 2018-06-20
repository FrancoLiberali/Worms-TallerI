/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionsave;
    QAction *actionsave_as;
    QAction *actionSalir;
    QAction *actionArmas;
    QAction *actionGusanos;
    QAction *actionFondo_de_Pantalla;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;
    QWidget *viga_layout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QSpinBox *spinBox_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_2;
    QWidget *gusano_leyout;
    QVBoxLayout *gusano_layout;
    QPushButton *pushButton_3;
    QPushButton *pushButton_6;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFIle;
    QMenu *menuConfiguracion;
    QMenu *menuSalir;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(701, 449);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName(QStringLiteral("actionsave"));
        actionsave_as = new QAction(MainWindow);
        actionsave_as->setObjectName(QStringLiteral("actionsave_as"));
        actionSalir = new QAction(MainWindow);
        actionSalir->setObjectName(QStringLiteral("actionSalir"));
        actionArmas = new QAction(MainWindow);
        actionArmas->setObjectName(QStringLiteral("actionArmas"));
        actionGusanos = new QAction(MainWindow);
        actionGusanos->setObjectName(QStringLiteral("actionGusanos"));
        actionFondo_de_Pantalla = new QAction(MainWindow);
        actionFondo_de_Pantalla->setObjectName(QStringLiteral("actionFondo_de_Pantalla"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, -1);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setStyleSheet(QLatin1String("#upLeft {\n"
" background-color: transparent; \n"
"border-image: url(:/img/recursos/viga.png); \n"
"background: none; border: none;\n"
" background-repeat: none; \n"
"}\n"
" #upLeft:pressed {\n"
" border-image: url(:/img/recursos/viga.png);\n"
" }"));
        pushButton->setIconSize(QSize(100, 20));
        pushButton->setShortcut(QStringLiteral(""));

        verticalLayout->addWidget(pushButton);

        viga_layout = new QWidget(centralWidget);
        viga_layout->setObjectName(QStringLiteral("viga_layout"));
        verticalLayout_2 = new QVBoxLayout(viga_layout);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(viga_layout);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        spinBox_2 = new QSpinBox(viga_layout);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));

        verticalLayout_2->addWidget(spinBox_2);

        pushButton_4 = new QPushButton(viga_layout);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setStyleSheet(QLatin1String("#upLeft {\n"
" background-color: transparent;\n"
" border-image: url(:/img/recursos/gusano1.png);\n"
" background: none; \n"
"border: none; \n"
"background-repeat: none; \n"
"} \n"
"#upLeft:pressed { \n"
"border-image:  url(:/img/recursos/gusano1.png); \n"
"}"));

        verticalLayout_2->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(viga_layout);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout_2->addWidget(pushButton_5);


        verticalLayout->addWidget(viga_layout);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(pushButton_2);

        gusano_leyout = new QWidget(centralWidget);
        gusano_leyout->setObjectName(QStringLiteral("gusano_leyout"));
        gusano_leyout->setAcceptDrops(false);
        gusano_layout = new QVBoxLayout(gusano_leyout);
        gusano_layout->setSpacing(6);
        gusano_layout->setContentsMargins(11, 11, 11, 11);
        gusano_layout->setObjectName(QStringLiteral("gusano_layout"));
        pushButton_3 = new QPushButton(gusano_leyout);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setCursor(QCursor(Qt::PointingHandCursor));

        gusano_layout->addWidget(pushButton_3);


        verticalLayout->addWidget(gusano_leyout);

        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(pushButton_6);


        verticalLayout_3->addLayout(verticalLayout);


        horizontalLayout->addLayout(verticalLayout_3);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMouseTracking(true);

        horizontalLayout->addWidget(graphicsView);


        horizontalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 701, 22));
        menuFIle = new QMenu(menuBar);
        menuFIle->setObjectName(QStringLiteral("menuFIle"));
        menuConfiguracion = new QMenu(menuBar);
        menuConfiguracion->setObjectName(QStringLiteral("menuConfiguracion"));
        menuSalir = new QMenu(menuBar);
        menuSalir->setObjectName(QStringLiteral("menuSalir"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFIle->menuAction());
        menuBar->addAction(menuConfiguracion->menuAction());
        menuBar->addAction(menuSalir->menuAction());
        menuFIle->addAction(actionOpen);
        menuFIle->addAction(actionsave);
        menuFIle->addSeparator();
        menuFIle->addAction(actionsave_as);
        menuFIle->addSeparator();
        menuFIle->addAction(actionSalir);
        menuConfiguracion->addAction(actionFondo_de_Pantalla);
        menuConfiguracion->addAction(actionArmas);
        menuConfiguracion->addAction(actionGusanos);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Abrir", 0));
        actionsave->setText(QApplication::translate("MainWindow", "Guardar", 0));
        actionsave_as->setText(QApplication::translate("MainWindow", "Guardar como", 0));
        actionSalir->setText(QApplication::translate("MainWindow", "Salir", 0));
        actionArmas->setText(QApplication::translate("MainWindow", "Armas", 0));
        actionGusanos->setText(QApplication::translate("MainWindow", "Gusanos", 0));
        actionFondo_de_Pantalla->setText(QApplication::translate("MainWindow", "Fondo de Pantalla", 0));
        label->setText(QApplication::translate("MainWindow", "Agregar:", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Viga", 0));
        label_3->setText(QApplication::translate("MainWindow", "Angulo:", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Grande", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "Pequenia", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Gusano", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Agregar", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "Eliminar", 0));
        menuFIle->setTitle(QApplication::translate("MainWindow", "Archivo", 0));
        menuConfiguracion->setTitle(QApplication::translate("MainWindow", "Configuracion", 0));
        menuSalir->setTitle(QApplication::translate("MainWindow", "Salir", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
