#include "getpocketapi.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QSettings>
#include <QStandardPaths>

GetPocketApi::GetPocketApi(QObject *parent)
: QObject(parent)
, m_ConsumerKey("36050-db8157de51cbb0c5f72edc33")
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
    QSettings settings(QStandardPaths::writableLocation (QStandardPaths::ConfigLocation) +
            "/harbour-linksbag/linksbag.conf", QSettings::NativeFormat);
    const QString& accessToken = settings.value ("access_token").toString();

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
