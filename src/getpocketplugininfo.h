#pragma once

#include <TransferEngine-qt5/transfermethodinfo.h>
#include <TransferEngine-qt5/transferplugininfo.h>

class GetPocketPluginInfo : public TransferPluginInfo
{
    Q_OBJECT

    bool m_Ready;
    QList<TransferMethodInfo> m_InfoList;

public:
    GetPocketPluginInfo();
    virtual ~GetPocketPluginInfo();

    QList<TransferMethodInfo> info() const;
    void query();
    bool ready() const;
};
