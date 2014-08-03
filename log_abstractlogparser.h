#ifndef ABSTRACTLOGParser_H
#define ABSTRACTLOGParser_H

#include <QtGui>
#include "core_appinfo.h"
#include "json_productrule.h"
#include "dao_clvdataaccessor.h"

class AbstractLogParser : public QThread
{
    Q_OBJECT

public:
    AbstractLogParser(QString dbFilePath, QList<QString> logFileList,
                      ProductRule *productRule);

protected:
    QString dbFilePath_m;
    QList<QString> logFileList_m;
    ProductRule *productRule_m;

    // util
    void writeGroupInfoToCsv(ClvDataAccessor *writer);
    void writeLayerInfoToCsv(ClvDataAccessor *writer);
    void updateCommandToCsv(ClvDataAccessor *writer);

    // signal rapper
    void setMaximumValueOnProgressDialog(int max);
    void setValueOnProgressDialog(int value);
    void setTextOnProgressDialog(QString string);

signals:
    void signalSetProgressMaximumValue(int max);
    void signalSetProgressValue(int value);
    void signalSetProgressString(QString string);

};

#endif // ABSTRACTLOGParser_H
