#ifndef DAO_CLVDATAACCESSOR_H
#define DAO_CLVDATAACCESSOR_H

#include <QtGui>
#include <QtSql>
#include "core_appinfo.h"

class ClvDataAccessor
{
public:
    // BASIC
    ClvDataAccessor(QString filePath);
    void open(bool initialize);
    bool isOpen();
    void close();
    void checkTableSyntax(bool initialize);
    void checkTableSyntax2(QString table, QString checkQuery, QString dropQuery, QString createQuery, bool initialize);
    QSqlQuery execSql(QSqlQuery query);
    QString getCurrentDateString();

    // PROJECT INFO
    void writeProjectInfo(QString product);

    // COMMAND
    void writeCommand(QString name, QString decoratedName, QString scope, QString tag, QString file, QByteArray data);
    void updateCommand(QString layer, QString group, QList<int> idList);

    // COMMAND GROUP
    void writeGroupDefinition(QString groupName, QList<QString> regexList, QList<QString> highlightList);
    QList<int> getIdListFromGroup(QString group);

    // LAYER
    void writeLayerDefinition(QString layer, QList<QString> groupList);

    // SEARCH

    // BOOKMARK

    // MEMO

private:
    QSqlDatabase db_m;

    // table project
    static const QString PROJECT_TABLE;
    static const QString PROJECT_CHECK_TABLE;
    static const QString PROJECT_DROP_TABLE;
    static const QString PROJECT_CREATE_TABLE;
    static const QString PROJECT_INSERT_TO_TABLE;

    // table command
    static const QString COMMAND_TABLE;
    static const QString COMMAND_CHECK_TABLE;
    static const QString COMMAND_DROP_TABLE;
    static const QString COMMAND_CREATE_TABLE;
    static const QString COMMAND_INSERT_TO_TABLE;
    static const QString COMMAND_UPDATE_GROUP_RAYER;
    static const QString COMMAND_SELECT_ID_BY_REGEX;
    static const QString COMMAND_SELECT_COMMAND_LAYER_GROUP;


    // table group
    static const QString GROUP_TABLE;
    static const QString GROUP_CHECK_TABLE;
    static const QString GROUP_DROP_TABLE;
    static const QString GROUP_CREATE_TABLE;
    static const QString GROUP_INSERT_TO_TABLE;
    static const QString GROUP_SELECT_COMMAND_ID_BY_GROUP_NAME;

    // table highlight
    static const QString HIGHLIGHT_TABLE;
    static const QString HIGHLIGHT_CHECK_TABLE;
    static const QString HIGHLIGHT_DROP_TABLE;
    static const QString HIGHLIGHT_CREATE_TABLE;
    static const QString HIGHLIGHT_INSERT_TO_TABLE;

    // table layer
    static const QString LAYER_TABLE;
    static const QString LAYER_CHECK_TABLE;
    static const QString LAYER_DROP_TABLE;
    static const QString LAYER_CREATE_TABLE;
    static const QString LAYER_INSERT_TO_TABLE;

    // table search
    static const QString SEARCH1_TABLE;
    static const QString SEARCH1_CHECK_TABLE;
    static const QString SEARCH1_DROP_TABLE;
    static const QString SEARCH1_CREATE_TABLE;
    static const QString SEARCH1_INSERT_TO_TABLE;

    static const QString SEARCH2_TABLE;
    static const QString SEARCH2_CHECK_TABLE;
    static const QString SEARCH2_DROP_TABLE;
    static const QString SEARCH2_CREATE_TABLE;
    static const QString SEARCH2_INSERT_TO_TABLE;

    // table bookmark
    static const QString BOOKMARK_TABLE;
    static const QString BOOKMARK_CHECK_TABLE;
    static const QString BOOKMARK_DROP_TABLE;
    static const QString BOOKMARK_CREATE_TABLE;
    static const QString BOOKMARK_INSERT_TO_TABLE;

    // table memo
    static const QString MEMO_TABLE;
    static const QString MEMO_CHECK_TABLE;
    static const QString MEMO_DROP_TABLE;
    static const QString MEMO_CREATE_TABLE;
    static const QString MEMO_INSERT_TO_TABLE;

    // sql bind tag
    static const QString BIND_MAJOR_VERSION;
    static const QString BIND_MINOR_VERSION;
    static const QString BIND_PRODUCT;
    static const QString BIND_CREATE_DATE;
    static const QString BIND_UPDATE_DATE;
    static const QString BIND_NAME;
    static const QString BIND_DECORATED_NAME;
    static const QString BIND_SCOPE;
    static const QString BIND_TAG;
    static const QString BIND_FILE;
    static const QString BIND_DATA;
    static const QString BIND_COMMAND_ID;
    static const QString BIND_GROUP_NAME;
    static const QString BIND_REGEX;
    static const QString BIND_COLOR;
};

#endif // DAO_CLVDATAACCESSOR_H
