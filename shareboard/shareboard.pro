CONFIG += qt debug
HEADERS +=	classes/widgets/qtcolorpicker.h \
				classes/widgets/cVectorDrawWidget.h \
				classes/widgets/QVecLine.h \
				classes/widgets/cMatrixWidget.h \
				classes/widgets/cServer.h \
				ui_shareboard.h
SOURCES +=	classes/widgets/qtcolorpicker.cpp \
				classes/widgets/cVectorDrawWidget.cpp \
				classes/widgets/QVecLine.cpp \
				classes/widgets/cMatrixWidget.cpp \
				classes/widgets/cServer.cpp \
				shareboard.cpp
TARGET = shareboard
FORMS += shareboard.ui
QT += network
INCLUDEPATH += classes/widgets classes/vector
