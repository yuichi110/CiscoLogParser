#include "dao_preferencedataaccessor.h"

const QString PreferenceDataAccessor::CHECK_TABLE_QUERY = "SELECT sql FROM sqlite_master WHERE type='table' AND name='pref'";
const QString PreferenceDataAccessor::DROP_TABLE_QUERY = "DROP TABLE pref";
const QString PreferenceDataAccessor::CREATE_TABLE_QUERY = "CREATE TABLE pref (domain TEXT, port INT)";
const QString PreferenceDataAccessor::INSERT_RAW_QUERY = "INSERT INTO pref VALUES ('%1', %2)";
const QString PreferenceDataAccessor::UPDATE_RAW_QUERY = "UPDATE pref SET domain = '%1', port = %2";
const QString PreferenceDataAccessor::SELECT_QUERY = "SELECT * FROM pref";

const int PreferenceDataAccessor::DOMAIN_INDEX = 0;
const int PreferenceDataAccessor::PORT_INDEX = 1;

PreferenceDataAccessor::PreferenceDataAccessor(QString filePath)
{
    db_m =  QSqlDatabase::addDatabase("QSQLITE");
    db_m.setDatabaseName(filePath);

    // check contents
    correctTable();
}

void PreferenceDataAccessor::correctTable(){
    db_m.open();
    QSqlQuery query;
    bool allOk = true;

    // check Table exists
    do{
        query.exec(CHECK_TABLE_QUERY);
        if(query.next()){
            // check Table syntax
            QString createTableQuery = query.value(0).toString();
            if(createTableQuery != CREATE_TABLE_QUERY){
                allOk = false;
                break;
            }
        }else{
            allOk = false;
            break;
        }

        // check table has 1 or more raws.
        query.exec(SELECT_QUERY);
        if(query.next()){
            //ok
        }else{
            allOk = false;
            break;
        }
    }while(false);

    if(!allOk){
        // This DB File have some problem.
        // initialize it.
        query.exec(DROP_TABLE_QUERY);
        query.exec(CREATE_TABLE_QUERY);
        QString insertQuery = QString(INSERT_RAW_QUERY).arg(AppInfo::SERVER_DEFAULT_DOMAIN,
                                                            QString::number(AppInfo::SERVER_DEFAULT_PORT));
        query.exec(insertQuery);
    }

    db_m.close();
}

QString PreferenceDataAccessor::getItem(int index){
    db_m.open();
    QSqlQuery query;
    query.exec(SELECT_QUERY);
    if(query.next()){
        return query.value(index).toString();
    }

    db_m.close();
    return "";
}

QString PreferenceDataAccessor::getDomain(){
    QString value = getItem(DOMAIN_INDEX);
    if(value == ""){
        value = AppInfo::SERVER_DEFAULT_DOMAIN;
    }

    return value;
}

int PreferenceDataAccessor::getPort(){
    QString value = getItem(PORT_INDEX);
    qDebug() << value;
    bool ok;
    int port = value.toInt(&ok);
    if(!ok){
        port = AppInfo::SERVER_DEFAULT_PORT;
    }

    bool inRange = ((0 < port) && (port < 65000));
    if(!inRange){
        port = AppInfo::SERVER_DEFAULT_PORT;
    }

    return port;
}

void PreferenceDataAccessor::update(QString domain, int port){
    QString updateQuery = QString(UPDATE_RAW_QUERY).arg(domain, QString::number(port));

    db_m.open();
    QSqlQuery query;
    query.exec(updateQuery);
    db_m.close();
}
