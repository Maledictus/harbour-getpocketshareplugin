#include "getpocketplugininfo.h"

#include <QSettings>
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
    QSettings settings(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) +
            "/harbour-linksbag/linksbag.conf", QSettings::NativeFormat);
    const QString& userName = settings.value("user_name").toString();
    const QString& accessToken = settings.value("access_token").toString();

    if (userName.isEmpty() || accessToken.isEmpty())
    {
        emit infoError(tr("LinksBag not authorized"));
        return;
    }

    TransferMethodInfo info;

    QStringList capabilities;
    capabilities << QLatin1String("text/x-url");

    info.displayName = QLatin1String("GetPocket");
    info.userName = userName;
    info.methodId = QLatin1String("GetPocketSharePlugin");
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
