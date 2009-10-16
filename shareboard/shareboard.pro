CONFIG += qt debug
HEADERS +=	classes/widgets/qtcolorpicker.h \
				classes/widgets/cVectorDrawWidget.h \
				classes/widgets/QVecLine.h \
				classes/widgets/cMatrixWidget.h \
				ui_shareboard.h
SOURCES +=	classes/widgets/qtcolorpicker.cpp \
				classes/widgets/cVectorDrawWidget.cpp \
				classes/widgets/QVecLine.cpp \
				classes/widgets/cMatrixWidget.cpp \
				shareboard.cpp
TARGET = shareboard
FORMS += shareboard.ui
INCLUDEPATH += classes/widgets classes/vector
