#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include "core_appinfo.h"
#include "core_messagebroker.h"
#include "mwc_productpicker.h"
#include "mwc_dropzone.h"
#include "mwc_menubar.h"
#include "mwc_progressdialog.h"
#include "window_windowmanager.h"

class MessageBroker;
class ProductManager;
class WindowManager;
class ProductPicker;
class DropZone;
class ProgressDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void logFileListChanged();
    ~MainWindow();

    QString openCsvFileChoser();
    QString getDbFilePath();
    void startParse();
    void initialize();

    // notification
    void logListUpdated();
    void chosedProductChanged();

private:
    MessageBroker *messageBroker_m;
    QLabel *fileNameLabel_m;
    QString clvFilePath_m;
    ProgressDialog *progressDialog_m;
    ProductPicker *productPicker_m;
    DropZone *dropZone_m;
    ProductManager *productManager_m;

    QHBoxLayout *createTopParts();
    QHBoxLayout *createBottomParts();

private slots:
    // button
    void clearButtonClicked();
    void parseButtonClicked();

};

#endif // MAINWINDOW_H
