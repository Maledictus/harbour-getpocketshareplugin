#include "getpocketplugininfo.h"

#include <QFile>
#include <QSettings>

#include <mlite5/MDConfGroup>

#include "accountsettings.h"

GetPocketPluginInfo::GetPocketPluginInfo()
: m_Ready(false)
{
}

GetPocketPluginInfo::~GetPocketPluginInfo()
{
}

QList<TransferMethodInfo> GetPocketPluginInfo::info() const
{
    return m_InfoList;
}

void GetPocketPluginInfo::query()
{
    QString userName = AccountSettings::Instance()->value("userName").toString();
    QString accessToken = AccountSettings::Instance()->value("accessToken").toString();
    if (userName.isEmpty() || accessToken.isEmpty()) {
        const QString path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) +
                "/harbour-linksbag/linksbag.conf";
        if (QFile::exists(path)) {
            qDebug() << "Try to read credentials from linksbag settings file";
            QSettings settings(path, QSettings::NativeFormat);
            userName = settings.value("user_name").toString();
            accessToken = settings.value("access_token").toString();
        }
        else
        {
            qDebug() << "Try to read credentials from linksbag dconf settings";
            auto linksBagConf = new MDConfGroup("/apps/harbour-linksbag");
            userName = linksBagConf->value("userName").toString();
            accessToken = linksBagConf->value("accessToken").toString();
            linksBagConf->deleteLater();
        }
    }

    if (userName.isEmpty() || accessToken.isEmpty())
    {
        emit infoError(tr("LinksBag not authorized"));
        return;
    }

    AccountSettings::Instance()->setValue("userName", userName);
    AccountSettings::Instance()->setValue("accessToken", accessToken);

    TransferMethodInfo info;

    QStringList capabilities;
    capabilities << QLatin1String("text/x-url");

    info.displayName = QLatin1String("GetPocket");
    info.userName = userName;
    info.methodId = QLatin1String("GetPocketSharePlugin");
    info.accountIcon = QLatin1String("/usr/share/harbour-getpocketshareplugin/images/linksbag_square.png");
    info.shareUIPath = QLatin1String("/usr/share/harbour-getpocketshareplugin/qml/GetPocketShareUi.qml");
    info.capabilitities = capabilities;

    m_InfoList.clear();
    m_InfoList << info;

    m_Ready = true;
    emit infoReady();
}

bool GetPocketPluginInfo::ready() const
{
    return m_Ready;
}
