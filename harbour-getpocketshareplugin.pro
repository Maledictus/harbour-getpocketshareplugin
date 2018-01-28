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
    translations/harbour-getpocketshareplugin_ru.ts \
    rpm/harbour-getpocketshareplugin.changes

TRANSLATIONS += translations/harbour-getpocketshareplugin.ts \
    translations/harbour-getpocketshareplugin_en.ts \
    translations/harbour-getpocketshareplugin_ru.ts \
    translations/harbour-getpocketshareplugin_fr.ts \
    translations/harbour-getpocketshareplugin_es.ts \
    translations/harbour-getpocketshareplugin_sv.ts

EN_QM = translations/harbour-getpocketshareplugin_en.qm
RU_QM = translations/harbour-getpocketshareplugin_ru.qm
FR_QM = translations/harbour-getpocketshareplugin_fr.qm
ES_QM = translations/harbour-getpocketshareplugin_es.qm
SV_QM = translations/harbour-getpocketshareplugin_sv.qm

english_install.path = /usr/share/translations/nemotransferengine
english_install.files = $$EN_QM
english_install.CONFIG += no_check_exist

russian_install.path = /usr/share/translations/nemotransferengine
russian_install.files = $$RU_QM
russian_install.CONFIG += no_check_exist

sv_install.path = /usr/share/translations/nemotransferengine
sv_install.files = $$SV_QM
sv_install.CONFIG += no_check_exist

fr_install.path = /usr/share/translations/nemotransferengine
fr_install.files = $$FR_QM
fr_install.CONFIG += no_check_exist

es_install.path = /usr/share/translations/nemotransferengine
es_install.files = $$ES_QM
es_install.CONFIG += no_check_exist

INSTALLS += english_install russian_install sv_install fr_install es_install
