#include "core_messagebroker.h"

MessageBroker::MessageBroker()
{
    // utility
    productManager_m = NULL;

    // view
    mainWindow_m = NULL;
    productPicker_m = NULL;
    dropZone_m = NULL;
}

/////////////
///  Static
/////////////

void MessageBroker::showWarningMessage(QString title, QString contents){
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.warning(NULL, title, contents);
}

void MessageBroker::showInformationMessage(QString title, QString contents){
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.information(NULL, title, contents);
}

/////////////
///  Register
/////////////

void MessageBroker::registerMainWindow(MainWindow *mainWindow){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::registerMainWindow()";
    mainWindow_m = mainWindow;
}

void MessageBroker::registerProductPicker(ProductPicker *productPicker){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::registerProductPicker()";
    productPicker_m = productPicker;
}

void MessageBroker::registerDropZone(DropZone *dropZone){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::registerDropZone()";
    dropZone_m = dropZone;
}

void MessageBroker::registerProductManager(ProductManager *productManager){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::registerProductManager()";
    productManager_m = productManager;
}

void MessageBroker::registerWindowManager(WindowManager *windowManager){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::registerWindowManager()";
    windowManager_m = windowManager;
}

void MessageBroker::registerPreferenceManager(PreferenceManager *preferenceManager){
    preferenceManager_m = preferenceManager;
}

void MessageBroker::registerPreferenceWidget(PreferenceWidget *preferenceWidget){
    preferenceWidget_m = preferenceWidget;
}

/////////////
/// MainWindow
//////////////

void MessageBroker::messageMainWindow_clearDropzoneLogs(){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::messageMainWindow_clearDropzoneLogs()";
    dropZone_m->clearLogPathList();
}

QList<QString> MessageBroker::messageMainWindow_getLogPathList(){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::messageMainWindow_getLogPathList()";
    return dropZone_m->getLogList();
}

AbstractLogParser *MessageBroker::messageMainWindow_getParser(){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::messageMainWindow_getParser()";
    QString product = productPicker_m->getSelectedProduct();
    return productManager_m->getParser(product);
}

bool MessageBroker::messageMainWindow_updateJsonFiles(){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::messageMainWindow_updateJsonFiles()";
    return productManager_m->updateJsonFromServer();
}

/////////////
/// DropZone
//////////////

bool MessageBroker::messageDropzone_isLogFileOK(QString filePath){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::messageDropzone_isLogFileOK()";
    QString product = productPicker_m->getSelectedProduct();
    return productManager_m->isLogFileOK(product, filePath);
}

void MessageBroker::messageDropzone_logFileListChanged(){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::messageDropzone_logFileListChanged()";
    mainWindow_m->logListUpdated();
}

/////////////
/// ProductPicker
/////////////

QList<QString> MessageBroker::messageProductPicker_getProductList(){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::messageProductPicker_getProductList()";
    return productManager_m->getProductList();
}

void MessageBroker::messageProductPicker_selectedItemChanged(){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::messageProductPicker_selectedItemChanged()";
    mainWindow_m->chosedProductChanged();
}

/////////////
/// MenuBar
////////////

void MessageBroker::messageMenuBar_appendFilePathList(QList<QString> logPathList){
    dropZone_m->appenLogPathList(logPathList);
}

void MessageBroker::messageMenuBar_openSetCsvFileChoser(){
    mainWindow_m->openCsvFileChoser();
}

void MessageBroker::messageMenuBar_parse(){
    mainWindow_m->startParse();
}

void MessageBroker::messageMenuBar_clear(){
    mainWindow_m->initialize();
}

void MessageBroker::messageMenuBar_openPreferenceWindow(){
    windowManager_m->openPreferenceWindow();
}

void MessageBroker::messageMenuBar_openJsonTestWindow(){
    windowManager_m->openJsonTestWindow();
}

void MessageBroker::messageMenuBar_openAboutWindow(){
    windowManager_m->openAboutWindow();
}

/////////////
/// ProgressBar
/////////////

void MessageBroker::messageProgressDialog_initialize(){
    mainWindow_m->initialize();
}

/////////////
/// PreferenceWidget
/////////////

QString MessageBroker::messagePreferenceWidget_update(QString domain, int port){
    QString resultMessage = preferenceManager_m->update(domain, port);
    return resultMessage;
}

QString MessageBroker::messagePreferenceWidget_initialize(){
    QString resultMessage = preferenceManager_m->initializeToDefault();
    return resultMessage;
}

QString MessageBroker::messagePreferenceWidget_getDomain(){
    return preferenceManager_m->getDomain();
}

int MessageBroker::messagePreferenceWidget_getPort(){
    return preferenceManager_m->getPort();
}

/////////////
/// PreferenceManager
/////////////

void MessageBroker::messagePreferenceManager_updated(){
    preferenceWidget_m->fillFields();
}

/////////////
/// ProductManager
/////////////

QString MessageBroker::messageProductManager_getCsvFilePath(){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::messageProductManager_getCsvFilePath()";
    return mainWindow_m->getDbFilePath();
}

QList<QString> MessageBroker::messageProductManager_getLogFileList(){
    if(AppInfo::DEBUG_MESSAGE_BROKER) qDebug() << "MessageBroker::messageProductManager_getLogFileList()";
    return dropZone_m->getLogList();
}

QString MessageBroker::messageProductManager_getDomain(){
    return preferenceManager_m->getDomain();
}

int MessageBroker::messageProductManager_getPort(){
    return preferenceManager_m->getPort();
}
