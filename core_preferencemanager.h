#ifndef CORE_PREFERENCEMANAGER_H
#define CORE_PREFERENCEMANAGER_H

#include <QtGui>
#include "core_appinfo.h"
#include "core_messagebroker.h"
#include "dao_preferencedataaccessor.h"

class PreferenceManager
{
public:
    PreferenceManager(MessageBroker *messageBroker);
    QString initializeToDefault();
    QString update(QString domain, int port);
    QString getDomain();
    int getPort();

private:
    const static QString DB_RELATIVE_PATH;
    MessageBroker *messageBroker_m;

    QString getAbsoluteSettingFilePath();
};

#endif // CORE_PREFERENCEMANAGER_H
