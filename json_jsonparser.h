#ifndef CORE_JSONPARSER_H
#define CORE_JSONPARSER_H

#include <QtGui>
#include "json_productrule.h"

class JsonParser
{
public:
    static const QString KEY_MAJOR_VERSION;
    static const QString KEY_MINOR_VERSION;
    static const QString KEY_PRODUCT;

    static const QString KEY_GROUP;
    static const QString KEY_NAME;
    static const QString KEY_REGEX;
    static const QString KEY_HIGHLIGHT;

    static const QString KEY_LAYER;
    static const QString KEY_PARENT_NAME;
    static const QString KEY_CHILD_NAMES;


    static ProductRule *getProductRuleFromFile(QString jsonFilePath);
    static ProductRule *getProductRuleFromText(QString text);

private:
    JsonParser();

    // group
    static QList<QString> *getGroupList(QJsonArray groupArray);
    static QMap<QString, QList<QString> > *getGroupRegexMap(QJsonArray groupArray);
    static QMap<QString, QList<QString> > *getGroupHighlightMap(QJsonArray groupArray);

    // layer
    static QList<QString> *getLayerList(QJsonArray layerArray);
    static QMap<QString, QList<QString> > *getLayerMap(QJsonArray layerArray);

    // helper
    static QList<QString> *getList(QJsonArray array, QString elem1_key);
    static QMap<QString, QList<QString> > *getMap(QJsonArray array, QString elem1_key, QString elem2_key);
};

#endif // CORE_JSONPARSER_H
