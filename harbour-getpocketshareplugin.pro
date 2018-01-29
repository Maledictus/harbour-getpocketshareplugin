TEMPLATE = subdirs
SUBDIRS = \
    shareui \
    translator

OTHER_FILES = \
    rpm/harbour-getpocketshareplugin.yaml

DISTFILES += rpm/harbour-getpocketshareplugin.spec \
    rpm/harbour-getpocketshareplugin.yaml \
    translations/getpocketshareplugin.ts \
    translations/getpocketshareplugin-en.ts \
    translations/getpocketshareplugin-ru.ts \
    translations/getpocketshareplugin-sv.ts \
    translations/getpocketshareplugin-es.ts \
    translations/getpocketshareplugin-fr.ts \
    rpm/harbour-getpocketshareplugin.changes

TRANSLATIONS += translations/getpocketshareplugin.ts \
    translations/getpocketshareplugin-en.ts \
    translations/getpocketshareplugin-ru.ts \
    translations/getpocketshareplugin-fr.ts \
    translations/getpocketshareplugin-es.ts \
    translations/getpocketshareplugin-sv.ts

EN_QM = translations/getpocketshareplugin-en.qm
RU_QM = translations/getpocketshareplugin-ru.qm
FR_QM = translations/getpocketshareplugin-fr.qm
ES_QM = translations/getpocketshareplugin-es.qm
SV_QM = translations/getpocketshareplugin-sv.qm

english_install.path = /usr/share/translations/harbour-getpocketshareplugin
english_install.files = $$EN_QM
english_install.CONFIG += no_check_exist

russian_install.path = /usr/share/translations/harbour-getpocketshareplugin
russian_install.files = $$RU_QM
russian_install.CONFIG += no_check_exist

sv_install.path = /usr/share/translations/harbour-getpocketshareplugin
sv_install.files = $$SV_QM
sv_install.CONFIG += no_check_exist

fr_install.path = /usr/share/translations/harbour-getpocketshareplugin
fr_install.files = $$FR_QM
fr_install.CONFIG += no_check_exist

es_install.path = /usr/share/translations/harbour-getpocketshareplugin
es_install.files = $$ES_QM
es_install.CONFIG += no_check_exist

INSTALLS += english_install russian_install fr_install es_install sv_install

