CONFIG += qt debug
HEADERS +=	classes/display/qtcolorpicker.h \
				classes/display/cVectorDrawWidget.h \
				classes/display/cMatrixWidget.h \
				classes/display/cConnDiag.h \
				classes/display/cStartServerDiag.h \
				classes/appengine/QVecLine.h \
				classes/network/cPDU.h \
				classes/network/sNetPeer.h \
				classes/network/cClient.h\
				classes/network/cServer.h \
				ui_shareboard.h
SOURCES +=	classes/display/qtcolorpicker.cpp \
				classes/display/cVectorDrawWidget.cpp \
				classes/display/cMatrixWidget.cpp \
				classes/display/cConnDiag.cpp \
				classes/display/cStartServerDiag.cpp \
				classes/appengine/QVecLine.cpp \
				classes/network/cPDU.cpp \
				classes/network/cServer.cpp \
				classes/network/cClient.cpp \
				shareboard.cpp
TARGET = shareboard
FORMS += shareboard.ui connectDialog.ui startNetworkDialog.ui
QT += network
INCLUDEPATH += classes/display classes/network classes/appengine classes
