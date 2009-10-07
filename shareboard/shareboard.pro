CONFIG += qt debug
HEADERS +=	classes/widgets/qtcolorpicker.h \
				classes/widgets/cVectorDrawWidget.h \
				classes/widgets/QLine.h \
				ui_shareboard.h
SOURCES +=	classes/widgets/qtcolorpicker.cpp \
				classes/widgets/cVectorDrawWidget.cpp \
				classes/widgets/QLine.cpp \
				shareboard.cpp
TARGET = shareboard
FORMS += shareboard.ui
INCLUDEPATH += classes/widgets classes/vector
