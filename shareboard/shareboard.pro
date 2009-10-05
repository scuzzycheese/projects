CONFIG += qt debug
HEADERS +=	classes/widgets/qtcolorpicker.h \
				classes/widgets/pWidget.h \
				ui_shareboard.h
SOURCES +=	classes/widgets/qtcolorpicker.cpp \
				classes/widgets/pWidget.cpp \
				shareboard.cpp
TARGET = shareboard
FORMS += shareboard.ui
INCLUDEPATH += classes/widgets
