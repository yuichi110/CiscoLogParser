#ifndef CORE_PRODUCTMANAGER_H
#define CORE_PRODUCTMANAGER_H

#include <QtGui>
#include "core_appinfo.h"
#include "core_messagebroker.h"
#include "json_productrule.h"
#include "json_jsonparser.h"
#include "log_abstractlogparser.h"

// need to update include files for new parser
#include "log_nexuslogparser.h"

class ProductManager
{

// need to update
public:
    ProductManager(MessageBroker *messageBroker);
    QList<QString> getProductList();
    bool isLogFileOK(QString product, QString filePath);
    AbstractLogParser* getParser(QString product);

private:
    static const QString NEXUS;
    static const QString NEXUS_JSON;

// don't need to update
public:
    bool updateJsonFromServer();
    bool testAllJsonIsOK();

private:
    MessageBroker *messageBroker_m;
    static const QString SERVER_FILE_URL;
    static const QString PRODUCT_LIST_FILE_NAME;
    static const QString JSON_WEB_RELATIVE_PATH;
    static const QString JSON_LOCAL_RELATIVE_PATH;

    ProductRule *getProductRule(QString jsonFileName);
    bool httpGet(QString url, QString savePath);
};

#endif // CORE_PRODUCTMANAGER_H
