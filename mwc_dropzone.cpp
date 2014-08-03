#include "mwc_dropzone.h"

DropZone::DropZone(QWidget *parent, MessageBroker *messageBroker) :
    QLabel(parent)
{
    messageBroker_m = messageBroker;
    messageBroker_m->registerDropZone(this);

    QPixmap pic(AppInfo::DROP_ICON);
    QPixmap scaled=pic.scaled (AppInfo::DROP_ZONE_WIDTH, AppInfo::DROP_ZONE_HEIGHT,
                               Qt::IgnoreAspectRatio, Qt::FastTransformation );
    setPixmap(scaled);

    logPathList_m.clear();
    setAcceptDrops(true);
}

QList<QString> DropZone::getLogList(){
    return logPathList_m;
}

void DropZone::clearLogPathList(){
    logPathList_m.clear();
    messageBroker_m->messageDropzone_logFileListChanged();
}

void DropZone::appenLogPathList(QList<QString> logPathList){
    if(!checkFilesOK(logPathList)){
        MessageBroker::showWarningMessage("Warning", "Some Files are not supported.\nPlease chose collect files");
        return;
    }

    bool dupExist = false;
    foreach(QString path, logPathList){
        if(logPathList_m.contains(path)){
            dupExist = true;
        }else{
            logPathList_m.append(path);
        }
    }

    if(dupExist){
        MessageBroker::showInformationMessage("Information", "Some Duplicate files are ignored.");
    }

    messageBroker_m->messageDropzone_logFileListChanged();
}


void DropZone::dragEnterEvent(QDragEnterEvent *event){
    QList<QUrl> urls = event->mimeData()->urls();
    if(checkFilesOK(urlsToPathList(urls))){
        event->acceptProposedAction();
    }
}

void DropZone::dropEvent(QDropEvent *event){
    QList<QUrl> urls = event->mimeData()->urls();
    appenLogPathList(urlsToPathList(urls));

    /*
    if(!checkFilesOK(urls)){
        return;
    }
    foreach(QUrl url, urls) {
        QString path = url.toLocalFile();
        if(!logPathList_m.contains(path)){
            logPathList_m.append(path);
        }
    }
    messageBroker_m->messageDropzone_logFileListChanged();
    */
}

/*
bool DropZone::checkFilesOK(QList<QUrl> urls){
    bool isAllOK = true;
    foreach(QUrl url, urls){
        QString path = url.toLocalFile();
        bool ok = messageBroker_m->messageDropzone_isLogFileOK(path);
        if(!ok){
            isAllOK = false;
            break;
        }
    }
    return isAllOK;
}
*/

QList<QString> DropZone::urlsToPathList(QList<QUrl> urls){
    QList<QString> pathList;
    foreach(QUrl url, urls){
        QString path = url.toLocalFile();
        pathList.append(path);
    }
    return pathList;
}

bool DropZone::checkFilesOK(QList<QString> pathList){
    bool isAllOK = true;
    foreach(QString path, pathList){
        bool ok = messageBroker_m->messageDropzone_isLogFileOK(path);
        if(!ok){
            isAllOK = false;
            break;
        }
    }
    return isAllOK;
}


