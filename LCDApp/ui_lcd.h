/********************************************************************************
** Form generated from reading UI file 'lcd.ui'
**
** Created: Fri Jul 1 22:44:15 2011
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
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>
#include "cVectorDrawWidget.h"

QT_BEGIN_NAMESPACE

class Ui_lcd
{
public:
    QWidget *centralwidget;
    cVectorDrawWidget *drawPanel;
    QTextEdit *textPanel;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *lcd)
    {
        if (lcd->objectName().isEmpty())
            lcd->setObjectName(QString::fromUtf8("lcd"));
        lcd->resize(530, 398);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lcd->sizePolicy().hasHeightForWidth());
        lcd->setSizePolicy(sizePolicy);
        lcd->setMinimumSize(QSize(530, 398));
        lcd->setMaximumSize(QSize(530, 398));
        centralwidget = new QWidget(lcd);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(530, 351));
        centralwidget->setMaximumSize(QSize(530, 351));
        centralwidget->setSizeIncrement(QSize(0, 0));
        drawPanel = new cVectorDrawWidget(centralwidget);
        drawPanel->setObjectName(QString::fromUtf8("drawPanel"));
        drawPanel->setGeometry(QRect(10, 210, 512, 128));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(4);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(drawPanel->sizePolicy().hasHeightForWidth());
        drawPanel->setSizePolicy(sizePolicy1);
        drawPanel->setMinimumSize(QSize(512, 128));
        drawPanel->setSizeIncrement(QSize(4, 1));
        drawPanel->setBaseSize(QSize(512, 128));
        textPanel = new QTextEdit(centralwidget);
        textPanel->setObjectName(QString::fromUtf8("textPanel"));
        textPanel->setGeometry(QRect(10, 10, 511, 181));
        textPanel->setReadOnly(true);
        lcd->setCentralWidget(centralwidget);
        menubar = new QMenuBar(lcd);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 530, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setGeometry(QRect(355, 165, 512, 128));
        menuFile->setSizeIncrement(QSize(4, 1));
        menuFile->setBaseSize(QSize(512, 128));
        lcd->setMenuBar(menubar);
        statusbar = new QStatusBar(lcd);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        lcd->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());

        retranslateUi(lcd);

        QMetaObject::connectSlotsByName(lcd);
    } // setupUi

    void retranslateUi(QMainWindow *lcd)
    {
        lcd->setWindowTitle(QApplication::translate("lcd", "MainWindow", 0, QApplication::UnicodeUTF8));
        textPanel->setHtml(QApplication::translate("lcd", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("lcd", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class lcd: public Ui_lcd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LCD_H
