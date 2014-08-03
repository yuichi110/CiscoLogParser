#ifndef WINDOW_JSONTESTWIDGET_H
#define WINDOW_JSONTESTWIDGET_H

#include <QtGui>
#include <QtWidgets>
#include "core_appinfo.h"
#include "window_jsontextedit.h"
#include "json_jsonparser.h"

class JsonTestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JsonTestWidget();
    void clear();

private:
    JsonTextEdit *jsonTextEdit_m;
    QLabel *resultLabel_m;

signals:

public slots:
    void sampleButtonClicked();
    void checkButtonClicked();
};

#endif // WINDOW_JSONTESTWIDGET_H
