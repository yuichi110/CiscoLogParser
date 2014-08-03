#include "core_preferencemanager.h"

const QString PreferenceManager::DB_RELATIVE_PATH = "/settings.db";

PreferenceManager::PreferenceManager(MessageBroker *messageBroker)
{
    messageBroker_m = messageBroker;
    messageBroker_m->registerPreferenceManager(this);
    //preferenceDataAccessor_m = new PreferenceDataAccessor(AppInfo::PREF_DBFILE_PATH);
}

QString PreferenceManager::getAbsoluteSettingFilePath(){
    QString dirPath = QCoreApplication::applicationDirPath();
    return dirPath + DB_RELATIVE_PATH;
}

QString PreferenceManager::getDomain(){
    PreferenceDataAccessor *accessor = new PreferenceDataAccessor(getAbsoluteSettingFilePath());
    QString domain = accessor->getDomain();
    return domain;
}

int PreferenceManager::getPort(){
    PreferenceDataAccessor *accessor = new PreferenceDataAccessor(getAbsoluteSettingFilePath());
    int port = accessor->getPort();
    return port;
}

QString PreferenceManager::initializeToDefault(){
    QString domain = AppInfo::SERVER_DEFAULT_DOMAIN;
    int port = AppInfo::SERVER_DEFAULT_PORT;
    PreferenceDataAccessor *accessor = new PreferenceDataAccessor(getAbsoluteSettingFilePath());
    accessor->update(domain, port);
    messageBroker_m->messagePreferenceManager_updated();
    return "Initialization Success";
}

QString PreferenceManager::update(QString domain, int port){
    domain = domain.trimmed();

    //domain allows only alphabet and - and .
    QRegExp regex("^[A-Za-z0-9\\-\\.]+$");
    if(regex.indexIn(domain) < 0){
        return QString("domain name %1 have problem. ignore.").arg(domain);
    }

    bool inRange = (0 < port) && (port <= 65535);
    if(!inRange){
        return QString("port number %1 isn't in port range. ignore.").arg(QString::number(port));
    }

    PreferenceDataAccessor *accessor = new PreferenceDataAccessor(getAbsoluteSettingFilePath());
    accessor->update(domain, port);
    messageBroker_m->messagePreferenceManager_updated();
    return "Update Success.";

}
