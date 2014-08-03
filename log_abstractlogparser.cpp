#include "log_abstractlogparser.h"

AbstractLogParser::AbstractLogParser(QString dbFilePath, QList<QString> logFileList,
                                     ProductRule *productRule) : QThread()
{
    dbFilePath_m = dbFilePath;
    logFileList_m = logFileList;
    productRule_m = productRule;
}

void AbstractLogParser::writeGroupInfoToCsv(ClvDataAccessor *writer){
    if(AppInfo::DEBUG_LOG_PARSER) qDebug() << "AbstractLogParser::writeGroupInfoToCsv()";
    QList<QString> *groupList = productRule_m->getGroupList();
    QMap<QString, QList<QString> > *groupRegexMap = productRule_m->getGroupRegexMap();
    QMap<QString, QList<QString> > *groupHighlightMap = productRule_m->getGroupHighlightMap();
    foreach(QString group, *groupList){
        if(groupRegexMap->contains(group) && groupHighlightMap->contains(group)){
            QList<QString> regexList = groupRegexMap->value(group);
            QList<QString> highlightList = groupHighlightMap->value(group);
            writer->writeGroupDefinition(group, regexList, highlightList);
        }else{
            qDebug() << QString("Error: regex map doesn't have key '%1'").arg(group);
        }
    }
}

void AbstractLogParser::writeLayerInfoToCsv(ClvDataAccessor *writer){
    if(AppInfo::DEBUG_LOG_PARSER) qDebug() << "AbstractLogParser::writeLayerInfoToCsv()";
    QList<QString> *layerList = productRule_m->getLayerList();
    QMap<QString, QList<QString> > *layerMap = productRule_m->getLayerMap();
    foreach(QString layer, *layerList){
        if(layerMap->contains(layer)){
            QList<QString> childList = layerMap->value(layer);
            writer->writeLayerDefinition(layer, childList);
        }else{
            qDebug() << QString("Error: layer map doesn't have key '%1'").arg(layer);
        }
    }
}

void AbstractLogParser::updateCommandToCsv(ClvDataAccessor *writer){
    if(AppInfo::DEBUG_LOG_PARSER) qDebug() << "AbstractLogParser::updateCommandToCsv()";

    QList<QString> *layerList = productRule_m->getLayerList();
    QMap<QString, QList<QString> > *layerMap = productRule_m->getLayerMap();

    foreach(QString layer, *layerList){
        if(!layerMap->contains(layer)){
            continue;
        }
        QList<QString> groupList = layerMap->value(layer);
        foreach(QString group, groupList){
            QList<int> commandIdList = writer->getIdListFromGroup(group);
            writer->updateCommand(layer, group, commandIdList);
        }
    }
}

void AbstractLogParser::setMaximumValueOnProgressDialog(int max){
    if(AppInfo::DEBUG_LOG_PARSER) qDebug() << "AbstractLogParser::setMaximumValueOnProgressDialog(): " << max;
    emit signalSetProgressMaximumValue(max);
}

void AbstractLogParser::setValueOnProgressDialog(int value){
    if(AppInfo::DEBUG_LOG_PARSER) qDebug() << "AbstractLogParser::setValueOnProgressDialog: " << value;
    emit signalSetProgressValue(value);
}

void AbstractLogParser::setTextOnProgressDialog(QString string){
    if(AppInfo::DEBUG_LOG_PARSER) qDebug() << "AbstractLogParser::setTextOnProgressDialog(): " << string;
    emit signalSetProgressString(string);
}

