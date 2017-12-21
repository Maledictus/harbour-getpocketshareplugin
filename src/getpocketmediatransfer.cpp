#include "getpocketmediatransfer.h"

#include <QFile>
#include <QMap>
#include <QSettings>
#include <QStandardPaths>

#include <nemonotifications-qt5/notification.h>

#include "getpocketapi.h"

GetPocketMediaTransfer::GetPocketMediaTransfer(QObject *parent)
: MediaTransferInterface(parent)
{
}

GetPocketMediaTransfer::~GetPocketMediaTransfer()
{
}

void GetPocketMediaTransfer::BookmarkAdded(bool success)
{
    success ?
        setStatus(MediaTransferInterface::TransferFinished) :
        setStatus(MediaTransferInterface::TransferInterrupted);
}

bool GetPocketMediaTransfer::cancelEnabled() const
{
    return false;
}

QString GetPocketMediaTransfer::displayName() const
{
    return QString("GetPocket");
}

bool GetPocketMediaTransfer::restartEnabled() const
{
    return false;
}

QUrl GetPocketMediaTransfer::serviceIcon() const
{
    return QUrl::fromLocalFile("/usr/share/harbour-getpocketshareplugin/images/linksbag.png");
}

void GetPocketMediaTransfer::cancel()
{
    setStatus(MediaTransferInterface::TransferCanceled);
}

void GetPocketMediaTransfer::start()
{
    const auto& map = mediaItem()->value (MediaItem::UserData).toMap();
    QStringList tags = map["tags"].toString().split(",");
    for (auto& tag : tags)
        tag = tag.trimmed();

    GetPocketApi *api = new GetPocketApi;
    connect(api,
        &GetPocketApi::bookmarkAdded,
        this,
        [this, api]()
        {
            BookmarkAdded(true);
            api->deleteLater();
            Notification notificaiton;
            notificaiton.setAppName(displayName());
            notificaiton.setAppIcon(serviceIcon().path());
            notificaiton.setPreviewBody(tr("Bookmark added succesfully"));
            notificaiton.publish();
        });
    connect(api,
        &GetPocketApi::addingBookmarkFailed,
        this,
        [this, api]()
        {
            BookmarkAdded(false);
            api->deleteLater();
            Notification notificaiton;
            notificaiton.setAppName(displayName());
            notificaiton.setAppIcon(serviceIcon().path());
            notificaiton.setPreviewBody(tr("Bookmark adding failed"));
            notificaiton.publish();
        });
    api->AddBookmark(map["link"].toUrl(), tags);
}
