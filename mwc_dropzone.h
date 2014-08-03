#ifndef MWC_DROPZONE_H
#define MWC_DROPZONE_H

#include <QtWidgets>
#include "core_appinfo.h"
#include "core_messagebroker.h"

class MessageBroker;

class DropZone : public QLabel
{
public:
    explicit DropZone(QWidget *parent, MessageBroker *messageBroker);
    QList<QString> getLogList();
    void clearLogPathList();
    void appenLogPathList(QList<QString> logPathList);

private:
    MessageBroker *messageBroker_m;
    QList<QString> logPathList_m;

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    QList<QString> urlsToPathList(QList<QUrl> urls);
    bool checkFilesOK(QList<QString> pathList);
};

#endif // MWC_DROPZONE_H
