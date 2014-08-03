#include "log_nexuslogparser.h"

const int NexusLogParser::PROGRESS_MAX = 100;
const int NexusLogParser::PROGRESS_STEP0 = 0;
const int NexusLogParser::PROGRESS_STEP1 = 5;
const int NexusLogParser::PROGRESS_STEP2 = 90;
const int NexusLogParser::PROGRESS_STEP3 = 92;
const int NexusLogParser::PROGRESS_STEP4 = 95;
const double NexusLogParser::PROGRESS_COMMAND_COUNT_RATIO = 0.1;

NexusLogParser::NexusLogParser(QString dbFilePath, QList<QString> logFileList, ProductRule *productRule) :
    AbstractLogParser(dbFilePath, logFileList, productRule)
{
}

bool NexusLogParser::isLogOK(QString logPath){
    if(AppInfo::DEBUG_LOG_PARSER) qDebug() << "NexusLogParser::isLogOK()";
    QFileInfo fileInfo(logPath);
    if(!fileInfo.exists()) return false;
    if(!fileInfo.isFile()) return false;

    return true;
}

void NexusLogParser::run(){
    if(AppInfo::DEBUG_LOG_PARSER) qDebug() << "NexusLogParser::run()";

    setTextOnProgressDialog("Start making CLV file.");
    setMaximumValueOnProgressDialog(PROGRESS_MAX);
    setValueOnProgressDialog(PROGRESS_STEP0);

    // STEP1 : Write Project Info
    ClvDataAccessor *writer = new ClvDataAccessor(dbFilePath_m);
    writer->open(true);
    writer->writeProjectInfo("Nexus");
    setValueOnProgressDialog(PROGRESS_STEP1);

    // STEP2 : Write Command
    int fileNum = logFileList_m.count(); // must not 0
    int stepValue = (PROGRESS_STEP2 - PROGRESS_STEP1) / fileNum;
    for(int i=0; i<logFileList_m.count(); i++){
        // progress
        QString text = QString("Parsing file %1/%2").arg(QString::number(i+1), QString::number(fileNum));
        setTextOnProgressDialog(text);
        int startProgress = PROGRESS_STEP1 + stepValue * i;
        int endProgress = PROGRESS_STEP1 + stepValue * (i+1);

        // parse
        QString filePath = logFileList_m.at(i);
        QFile file(filePath);
        if(file.exists()){
            parseLog(writer, filePath, startProgress, endProgress);
        }else{
            qDebug() << QString("Error: file '%1' doesn't exist.").arg(filePath);
        }

        // progress
        setValueOnProgressDialog(endProgress);
    }

    // Step2 : Write group info
    setValueOnProgressDialog(PROGRESS_STEP2);
    setTextOnProgressDialog("Writing group information to CLV file.");
    writeGroupInfoToCsv(writer);

    // Step3 : Write layer info.
    setValueOnProgressDialog(PROGRESS_STEP3);
    setTextOnProgressDialog("Writing layer information to CLV file.");
    writeLayerInfoToCsv(writer);

    // Step4 : Other
    setValueOnProgressDialog(PROGRESS_STEP4);
    setTextOnProgressDialog("Writing group info to each command.");
    updateCommandToCsv(writer);

    // Step Done.
    setValueOnProgressDialog(PROGRESS_MAX);
    setTextOnProgressDialog("Done!!");

    // return true if parse success.
    //return true;
}

bool NexusLogParser::parseLog(ClvDataAccessor *writer, QString logFilePath, int startProgress, int endProgress){
    // progress
    int numOfCommands = countCommand(logFilePath);
    int diffOfProgress = endProgress - startProgress;
    int progressAfterCounting = startProgress + diffOfProgress * PROGRESS_COMMAND_COUNT_RATIO;
    double stepValue = diffOfProgress * (1 - PROGRESS_COMMAND_COUNT_RATIO);
    setValueOnProgressDialog(progressAfterCounting);

    // setup
    QFileInfo info(logFilePath);
    QString fileName = info.fileName();
    QFile file(logFilePath);
    file.open(QIODevice::ReadOnly);
    QRegExp regex("`(.*)`");
    QString line;
    QString command = "";
    QByteArray buffer;
    int counter = 0;

    // parse each line
    while(!file.atEnd()){
        line = file.readLine();

        // command
        if(regex.indexIn(line) > -1){
            if(command != ""){ // not first command
                QByteArray compressed = qCompress(buffer, 5);
                writer->writeCommand(command, command, "root", "", fileName, compressed);
                if(false){
                    qDebug() << command;
                    qDebug() << "row       : " << buffer.length();
                    qDebug() << "compressed: " << compressed.length();
                }
            }

            // clears old command's buffer for buffering next command.
            command = regex.cap(1).trimmed();
            buffer.clear();

            // progress
            counter++;
            if(counter % 10 == 0){
                int value = progressAfterCounting + (stepValue * counter / numOfCommands);
                setValueOnProgressDialog(value);
            }
        }

        // buffer both command and contents line
        buffer.append(line);
    }

    // write last command
    if(command != ""){
        QByteArray compressed = qCompress(buffer, 5);
        writer->writeCommand(command, command, "root", "", fileName, compressed);
        if(false){
            qDebug() << command;
            qDebug() << "row       : " << buffer.length();
            qDebug() << "compressed: " << compressed.length();
        }
        buffer.clear();
        compressed.clear();
    }

    return true;
}

int NexusLogParser::countCommand(QString logFilePath){
    QFile file(logFilePath);
    file.open(QIODevice::ReadOnly);
    QRegExp regex("`(.*)`");
    QString line;
    int counter = 0;

    while(!file.atEnd()){
        line = file.readLine();
        if(regex.indexIn(line) > -1){
            counter++;
        }
    }

    return counter;
}
