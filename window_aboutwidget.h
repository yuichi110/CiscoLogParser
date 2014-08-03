#ifndef WINDOW_ABOUTWIDGET_H
#define WINDOW_ABOUTWIDGET_H

#include <QtGui>
#include <QtWidgets>
#include "core_appinfo.h"

class AboutWidget : public QWidget
{
    Q_OBJECT
public:
    static AboutWidget *getInstance();

private:
    explicit AboutWidget();

signals:

public slots:

};

#endif // WINDOW_ABOUTWIDGET_H
