#include "getpockettransferiface.h"

#include <QtPlugin>
#include <QSettings>
#include <QStandardPaths>
#include <QFile>

#include <mlite5/MDConfGroup>

#include "accountsettings.h"
#include "getpocketplugininfo.h"
#include "getpocketmediatransfer.h"

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
    QString userName = AccountSettings::Instance()->value("user_name").toString();
    QString accessToken = AccountSettings::Instance()->value("access_token").toString();
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
