#include "window_jsontextedit.h"

JsonTextEdit::JsonTextEdit(QWidget *parent) :
    QTextEdit(parent)
{
    this->setAcceptDrops(true);
}

void JsonTextEdit::dragEnterEvent(QDragEnterEvent *event){
    if(isUrlsOK(event->mimeData()->urls())){
        event->acceptProposedAction();
    }
}

void JsonTextEdit::dropEvent(QDropEvent *event){
    QList<QUrl> urls = event->mimeData()->urls();
    if(isUrlsOK(urls)){
        QString path = urls.at(0).toLocalFile();
        QFile file(path);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        this->setText(file.readAll());
    }
}

bool JsonTextEdit::isUrlsOK(QList<QUrl> urls){
    if(urls.count() != 1) return false;
    QString filePath = urls.at(0).toLocalFile();
    QFileInfo fileInfo(filePath);
    if(!fileInfo.exists()) return false;
    if(!fileInfo.isFile()) return false;

    return true;
}
