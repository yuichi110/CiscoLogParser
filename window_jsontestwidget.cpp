#include "window_jsontestwidget.h"

JsonTestWidget::JsonTestWidget() :
    QWidget(NULL)
{
    setMinimumSize(AppInfo::JSON_WINDOW_MIN_WIDTH, AppInfo::JSON_WINDOW_MIN_HEIGHT);

    QString text = QString("MajorVersion %1.").arg(QString::number(AppInfo::MAJOR_VERSION));
    QLabel *versionLabel = new QLabel(text);
    versionLabel->setAlignment(Qt::AlignLeft);
    QPushButton *sampleButton = new QPushButton("sample", this);
    sampleButton->setFixedWidth(AppInfo::JSON_WINDOW_BUTTON_WIDTH);
    connect(sampleButton, SIGNAL(clicked()), this, SLOT(sampleButtonClicked()));
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setContentsMargins(0,0,0,0);
    topLayout->addWidget(versionLabel);
    topLayout->addWidget(sampleButton);

    jsonTextEdit_m = new JsonTextEdit(this);

    resultLabel_m = new QLabel("Please paste json rule and click 'check' button.");
    resultLabel_m->setAlignment(Qt::AlignLeft);
    QPushButton *checkButton = new QPushButton("check", this);
    checkButton->setFixedWidth(AppInfo::JSON_WINDOW_BUTTON_WIDTH);
    connect(checkButton, SIGNAL(clicked()), this, SLOT(checkButtonClicked()));
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->setContentsMargins(0,0,0,0);
    bottomLayout->addWidget(resultLabel_m);
    bottomLayout->addWidget(checkButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(AppInfo::WINDOW_MARGIN, AppInfo::WINDOW_MARGIN,
                                   AppInfo::WINDOW_MARGIN, AppInfo::WINDOW_MARGIN);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(jsonTextEdit_m);
    mainLayout->addLayout(bottomLayout);
    this->setLayout(mainLayout);
}

void JsonTestWidget::clear(){
    jsonTextEdit_m->setText("");
    resultLabel_m->setText("");
}

void JsonTestWidget::sampleButtonClicked(){
    QFile file(":/json/sample.json");
    if(!file.exists()){
        return ;
    }

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString text = file.readAll();
    file.close();

    jsonTextEdit_m->setText(text);
}

void JsonTestWidget::checkButtonClicked(){
    QString text = jsonTextEdit_m->toPlainText();

    // json syntax check
    QJsonObject root = QJsonDocument::fromJson(text.toUtf8()).object();
    if(root.count() == 0){
        resultLabel_m->setText("Json syntax is wrong.");
    }else if(NULL == JsonParser::getProductRuleFromText(text)){
        // invalid contents
        resultLabel_m->setText("Json syntax is OK. But contents have problem.");
    }else{
        // ok
        resultLabel_m->setText("No problem.");
    }
}
