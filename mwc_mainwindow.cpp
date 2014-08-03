#include "mwc_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    if(AppInfo::DEBUG_MAIN_WINDOW) qDebug() << "MainWindow::MainWindow()";
    // message broker
    messageBroker_m = new MessageBroker();
    messageBroker_m->registerMainWindow(this);
    clvFilePath_m = "";

    // utility
    new PreferenceManager(messageBroker_m);
    new ProductManager(messageBroker_m);
    new WindowManager(this, messageBroker_m);

    // initialize window
    setWindowIcon(QIcon(AppInfo::APP_ICON));
    setWindowTitle(AppInfo::APP_NAME);
    setFixedSize(AppInfo::WINDOW_WIDTH, AppInfo::WINDOW_HEIGHT);

    QWidget *centerWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centerWidget);
    mainLayout->setContentsMargins(AppInfo::WINDOW_MARGIN,AppInfo::WINDOW_MARGIN,
                                   AppInfo::WINDOW_MARGIN,AppInfo::WINDOW_MARGIN);
    mainLayout->setSpacing(AppInfo::WINDOW_SPACING);
    mainLayout->addLayout(createTopParts());
    mainLayout->addLayout(createBottomParts());
    centerWidget->setLayout(mainLayout);
    setCentralWidget(centerWidget);

    // menu
    MenuBar *mainMenuBar = new MenuBar(this, messageBroker_m);
    setMenuBar(mainMenuBar);

    // progressDialog
    progressDialog_m = new ProgressDialog(this, messageBroker_m);
}

QHBoxLayout *MainWindow::createTopParts(){
    if(AppInfo::DEBUG_MAIN_WINDOW) qDebug() << "MainWindow::createTopParts()";

    QVBoxLayout *left = new QVBoxLayout();
    left->setSpacing(2);
    QLabel *leftLabel = new QLabel("Chose Product", this);
    leftLabel->setStyleSheet("border: 1px solid grey");
    productPicker_m = new ProductPicker(this, messageBroker_m);
    left->addWidget(leftLabel);
    left->addWidget(productPicker_m);

    QVBoxLayout *right = new QVBoxLayout();
    right->setSpacing(0);
    right->setContentsMargins(0,0,0,0);
    dropZone_m = new DropZone(this, messageBroker_m);
    dropZone_m->setFixedSize(AppInfo::DROP_ZONE_WIDTH, AppInfo::DROP_ZONE_HEIGHT);
    fileNameLabel_m = new QLabel(this);
    fileNameLabel_m->setWordWrap(true);
    fileNameLabel_m->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    fileNameLabel_m->setStyleSheet("border: 1px solid grey");
    logListUpdated();
    right->addWidget(dropZone_m);
    right->addWidget(fileNameLabel_m);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addLayout(left);
    topLayout->addLayout(right);
    return topLayout;
}

QHBoxLayout *MainWindow::createBottomParts(){
    if(AppInfo::DEBUG_MAIN_WINDOW) qDebug() << "MainWindow::createBottomParts()";

    QPushButton *clearButton = new QPushButton("Clear Log Files", this);
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));
    QPushButton *parseButton = new QPushButton("Parse and Export", this);
    connect(parseButton, SIGNAL(clicked()), this, SLOT(parseButtonClicked()));

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->setContentsMargins(0,0,0,0);
    bottomLayout->setAlignment(Qt::AlignRight);
    bottomLayout->addWidget(clearButton);
    bottomLayout->addWidget(parseButton);
    return bottomLayout;
}

MainWindow::~MainWindow()
{
    if(AppInfo::DEBUG_MAIN_WINDOW) qDebug() << "MainWindow::~MainWindow()";
}

QString MainWindow::openCsvFileChoser(){

    QList<QString> list = messageBroker_m->messageMainWindow_getLogPathList();
    if(list.count() < 1){
        MessageBroker::showWarningMessage("Warning", "Please chose parse files first.");
        return "";
    }

    QFileInfo fileInfo(list.at(0));
    QString dirPath = fileInfo.absoluteDir().absolutePath();
    QFileDialog fd(this, "CLV File Name", dirPath);
    fd.setFileMode(QFileDialog::AnyFile);
    fd.setNameFilter("Cisco Log Viewer file (*.clv)");
    fd.setAcceptMode(QFileDialog::AcceptSave);
    if(!fd.exec()){
        return "";
    }

    QString path = fd.selectedFiles().at(0);
    return path;
}


QString MainWindow::getDbFilePath(){
    return clvFilePath_m;
}


void MainWindow::startParse(){
    QList<QString> logList = messageBroker_m->messageMainWindow_getLogPathList();
    if(logList.count() < 1){
        MessageBroker::showWarningMessage("Warning", "Logs are not set.");
        return;
    }

    QString dbPath = openCsvFileChoser();
    clvFilePath_m = dbPath;
    if(dbPath == ""){
        return;
    }

    AbstractLogParser *parser = messageBroker_m->messageMainWindow_getParser();
    if(parser == NULL){
        MessageBroker::showWarningMessage("Warning", "Parser have problem. Please update rule via help menu.");
        return;
    }

    progressDialog_m->connectParser(parser);
    parser->start();
}

void MainWindow::logListUpdated(){
    if(AppInfo::DEBUG_MAIN_WINDOW) qDebug() << "MainWindow::logListUpdated()";

    QList<QString> list = messageBroker_m->messageMainWindow_getLogPathList();
    QString text = "File Names:\n";
    foreach(QString logPath, list){
        qDebug() << logPath;
        QFileInfo fileInfo(logPath);
        if(!fileInfo.exists()){
            continue;
        }else{
            QString fileName = fileInfo.fileName();
            text += QString("%1, ").arg(fileName);
        }
    }
    fileNameLabel_m->setText(text);
}

void MainWindow::chosedProductChanged(){
    if(AppInfo::DEBUG_MAIN_WINDOW) qDebug() << "MainWindow::chosedProductChanged()";
    initialize();
}

void MainWindow::initialize(){
    if(AppInfo::DEBUG_MAIN_WINDOW) qDebug() << "MainWindow::initialize()";
    messageBroker_m->messageMainWindow_clearDropzoneLogs();
    clvFilePath_m = "";
}


///////////
/// GUI Event on MainWindow
/// ProductPicker and DropZone have own imlementation
///////////

void MainWindow::clearButtonClicked(){
    if(AppInfo::DEBUG_MAIN_WINDOW) qDebug() << "MainWindow::clearButtonClicked()";
    initialize();
}

void MainWindow::parseButtonClicked(){
    if(AppInfo::DEBUG_MAIN_WINDOW) qDebug() << "MainWindow::parseButtonClicked()";
    startParse();
}
