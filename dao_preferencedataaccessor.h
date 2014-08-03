#ifndef PREFERENCEDATAACCESSOR_H
#define PREFERENCEDATAACCESSOR_H

#include <QtSql>
#include "core_appinfo.h"

class PreferenceDataAccessor
{
public:
    PreferenceDataAccessor(QString filePath);
    QString getDomain();
    int getPort();
    void update(QString domain, int port);

private:
    static const QString CHECK_TABLE_QUERY;
    static const QString DROP_TABLE_QUERY;
    static const QString CREATE_TABLE_QUERY;
    static const QString INSERT_RAW_QUERY;
    static const QString UPDATE_RAW_QUERY;
    static const QString SELECT_QUERY;
    static const int DOMAIN_INDEX;
    static const int PORT_INDEX;

    QSqlDatabase db_m;
    void correctTable();
    QString getItem(int index);
};

#endif // PREFERENCEDATAACCESSOR_H
