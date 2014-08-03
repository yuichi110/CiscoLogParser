#include "core_productmanager.h"

////////////////////////////////
/// NEED TO UPDATE FROM HERE ///
////////////////////////////////

// please update from here
const QString ProductManager::NEXUS = "Nexus";
const QString ProductManager::NEXUS_JSON = "nexus.json";

// new products

QList<QString> ProductManager::getProductList(){
    QList<QString> list;

    // please update
    list.append(NEXUS);
    // append new product

    return list;
}

bool ProductManager::isLogFileOK(QString product, QString filePath){
    // please update from here
    if(product == NEXUS){
        return NexusLogParser::isLogOK(filePath);
    }
    // "else if" for new product

    return false;
}

AbstractLogParser* ProductManager::getParser(QString product){
    AbstractLogParser *parser = NULL;
    QString dbFilePath = messageBroker_m->messageProductManager_getCsvFilePath();
    QList<QString> logFileList = messageBroker_m->messageProductManager_getLogFileList();

    // please update from here
    if(product == NEXUS){
        ProductRule *rule = getProductRule(NEXUS_JSON);
        if(rule != NULL) parser = new NexusLogParser(dbFilePath, logFileList, rule);
    }
    // "else if" for new product

    if(parser == NULL){
        qDebug() << "";
        qDebug() << "FATAL ERROR.";
        qDebug() << QString("%1 is not defined or having problem in jsonfile.").arg(product);
        qDebug() << "";
    }

    return parser;
}


//////////////////////////////////////
/// DON'T NEED TO UPDATE FROM HERE ///
//////////////////////////////////////


const QString ProductManager::SERVER_FILE_URL = "http://%1:%2/json/%3/%4";
const QString ProductManager::PRODUCT_LIST_FILE_NAME = "productlist";
const QString ProductManager::JSON_WEB_RELATIVE_PATH = "/json-web/%1";
const QString ProductManager::JSON_LOCAL_RELATIVE_PATH = "/json-local/%1";
ProductManager::ProductManager(MessageBroker *messageBroker)
{
    messageBroker_m = messageBroker;
    messageBroker_m->registerProductManager(this);
}

bool ProductManager::updateJsonFromServer(){
    // server
    QString domain = messageBroker_m->messageProductManager_getDomain();
    QString port = QString::number(messageBroker_m->messageProductManager_getPort());
    QString majorVersion = QString::number(AppInfo::MAJOR_VERSION);
    QString listfileUrl = QString(SERVER_FILE_URL).arg(domain, port, majorVersion, PRODUCT_LIST_FILE_NAME);

    // local file
    QString saveAbsolutePath = QCoreApplication::applicationDirPath() + JSON_WEB_RELATIVE_PATH;
    QString listfileSavePath = QString(saveAbsolutePath).arg(PRODUCT_LIST_FILE_NAME);
    bool listSuccess = httpGet(listfileUrl, listfileSavePath);

    if(!listSuccess) {
        qDebug() << "Unable to get listfile from server.";
        MessageBroker::showWarningMessage("Warning", "Unable to get listfile from server.");
        return false;
    }

    QFileInfo fileInfo(listfileSavePath);
    if(!fileInfo.exists()) {
        MessageBroker::showWarningMessage("Warning", "CLP can access to Server. But unable to write listfile to local");
        qDebug() << "Unable to write listfile";
        return false;
    }

    QString resultText = "";
    bool allSuccess = true;
    QFile file(listfileSavePath);
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd()){
        QString jsonFileName = file.readLine().trimmed();
        QString productUrl = QString(SERVER_FILE_URL).arg(domain, port, majorVersion, jsonFileName);
        QString localPath = QString(saveAbsolutePath).arg(jsonFileName);
        bool success = httpGet(productUrl, localPath);

        QString productName = jsonFileName.replace(".json", "");
        if(!success){
            allSuccess = false;
            resultText += QString("%1 : update fail.\n").arg(productName);
        }else{
            resultText += QString("%1 : update success.\n").arg(productName);
        }
    }

    QString messageTemplate = "All updates %1.\n------------------\n%2------------------";
    if(allSuccess){
        MessageBroker::showInformationMessage("OK", messageTemplate.arg("success", resultText));
    }else{
        MessageBroker::showWarningMessage("Warning", messageTemplate.arg("fail", resultText));
    }

    return allSuccess;
}

bool ProductManager::httpGet(QString url, QString savePath){
    // network setup
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply *reply = mgr.get(QNetworkRequest(QUrl(url)));
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        // success to get file from server.

        // read contents and check syntax if it is jsonfile.
        QString text = reply->readAll();
        if(url.endsWith(".json")){
            ProductRule *rule = JsonParser::getProductRuleFromText(text);
            if(rule == NULL){
                // json syntax error. don't update local file.
                delete reply;
                return false;
            }
        }

        // make parent dir
        QFileInfo fileInfo(savePath);
        QString parentDir = fileInfo.dir().path();
        QDir::current().mkpath(parentDir);

        // write file
        QFile file(savePath);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << text;
        file.close();

        delete reply;
        return true;

    }else{
        //failure
        qDebug() << "Failure Reason: " << reply->errorString();
        delete reply;
        return false;
    }
}

ProductRule *ProductManager::getProductRule(QString jsonFileName){
    // web saved path
    QString webJsonTempPath = QCoreApplication::applicationDirPath() + JSON_WEB_RELATIVE_PATH;
    QString webJsonAbsPath = QString(webJsonTempPath).arg(jsonFileName);

    // local path
    QString localJsonTempPath = QCoreApplication::applicationDirPath() + JSON_LOCAL_RELATIVE_PATH;
    QString localJsonAbsPath = QString(localJsonTempPath).arg(jsonFileName);

    QFile file1(webJsonAbsPath);
    if(file1.exists()){
        ProductRule *rule = JsonParser::getProductRuleFromFile(webJsonAbsPath);
        if(rule != NULL){
            return rule;
        }else{
            qDebug() << QString("online updated json %1 have some error").arg(jsonFileName);
        }
    }

    QFile file2(localJsonAbsPath);
    if(file2.exists()){
        ProductRule *rule = JsonParser::getProductRuleFromFile(localJsonAbsPath);
        if(rule != NULL){
            return rule;
        }else{
            qDebug() << QString("embeded json %1 have some error").arg(jsonFileName);
        }
    }

    // this code must not be called.
    // please test json by function "testAllJsonFileOK" before you deploy this app.
    qDebug();
    qDebug() << "Fatal Error";
    qDebug() << QString("json %1 doesn't exist or having syntax error").arg(jsonFileName);
    qDebug();
    return NULL;
}
