TEMPLATE = lib

QMAKE_CXXFLAGS += -std=c++0x

TARGET = $$qtLibraryTarget(getpocketshareplugin)

target.path = /usr/lib/nemo-transferengine/plugins

QT += network

CONFIG += plugin link_pkgconfig

PKGCONFIG += nemotransferengine-qt5

HEADERS += src/getpockettransferiface.h \
    src/getpocketplugininfo.h \
    src/getpocketmediatransfer.h \
    src/getpocketapi.h

SOURCES += src/getpockettransferiface.cpp \
    src/getpocketplugininfo.cpp \
    src/getpocketmediatransfer.cpp \
    src/getpocketapi.cpp

qml.path = /usr/share/harbour-getpocketshareplugin/qml
qml.files = qml/GetPocketShareUi.qml

icons.files = icons/linksbag.png
icons.path = /usr/share/harbour-getpocketshareplugin/images

INSTALLS += target qml icons

DISTFILES += qml/GetPocketShareUi.qml

