#ifndef CORE_MESSAGEBROKER_H
#define CORE_MESSAGEBROKER_H

#include <QtGui>
#include "core_appinfo.h"
#include "mwc_mainwindow.h"
#include "mwc_productpicker.h"
#include "mwc_dropzone.h"
#include "core_productmanager.h"
#include "log_abstractlogparser.h"
#include "window_windowmanager.h"
#include "core_preferencemanager.h"
#include "window_preferencewidget.h"

class MainWindow;
class DropZone;
class ProductPicker;
class AbstractLogParser;
class ProductManager;
class WindowManager;
class PreferenceManager;
class PreferenceWidget;

class MessageBroker
{
private:
    // utility
    ProductManager *productManager_m;
    WindowManager *windowManager_m;
    PreferenceManager *preferenceManager_m;

    // view
    MainWindow *mainWindow_m;
    ProductPicker *productPicker_m;
    DropZone *dropZone_m;

    // window
    PreferenceWidget *preferenceWidget_m;

public:
    // constructer
    MessageBroker();

    // static
    static void showWarningMessage(QString title, QString contents);
    static void showInformationMessage(QString title, QString contents);

    // register
    void registerMainWindow(MainWindow *mainWindow);
    void registerProductPicker(ProductPicker *productPicker);
    void registerDropZone(DropZone *dropZone);

    void registerProductManager(ProductManager *productManager);
    void registerWindowManager(WindowManager *windowManager);
    void registerPreferenceManager(PreferenceManager *preferenceManager);
    void registerPreferenceWidget(PreferenceWidget *preferenceWidget);

    // mainWindow
    void messageMainWindow_clearDropzoneLogs();
    QList<QString> messageMainWindow_getLogPathList();
    AbstractLogParser *messageMainWindow_getParser();
    bool messageMainWindow_updateJsonFiles();

    // dropZone
    bool messageDropzone_isLogFileOK(QString filePath);
    void messageDropzone_logFileListChanged();

    // productPicker
    QList<QString> messageProductPicker_getProductList();
    void messageProductPicker_selectedItemChanged();

    // menuBar
    void messageMenuBar_appendFilePathList(QList<QString> list);
    void messageMenuBar_openSetCsvFileChoser();
    void messageMenuBar_parse();
    void messageMenuBar_clear();
    void messageMenuBar_openPreferenceWindow();
    void messageMenuBar_openJsonTestWindow();
    void messageMenuBar_openAboutWindow();

    // progressbar
    void messageProgressDialog_initialize();

    // preferenceWidget
    QString messagePreferenceWidget_update(QString domain, int port);
    QString messagePreferenceWidget_initialize();
    QString messagePreferenceWidget_getDomain();
    int messagePreferenceWidget_getPort();

    // preferenceManager
    void messagePreferenceManager_updated();

    // productManager
    QString messageProductManager_getDomain();
    int messageProductManager_getPort();
    QString messageProductManager_getCsvFilePath();
    QList<QString> messageProductManager_getLogFileList();

};

#endif // CORE_MESSAGEBROKER_H
