#ifndef MWC_PROGRESSDIALOG_H
#define MWC_PROGRESSDIALOG_H

#include <QtGui>
#include <QtWidgets>
#include "core_messagebroker.h"
#include "log_abstractlogparser.h"

class ProgressDialog : QProgressDialog
{
    Q_OBJECT
public:
    ProgressDialog(QWidget *parent, MessageBroker *MessageBroker);
    void connectParser(AbstractLogParser *parser);

private:
    static const QString INITIAL_TEXT;
    static const QString CANCEL_TEXT;
    static const int MIN_PROGRESS;
    static const int MAX_PROGRESS;

    MessageBroker *messageBroker_m;

private slots:
    void setProgressMaximum(int max);
    void setProgressValue(int value);
    void setProgressString(QString string);
    void progressCanceld();
    void creationComplete();
};

#endif // MWC_PROGRESSDIALOG_H
