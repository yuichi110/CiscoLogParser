#include "json_jsonparser.h"

const QString JsonParser::KEY_MAJOR_VERSION = "major_version";
const QString JsonParser::KEY_MINOR_VERSION = "minor_version";
const QString JsonParser::KEY_PRODUCT = "product";

const QString JsonParser::KEY_GROUP = "group";
const QString JsonParser::KEY_NAME = "name";
const QString JsonParser::KEY_REGEX = "regex";
const QString JsonParser::KEY_HIGHLIGHT = "highlight";

const QString JsonParser::KEY_LAYER = "layer";
const QString JsonParser::KEY_PARENT_NAME = "parent_name";
const QString JsonParser::KEY_CHILD_NAMES = "child_names";

JsonParser::JsonParser()
{
}

ProductRule *JsonParser::getProductRuleFromFile(QString jsonFilePath){
    QString failReason = "";
    QFile file(jsonFilePath);
    if(!file.exists()){
        failReason = QString("File %1 doesn't exist.").arg(jsonFilePath);
        return NULL;
    }

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString text = file.readAll();
    file.close();

    return getProductRuleFromText(text);
}

ProductRule *JsonParser::getProductRuleFromText(QString text){
    int majorVersion = -1;
    int minorVersion = -1;
    QString product = "";
    QList<QString> *groupList = NULL;
    QMap<QString, QList<QString> > *groupRegexMap = NULL;
    QMap<QString, QList<QString> > *groupHighlightMap = NULL;
    QList<QString> *layerList = NULL;
    QMap<QString, QList<QString> > *layerMap = NULL;

    bool success = false;
    QString failReason = "";
    do{
        // convert qstring to json object
        QJsonObject root = QJsonDocument::fromJson(text.toUtf8()).object();
        if(root.count() == 0){
            failReason = QString("json syntax might be wrong.");
            break;
        }

        // root level
        if(!root.contains(KEY_MAJOR_VERSION)) {
            failReason = QString("KEY %1 doesn't exist on root level.").arg(KEY_MAJOR_VERSION);
            break;
        }
        bool majorOK;
        majorVersion = root.value(KEY_MAJOR_VERSION).toString().toInt(&majorOK);
        if(!majorOK){
            failReason = "major version isn't Integer value";
            break;
        }

        if(!root.contains(KEY_MINOR_VERSION)){
            failReason = QString("KEY %1 doesn't exist on root level.").arg(KEY_MINOR_VERSION);
            break;
        }
        bool minorOK;
        minorVersion = root.value(KEY_MINOR_VERSION).toString().toInt(&minorOK);
        if(!minorOK){
            failReason = "minor version isn't Integer value";
            break;
        }

        if(!root.contains(KEY_PRODUCT)) {
            failReason = QString("KEY %1 doesn't exist on root level.").arg(KEY_PRODUCT);
            break;
        }
        product = root.value(KEY_PRODUCT).toString();

        // group
        if(!root.contains(KEY_GROUP)) {
            failReason = QString("KEY %1 doesn't exist on root level.").arg(KEY_GROUP);
            break;
        }
        QJsonArray groupArray = root.value(KEY_GROUP).toArray();
        groupList = getGroupList(groupArray);
        if(groupList == NULL){
            failReason = "Iteration fail on getGroupList()";
            break;
        }
        groupRegexMap = getGroupRegexMap(groupArray);
        if(groupRegexMap == NULL){
            failReason = "Iteration fail on getGroupRegexMap()";
            break;
        }

        groupHighlightMap = getGroupHighlightMap(groupArray);
        if(groupHighlightMap == NULL){
            failReason = "Iteration fail on getGroupHighlightMap()";
            break;
        }

        // layer
        if(!root.contains(KEY_LAYER)) {
            failReason = QString("KEY %1 doesn't exist on root level.").arg(KEY_LAYER);
            break;
        }
        QJsonArray layerArray = root.value(KEY_LAYER).toArray();
        layerList = getLayerList(layerArray);
        if(layerList == NULL){
            failReason = "Iteration fail on getLayerList()";
            break;
        }
        layerMap = getLayerMap(layerArray);
        if(layerMap == NULL){
            failReason = "Iteration fail on getLayerMap()";
            break;
        }

        // all OK.
        success = true;

    }while(false);


    if(success){
        return new ProductRule(majorVersion, minorVersion, product, groupList,
                              groupRegexMap, groupHighlightMap, layerList, layerMap);
    }else{
        qDebug() << failReason;
        return NULL;
    }
}

QList<QString> *JsonParser::getGroupList(QJsonArray groupArray){
    return getList(groupArray, KEY_NAME);
}

QList<QString> *JsonParser::getLayerList(QJsonArray groupArray){
    return getList(groupArray, KEY_PARENT_NAME);
}

QList<QString> *JsonParser::getList(QJsonArray array, QString elem1_key){
    QList<QString> *list = new QList<QString>;
    for(int i=0; i<array.count(); i++){
        QJsonObject json = array[i].toObject();
        if(!json.contains(elem1_key)) return NULL;
        QString elem1 = json.value(elem1_key).toString();
        list->append(elem1);
    }
    return list;
}

QMap<QString, QList<QString> > *JsonParser::getGroupRegexMap(QJsonArray groupArray){
    return getMap(groupArray, KEY_NAME, KEY_REGEX);
}

QMap<QString, QList<QString> > *JsonParser::getGroupHighlightMap(QJsonArray groupArray){
    return getMap(groupArray, KEY_NAME, KEY_HIGHLIGHT);
}

QMap<QString, QList<QString> > *JsonParser::getLayerMap(QJsonArray layerArray){
    return getMap(layerArray, KEY_PARENT_NAME, KEY_CHILD_NAMES);
}

QMap<QString, QList<QString> > *JsonParser::getMap(QJsonArray array, QString elem1_key, QString elem2_key){
    QMap<QString, QList<QString> > *map = new QMap<QString, QList<QString> >;
    for(int i=0; i<array.count(); i++){
        // key
        QJsonObject json = array[i].toObject();
        if(!json.contains(elem1_key)) return NULL;
        QString key = json.value(elem1_key).toString();

        // value
        if(!json.contains(elem2_key)) return NULL;
        QList<QString> list;
        QJsonArray elem2Array = json.value(elem2_key).toArray();
        for(int j=0; j<elem2Array.count(); j++){
            QString elem2 = elem2Array[j].toString();
            list.append(elem2);
        }
        map->insert(key, list);
    }
    return map;
}
