#include "test_componenttester.h"


ComponentTester::ComponentTester()
{
}

void ComponentTester::testPreference(){
    qDebug() << "1: initialize";
    QString dbPath = "/Users/yuichi/Desktop/clp-test.db";
    PreferenceDataAccessor *pref = new PreferenceDataAccessor(dbPath);
    qDebug() << "2: initilize done";
    QString domain = pref->getDomain();
    qDebug() << "3: get domain: " << domain;
    int port = pref->getPort();
    qDebug() << "4: get port: " << port;
    pref->update("helloworld.com", 8888);
    qDebug() << "5: update";
    qDebug() << "  domain: " << pref->getDomain();
    qDebug() << "  port:   " << pref->getPort();

    qDebug() << "\nDone!!\n";
}

void ComponentTester::testDatabase1(){
    QString path = "/Users/yuichi/Desktop/clp-testDatabase2.clv";
    ClvDataAccessor *writer = new ClvDataAccessor(path);
    writer->open(false);
    /*
    writer->writeProjectInfo("TestProduct");
    writer->writeCommand("commandName", "fancyCommandName", "scope", "tag", "hello.txt", QByteArray("TEST DATA"));
    */
    QList<int> idList = writer->getIdListFromGroup("Env");
    writer->updateCommand("Hard", "Env", idList);
    writer->close();
}

int ComponentTester::testDatabase2(int argc, char *argv[]){
    QApplication app(argc, argv);
    QString dbPath = "/Users/yuichi/Desktop/clp-testDatabase2.clv";
    QList<QString> logList;
    QString logPath = "/Users/yuichi/Desktop/show-tech2.txt";
    logList.append(logPath);
    QString jsonFile = "/Users/yuichi/Desktop/nexus.json";
    ProductRule *rule = JsonParser::getProductRuleFromFile(jsonFile);

    qDebug() << "Start parser";
    NexusLogParser *parser = new NexusLogParser(dbPath, logList, rule);
    parser->start();
    return app.exec();
}


