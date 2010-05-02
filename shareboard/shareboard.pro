CONFIG += qt debug
HEADERS +=	classes/widgets/qtcolorpicker.h \
				classes/widgets/cVectorDrawWidget.h \
				classes/widgets/QVecLine.h \
				classes/widgets/cMatrixWidget.h \
				classes/widgets/cServer.h \
				classes/widgets/cConnDiag.h \
				classes/widgets/cStartServerDiag.h \
				classes/widgets/cClient.h\
				classes/cPDU.h \
				classes/sNetPeer.h \
				ui_shareboard.h
SOURCES +=	classes/widgets/qtcolorpicker.cpp \
				classes/widgets/cVectorDrawWidget.cpp \
				classes/widgets/QVecLine.cpp \
				classes/widgets/cMatrixWidget.cpp \
				classes/widgets/cServer.cpp \
				classes/widgets/cConnDiag.cpp \
				classes/widgets/cStartServerDiag.cpp \
				classes/widgets/cClient.cpp \
				classes/cPDU.cpp \
				shareboard.cpp
TARGET = shareboard
FORMS += shareboard.ui connectDialog.ui startNetworkDialog.ui
QT += network
INCLUDEPATH += classes/widgets classes/vector classes
