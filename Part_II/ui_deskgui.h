/********************************************************************************
** Form generated from reading UI file 'deskgui.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESKGUI_H
#define UI_DESKGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeskGUI
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit_pos;
    QPushButton *pushButton_start;
    QTableWidget *desk;
    QLabel *label_knight;
    QLineEdit *lineEdit_knight;
    QPushButton *pushButton_stop;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DeskGUI)
    {
        if (DeskGUI->objectName().isEmpty())
            DeskGUI->setObjectName(QString::fromUtf8("DeskGUI"));
        DeskGUI->resize(538, 535);
        centralWidget = new QWidget(DeskGUI);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        lineEdit_pos = new QLineEdit(centralWidget);
        lineEdit_pos->setObjectName(QString::fromUtf8("lineEdit_pos"));

        gridLayout->addWidget(lineEdit_pos, 4, 0, 1, 1);

        pushButton_start = new QPushButton(centralWidget);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));

        gridLayout->addWidget(pushButton_start, 5, 0, 1, 1);

        desk = new QTableWidget(centralWidget);
        if (desk->columnCount() < 8)
            desk->setColumnCount(8);
        QFont font;
        font.setPointSize(16);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        desk->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        desk->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        desk->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        desk->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        desk->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        desk->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        desk->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        desk->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        if (desk->rowCount() < 8)
            desk->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font);
        desk->setVerticalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font);
        desk->setVerticalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font);
        desk->setVerticalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFont(font);
        desk->setVerticalHeaderItem(3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setFont(font);
        desk->setVerticalHeaderItem(4, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setFont(font);
        desk->setVerticalHeaderItem(5, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setFont(font);
        desk->setVerticalHeaderItem(6, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setFont(font);
        desk->setVerticalHeaderItem(7, __qtablewidgetitem15);
        desk->setObjectName(QString::fromUtf8("desk"));

        gridLayout->addWidget(desk, 0, 0, 1, 1);

        label_knight = new QLabel(centralWidget);
        label_knight->setObjectName(QString::fromUtf8("label_knight"));

        gridLayout->addWidget(label_knight, 1, 0, 1, 1);

        lineEdit_knight = new QLineEdit(centralWidget);
        lineEdit_knight->setObjectName(QString::fromUtf8("lineEdit_knight"));

        gridLayout->addWidget(lineEdit_knight, 2, 0, 1, 1);

        pushButton_stop = new QPushButton(centralWidget);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));

        gridLayout->addWidget(pushButton_stop, 6, 0, 1, 1);

        DeskGUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DeskGUI);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 538, 21));
        DeskGUI->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DeskGUI);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        DeskGUI->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DeskGUI);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DeskGUI->setStatusBar(statusBar);

        retranslateUi(DeskGUI);

        QMetaObject::connectSlotsByName(DeskGUI);
    } // setupUi

    void retranslateUi(QMainWindow *DeskGUI)
    {
        DeskGUI->setWindowTitle(QCoreApplication::translate("DeskGUI", "DeskGUI", nullptr));
        label->setText(QCoreApplication::translate("DeskGUI", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \320\272\320\276\320\275\320\265\321\207\320\275\320\276\320\271 \320\277\320\276\320\267\320\270\321\206\320\270\320\270", nullptr));
        pushButton_start->setText(QCoreApplication::translate("DeskGUI", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        label_knight->setText(QCoreApplication::translate("DeskGUI", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \320\272\320\276\320\275\321\217", nullptr));
        pushButton_stop->setText(QCoreApplication::translate("DeskGUI", "\320\241\321\202\320\276\320\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeskGUI: public Ui_DeskGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESKGUI_H
