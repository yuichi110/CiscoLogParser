#include "json_productrule.h"

ProductRule::ProductRule(int majorVersion, int minorVersion, QString product,
                       QList<QString> *groupList, QMap<QString, QList<QString> > *groupRegexMap, QMap<QString, QList<QString> > *groupHighlightMap,
                       QList<QString> *layerList, QMap<QString, QList<QString> > *layerMap)
{
    majorVersion_m = majorVersion;
    minorVersion_m = minorVersion;
    product_m = product;
    groupList_m = groupList;
    groupRegexMap_m = groupRegexMap;
    groupHighlightMap_m = groupHighlightMap;
    layerList_m = layerList;
    layerMap_m = layerMap;
}

int ProductRule::getMajorVersion(){
    return majorVersion_m;
}

int ProductRule::getMinorVersion(){
    return minorVersion_m;
}

QString ProductRule::getProduct(){
    return product_m;
}

QList<QString> *ProductRule::getGroupList(){
    return groupList_m;
}

QMap<QString, QList<QString> > *ProductRule::getGroupRegexMap(){
    return groupRegexMap_m;
}

QMap<QString, QList<QString> > *ProductRule::getGroupHighlightMap(){
    return groupHighlightMap_m;
}

QList<QString> *ProductRule::getLayerList(){
    return layerList_m;
}

QMap<QString, QList<QString> > *ProductRule::getLayerMap(){
    return layerMap_m;
}
