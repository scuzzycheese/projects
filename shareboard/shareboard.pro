CONFIG += qt debug
HEADERS +=	classes/widgets/qtcolorpicker.h \
				classes/widgets/cVectorDrawWidget.h \
				classes/widgets/QVecLine.h \
				classes/widgets/cMatrixWidget.h \
				classes/widgets/cServer.h \
				classes/cNetwork.h \
				ui_shareboard.h
SOURCES +=	classes/widgets/qtcolorpicker.cpp \
				classes/widgets/cVectorDrawWidget.cpp \
				classes/widgets/QVecLine.cpp \
				classes/widgets/cMatrixWidget.cpp \
				classes/widgets/cServer.cpp \
				classes/cNetwork.cpp \
				shareboard.cpp
TARGET = shareboard
FORMS += shareboard.ui connectDialog.ui
QT += network
INCLUDEPATH += classes/widgets classes/vector classes
