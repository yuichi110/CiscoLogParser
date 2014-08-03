#ifndef LOG_NEXUSLOGParser_H
#define LOG_NEXUSLOGParser_H

#include <QtGui>
#include <QtSql>
#include "core_appinfo.h"
#include "log_abstractlogparser.h"
#include "dao_clvdataaccessor.h"
#include "json_productrule.h"

class NexusLogParser : public AbstractLogParser
{
    //Q_OBJECT

public:
    NexusLogParser(QString dbFilePath, QList<QString> logFileList,
                   ProductRule *productRule);
    static bool isLogOK(QString logPath);

    void run();
    bool parseLog(ClvDataAccessor *writer, QString logFilePath, int startProgress, int endProgress);
    int countCommand(QString logFilePath);

private:
    static const QString NEXUS;
    static const int PROGRESS_MAX;
    static const int PROGRESS_STEP0;
    static const int PROGRESS_STEP1;
    static const int PROGRESS_STEP2;
    static const int PROGRESS_STEP3;
    static const int PROGRESS_STEP4;
    static const double PROGRESS_COMMAND_COUNT_RATIO;

};

#endif // LOG_NEXUSLOGParser_H
