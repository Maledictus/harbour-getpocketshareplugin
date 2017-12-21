#pragma once

#include <QString>
#include <QUrl>

#include <TransferEngine-qt5/mediaitem.h>
#include <TransferEngine-qt5/mediatransferinterface.h>



class GetPocketMediaTransfer : public MediaTransferInterface
{
    Q_OBJECT

public:
    GetPocketMediaTransfer(QObject * parent = 0);
    virtual ~GetPocketMediaTransfer();

    bool cancelEnabled() const;
    QString	displayName() const;
    bool restartEnabled() const;
    QUrl serviceIcon() const;
private:
    void BookmarkAdded(bool success);

public slots:
    void cancel();
    void start();

};
