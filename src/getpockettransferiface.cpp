#include "getpockettransferiface.h"
#include "getpocketplugininfo.h"
#include "getpocketmediatransfer.h"

#include <QtPlugin>
#include <QSettings>
#include <QStandardPaths>

GetPocketSharePlugin::GetPocketSharePlugin()
{
}

GetPocketSharePlugin::~GetPocketSharePlugin()
{
}

QString GetPocketSharePlugin::pluginId() const
{
    return QLatin1String("GetPocketSharePlugin");
}

bool GetPocketSharePlugin::enabled() const
{
    QSettings settings(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) +
            "/harbour-linksbag/linksbag.conf", QSettings::NativeFormat);
    const QString& userName = settings.value("user_name").toString();
    const QString& accessToken = settings.value("access_token").toString();

    return !userName.isEmpty() && !accessToken.isEmpty();
}

TransferPluginInfo* GetPocketSharePlugin::infoObject()
{
    return new GetPocketPluginInfo;
}

MediaTransferInterface* GetPocketSharePlugin::transferObject()
{
    return new GetPocketMediaTransfer;
}
