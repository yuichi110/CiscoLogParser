#ifndef WINDOW_JSONTEXTEDIT_H
#define WINDOW_JSONTEXTEDIT_H

#include <QtGui>
#include <QtWidgets>

class JsonTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit JsonTextEdit(QWidget *parent = 0);

private:
    bool isUrlsOK(QList<QUrl> urls);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

signals:

public slots:

};

#endif // WINDOW_JSONTEXTEDIT_H
