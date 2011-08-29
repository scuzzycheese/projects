TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = LCDApp
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
QT = core gui
SOURCES += cLCDDockWidget.cpp cDrawWidget.cpp cLM6800Proxy.cpp cDockMainWindow.cpp main.cpp cCustomDockWidget.cpp cSerialTalk.cpp
HEADERS += cLCDDockWidget.h cDockMainWindow.h cLM6800Proxy.h lcdFramework.h cCustomDockWidget.h cDrawWidget.h cSerialTalk.h
FORMS += lcd.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /usr/include/c++/4.4 
LIBS += 
