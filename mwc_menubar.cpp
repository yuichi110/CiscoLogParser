#include "mwc_menubar.h"

MenuBar::MenuBar(QWidget *parent, MessageBroker *messageBroker) :
    QMenuBar(parent)
{
    messageBroker_m = messageBroker;

    // Preference
    QMenu *prefMenu = addMenu("Preference");
    QAction *actionPreference = new QAction("Setting", parent);
    connect(actionPreference, SIGNAL(triggered()), this, SLOT(openPreferenceClicked()));
    prefMenu->addAction(actionPreference);
    QAction *actionAbout = new QAction("About CLP", parent);
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(openAboutClicked()));
    prefMenu->addAction(actionAbout);

    // File
    QMenu *fileMenu = addMenu("File");
    QAction *actionSetLogs = new QAction("Set Logs", parent);
    connect(actionSetLogs, SIGNAL(triggered()), this, SLOT(setLogsClicked()));
    fileMenu->addAction(actionSetLogs);

    QAction *actionParse = new QAction("Parse", parent);
    connect(actionParse, SIGNAL(triggered()), this, SLOT(parseClicked()));
    fileMenu->addAction(actionParse);
    QAction *actionClear = new QAction("Clear", parent);
    connect(actionClear, SIGNAL(triggered()), this, SLOT(clearClicked()));
    fileMenu->addAction(actionClear);

    // Window
    QMenu *windowMenu = addMenu("Window");
    QAction *actionMinimize = new QAction("Minimize", parent);
    connect(actionMinimize, SIGNAL(triggered()), this, SLOT(minimizeClicked()));
    windowMenu->addAction(actionMinimize);
    QAction *actionJson = new QAction("Open Json Tester", parent);
    connect(actionJson, SIGNAL(triggered()), this, SLOT(openJsonTesterClicked()));
    windowMenu->addAction(actionJson);

    // Help
    QMenu *helpMenu = addMenu("Help");
    QAction *actionOpenHelp = new QAction("Open help page", parent);
    connect(actionOpenHelp, SIGNAL(triggered()), this, SLOT(openHelpPageClicked()));
    helpMenu->addAction(actionOpenHelp);
    QAction *actionReportNewBug = new QAction("Report new bug", parent);
    connect(actionReportNewBug, SIGNAL(triggered()), this, SLOT(reportNewBugClicked()));
    helpMenu->addAction(actionReportNewBug);
    QAction *actionContact = new QAction("Contact to author", parent);
    connect(actionContact, SIGNAL(triggered()), this, SLOT(contactToAuthorClicked()));
    helpMenu->addAction(actionContact);
    QAction *actionUpdateRule = new QAction("Update Categorize rule", parent);
    connect(actionUpdateRule, SIGNAL(triggered()), this, SLOT(updateCategorizeRuleClicked()));
    helpMenu->addAction(actionUpdateRule);
    QAction *actionCheckUpdate = new QAction("Check software update", parent);
    connect(actionCheckUpdate, SIGNAL(triggered()), this, SLOT(checkSoftwareUpdateClicked()));
    helpMenu->addAction(actionCheckUpdate);
}

// preference
void MenuBar::openPreferenceClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::openPreferenceClicked()";
    messageBroker_m->messageMenuBar_openPreferenceWindow();
}

void MenuBar::openAboutClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::openAboutClicked()";
    messageBroker_m->messageMenuBar_openAboutWindow();
}

// edit

void MenuBar::setLogsClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::setLogsClicked()";

    /*
     *  Need implementation here
     */
    QString dirPath = QDir::homePath();
    QFileDialog fd(this, "Log Files", dirPath);
    fd.setFileMode(QFileDialog::ExistingFiles);
    fd.setAcceptMode(QFileDialog::AcceptOpen);
    if(!fd.exec()){
        return;
    }

    QStringList slist = fd.selectedFiles();
    QList<QString> list;
    foreach(QString path, slist){
        list.append(path);
    }

    messageBroker_m->messageMenuBar_appendFilePathList(list);
}

/*
void MenuBar::setCsvFileClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::setCsvFileClicked()";
    messageBroker_m->messageMenuBar_openSetCsvFileChoser();
}
*/

void MenuBar::parseClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::parseClicked()";
    messageBroker_m->messageMenuBar_parse();
}

void MenuBar::clearClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::clearClicked()";
    messageBroker_m->messageMenuBar_clear();
}

// window

void MenuBar::minimizeClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::minimizeClicked()";
    QWidget *mainWindow = parentWidget();
    if(mainWindow->isMinimized()){
        mainWindow->showNormal();
    }else{
        mainWindow->showMinimized();
    }
}

void MenuBar::openJsonTesterClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::openJsonTesterClicked()";
    messageBroker_m->messageMenuBar_openJsonTestWindow();
}

// help

void MenuBar::openHelpPageClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::openHelpPageClicked()";
    QDesktopServices::openUrl(AppInfo::WEB_PAGE_URL);
}

void MenuBar::reportNewBugClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::reportNewBugClicked()";
    QString url = QString(AppInfo::REPORT_BUG_URL).arg(AppInfo::MAIL_ADDRESS, QString::number(AppInfo::MAJOR_VERSION),
                                                       QString::number(AppInfo::MINOR_VERSION));
    qDebug() << url;
    url = url.replace(" ", "%20");
    qDebug() << url;
    QDesktopServices::openUrl(url);
}

void MenuBar::contactToAuthorClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::reportNewBugClicked()";
    QString url = QString(AppInfo::CONTACT_URL).arg(AppInfo::MAIL_ADDRESS);
    QDesktopServices::openUrl(url);
}

void MenuBar::updateCategorizeRuleClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::updateCategorizeRuleClicked()";
    messageBroker_m->messageMainWindow_updateJsonFiles();
}

void MenuBar::checkSoftwareUpdateClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::checkSoftwareUpdateClicked()";

    // update file on the server has
    // X.Y
    // on top line.
    // where X is majorversion and Y is minorversion
    // the path is
    // http://DOMAIN/version/latest

    QString url = "http://clp.yuichi.com/version/latest";
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply *reply = mgr.get(QNetworkRequest(QUrl(url)));
    eventLoop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        MessageBroker::showWarningMessage("Warning", "Unable to get version information from server.");
        return;
    }

    QString text = reply->readAll();
    QStringList slist = text.split("\n");
    QString versionText = slist.at(0);
    QRegExp regex("(\\d+)\\.(\\d+)");
    if(regex.indexIn(versionText) < 0){
        MessageBroker::showWarningMessage("Warning", "CLP can access to server. But unable to get version information.");
        return;
    }

    int majorVersion = regex.cap(1).toInt();
    int minorVersion = regex.cap(2).toInt();
    bool isLatest = true;
    if(majorVersion > AppInfo::MAJOR_VERSION){
        isLatest = false;
    }else if(majorVersion == AppInfo::MAJOR_VERSION){
        if(minorVersion > AppInfo::MINOR_VERSION){
            isLatest = false;
        }
    }

    if(isLatest){
        QString message = QString("You are using latest version.\nVersion: %1.%2").arg(QString::number(AppInfo::MAJOR_VERSION),
                                                                       QString::number(AppInfo::MINOR_VERSION));
        MessageBroker::showInformationMessage("OK", message);
    }else{
        QString message = QString("Your Application isn't latest.\nLatest version is %1.%2.").arg(QString::number(majorVersion),
                                                                                                 QString::number(minorVersion));
        MessageBroker::showWarningMessage("Warning", message);
    }
}
