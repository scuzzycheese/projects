TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = LCDApp
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
QT = core gui
SOURCES += cSerialTalk.cpp cLM6800Proxy.cpp cVectorDrawWidget.cpp main.cpp
HEADERS += cLM6800Proxy.h cVectorDrawWidget.h lcdFramework.h cSerialTalk.h
FORMS += lcd.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /usr/include/c++/4.4 
LIBS += 
