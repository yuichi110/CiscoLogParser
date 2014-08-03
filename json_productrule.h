#ifndef CORE_PRODUCTRULE_H
#define CORE_PRODUCTRULE_H

#include <QtGui>

class ProductRule
{
public:
    ProductRule(int majorVersion, int minorVersion, QString product,
               QList<QString> *groupList, QMap<QString, QList<QString> > *groupRegexMap, QMap<QString, QList<QString> > *groupHeighlightMap,
               QList<QString> *layerList, QMap<QString, QList<QString> > *layerMap);

    int getMajorVersion();
    int getMinorVersion();
    QString getProduct();
    QList<QString> *getGroupList();
    QMap<QString, QList<QString> > *getGroupRegexMap();
    QMap<QString, QList<QString> > *getGroupHighlightMap();
    QList<QString> *getLayerList();
    QMap<QString, QList<QString> > *getLayerMap();

private:
    int majorVersion_m;
    int minorVersion_m;
    QString product_m;

    QList<QString> *groupList_m;
    QMap<QString, QList<QString> > *groupRegexMap_m;
    QMap<QString, QList<QString> > *groupHighlightMap_m;
    QList<QString> *layerList_m;
    QMap<QString, QList<QString> > *layerMap_m;
};

#endif // CORE_PRODUCTRULE_H
