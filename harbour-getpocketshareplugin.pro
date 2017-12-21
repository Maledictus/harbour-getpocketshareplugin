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

qml.path = /usr/share/nemo-transferengine/plugins
qml.files = qml/GetPocketShareUi.qml

icons.files = icons/linksbag.png
icons.path = /usr/share/harbour-getpocketshareplugin/images

INSTALLS += target qml icons

DISTFILES += rpm/harbour-getpocketshareplugin.spec \
    rpm/harbour-getpocketshareplugin.yaml \
    qml/GetPocketShareUi.qml \
    translations/harbour-getpocketshareplugin.ts \
    translations/harbour-getpocketshareplugin_en.ts \
    translations/harbour-getpocketshareplugin_ru.ts

TRANSLATIONS += translations/harbour-getpocketshareplugin.ts \
    translations/harbour-getpocketshareplugin_en.ts \
    translations/harbour-getpocketshareplugin_ru.ts

EN_QM = translations/harbour-getpocketshareplugin_en.qm
RU_QM = translations/harbour-getpocketshareplugin_ru.qm

english_install.path = /usr/share/translations/nemotransferengine
english_install.files = $$EN_QM
english_install.CONFIG += no_check_exist

russian_install.path = /usr/share/translations/nemotransferengine
russian_install.files = $$RU_QM
russian_install.CONFIG += no_check_exist

INSTALLS += english_install russian_install
