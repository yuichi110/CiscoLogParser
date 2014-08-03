#include "mwc_progressdialog.h"

const QString ProgressDialog::INITIAL_TEXT = "";
const QString ProgressDialog::CANCEL_TEXT = "cancel";
const int ProgressDialog::MIN_PROGRESS = 0;
const int ProgressDialog::MAX_PROGRESS = 100;

ProgressDialog::ProgressDialog(QWidget *parent, MessageBroker *messageBroker) :
    QProgressDialog(INITIAL_TEXT, CANCEL_TEXT, MIN_PROGRESS, MAX_PROGRESS, parent)
{
    messageBroker_m = messageBroker;
    setFixedSize(AppInfo::PROGRESS_DIALOG_WIDTH, AppInfo::PROGRESS_DIALOG_HEIGHT);
}

void ProgressDialog::connectParser(AbstractLogParser *parser){
    if(AppInfo::DEBUG_PROGRESS_DIALOG) qDebug() << "ProgressDialog::connectParser()";
    disconnect(this);
    connect(parser, SIGNAL(signalSetProgressMaximumValue(int)), this, SLOT(setProgressMaximum(int)));
    connect(parser, SIGNAL(signalSetProgressValue(int)), this, SLOT(setProgressValue(int)));
    connect(parser, SIGNAL(signalSetProgressString(QString)), this, SLOT(setProgressString(QString)));
    connect(parser, SIGNAL(finished()), this, SLOT(creationComplete()));
}

void ProgressDialog::setProgressMaximum(int max){
    if(AppInfo::DEBUG_PROGRESS_DIALOG) qDebug() << "ProgressDialog::setProgressMaximum()";
    setMaximum(max);
}

void ProgressDialog::setProgressValue(int value){
    if(AppInfo::DEBUG_PROGRESS_DIALOG) qDebug() << "ProgressDialog::setProgressValue()";
    setValue(value);
}

void ProgressDialog::setProgressString(QString string){
    if(AppInfo::DEBUG_PROGRESS_DIALOG) qDebug() << "ProgressDialog::setProgressString()";
    setLabelText(string);
    update();
}

void ProgressDialog::progressCanceld(){
    if(AppInfo::DEBUG_PROGRESS_DIALOG) qDebug() << "ProgressDialog::progressCanceld()";

}

void ProgressDialog::creationComplete(){
    if(AppInfo::DEBUG_PROGRESS_DIALOG) qDebug() << "ProgressDialog::creationComplete()";
    close();
    disconnect(this);
    messageBroker_m->messageProgressDialog_initialize();
}
