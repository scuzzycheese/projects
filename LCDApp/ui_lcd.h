/********************************************************************************
** Form generated from reading UI file 'lcd.ui'
**
** Created: Mon Dec 12 17:13:01 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LCD_H
#define UI_LCD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include "cDrawWidget.h"

QT_BEGIN_NAMESPACE

class Ui_lcd
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFrame *frame;
    cDrawWidget *drawPanel;
    QWidget *realEstateTab;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QListWidget *pluginList;
    QFrame *frame_2;
    QFormLayout *formLayout;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QFrame *pluginConfig;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *lcd)
    {
        if (lcd->objectName().isEmpty())
            lcd->setObjectName(QString::fromUtf8("lcd"));
        lcd->resize(869, 660);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lcd->sizePolicy().hasHeightForWidth());
        lcd->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(lcd);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        centralwidget->setSizeIncrement(QSize(0, 0));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        frame = new QFrame(tab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setEnabled(true);
        frame->setGeometry(QRect(110, 140, 514, 130));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        drawPanel = new cDrawWidget(frame);
        drawPanel->setObjectName(QString::fromUtf8("drawPanel"));
        drawPanel->setGeometry(QRect(1, 1, 512, 128));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(4);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(drawPanel->sizePolicy().hasHeightForWidth());
        drawPanel->setSizePolicy(sizePolicy1);
        drawPanel->setSizeIncrement(QSize(4, 1));
        drawPanel->setBaseSize(QSize(512, 128));
        drawPanel->setCursor(QCursor(Qt::CrossCursor));
        tabWidget->addTab(tab, QString());
        realEstateTab = new QWidget();
        realEstateTab->setObjectName(QString::fromUtf8("realEstateTab"));
        gridLayout_2 = new QGridLayout(realEstateTab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(realEstateTab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pluginList = new QListWidget(groupBox);
        pluginList->setObjectName(QString::fromUtf8("pluginList"));

        gridLayout_3->addWidget(pluginList, 0, 0, 1, 1);

        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame_2);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        pushButton = new QPushButton(frame_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        formLayout->setWidget(0, QFormLayout::LabelRole, pushButton);


        gridLayout_3->addWidget(frame_2, 1, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(realEstateTab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pluginConfig = new QFrame(groupBox_2);
        pluginConfig->setObjectName(QString::fromUtf8("pluginConfig"));
        sizePolicy.setHeightForWidth(pluginConfig->sizePolicy().hasHeightForWidth());
        pluginConfig->setSizePolicy(sizePolicy);
        pluginConfig->setFrameShape(QFrame::StyledPanel);
        pluginConfig->setFrameShadow(QFrame::Raised);

        gridLayout_4->addWidget(pluginConfig, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 0, 0, 1, 1);

        tabWidget->addTab(realEstateTab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        lcd->setCentralWidget(centralwidget);
        menubar = new QMenuBar(lcd);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 869, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setGeometry(QRect(355, 161, 140, 46));
        menuFile->setSizeIncrement(QSize(4, 1));
        menuFile->setBaseSize(QSize(512, 128));
        lcd->setMenuBar(menubar);
        statusbar = new QStatusBar(lcd);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        lcd->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());

        retranslateUi(lcd);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(lcd);
    } // setupUi

    void retranslateUi(QMainWindow *lcd)
    {
        lcd->setWindowTitle(QApplication::translate("lcd", "MainWindow", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("lcd", "Doodle", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("lcd", "Plugins", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("lcd", "Add", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("lcd", "Plugin Configuration", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(realEstateTab), QApplication::translate("lcd", "Plugins", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("lcd", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class lcd: public Ui_lcd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LCD_H
