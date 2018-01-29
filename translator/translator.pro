TEMPLATE = lib
QT += quick core
CONFIG += qt plugin link_pkgconfig

TARGET = $$qtLibraryTarget(translator)
target.path = /usr/share/harbour-getpocketshareplugin/qml/harbour/getpocketshareplugin/translator

SOURCES += \
    translatorplugin.cpp \
    translator.cpp

HEADERS += \
    translatorplugin.h \
    translator.h

qmldir.files = qmldir
qmldir.path = /usr/share/harbour-getpocketshareplugin/qml/harbour/getpocketshareplugin/translator

INSTALLS += target qmldir
