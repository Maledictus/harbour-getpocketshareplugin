#include "getpocketapi.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QSettings>
#include <QStandardPaths>

#include <mlite5/MDConfGroup>

#include "accountsettings.h"

GetPocketApi::GetPocketApi(QObject *parent)
: QObject(parent)
, m_ConsumerKey(CONSUMER_KEY)
, m_NAM(new QNetworkAccessManager(this))
{
}

namespace
{
    QNetworkRequest CreateRequest(const QUrl& url)
    {
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader ,
                "application/json; charset=UTF-8");
        request.setRawHeader("X-Accept", "application/json");
        return request;
    }
}

void GetPocketApi::AddBookmark(const QUrl& url, const QStringList& tags)
{
    QString accessToken = AccountSettings::Instance()->value("accessToken").toString();
    if (accessToken.isEmpty()) {
        const QString path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) +
                "/harbour-linksbag/linksbag.conf";
        if (QFile::exists(path)) {
            qDebug() << "Try to read credentials from linksbag settings file";
            QSettings settings(path, QSettings::NativeFormat);
            accessToken = settings.value("access_token").toString();
        }
        else
        {
            qDebug() << "Try to read credentials from linksbag dconf settings";
            auto linksBagConf = new MDConfGroup("/apps/harbour-linksbag");
            accessToken = linksBagConf->value("accessToken").toString();
            linksBagConf->deleteLater();
        }
    }

    QVariantMap params;
    params["consumer_key"] = m_ConsumerKey;
    params["access_token"] = accessToken;
    params["url"] = url.toEncoded();
    params["tags"] = tags.join(',');

    QJsonDocument doc(QJsonObject::fromVariantMap(params));

    QNetworkReply *reply = m_NAM->post(CreateRequest(QUrl("https://getpocket.com/v3/add")),
            doc.toJson());

    connect(reply,
            &QNetworkReply::finished,
            this,
            &GetPocketApi::handleAddBookmark);
    connect(reply,
            SIGNAL(error(QNetworkReply::NetworkError)),
            this,
            SLOT(handleNetworkError(QNetworkReply::NetworkError)));
}

void GetPocketApi::handleAddBookmark()
{
    if (auto reply = qobject_cast<QNetworkReply*>(sender ()))
    {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if (doc.isNull())
            emit addingBookmarkFailed();
        else
        {
            const auto& rootObject = doc.object();
            if (rootObject["status"].toInt() == 1)
                emit bookmarkAdded();
            else
                emit addingBookmarkFailed();
        }
    }
}

void GetPocketApi::handleNetworkError(QNetworkReply::NetworkError)
{
    emit addingBookmarkFailed();
}
