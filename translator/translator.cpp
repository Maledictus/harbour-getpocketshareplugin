#include "translator.h"

#include <QGuiApplication>
#include <QStringList>
#include <QLocale>
#include <QDebug>

Translator::Translator(QObject *parent)
: QObject(parent)
{
    translator = new QTranslator(this);
    if (translator->load(QLocale::system(), "getpocketshareplugin", "-", "/usr/share/translations/harbour-getpocketshareplugin/")) {
        qDebug() << "translation loaded: " << QLocale::system().name();
        QGuiApplication::installTranslator(translator);
    }
    else {
        translator->load(QLocale(QLocale::English), "getpocketshareplugin", "-", "/usr/share/translations/harbour-getpocketshareplugin/");
        qDebug() << "translation not available for " << QLocale::system().name() << ". Load english locale";
        QGuiApplication::installTranslator(translator);
    }
}
