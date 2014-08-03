#include "window_preferencewidget.h"

PreferenceWidget::PreferenceWidget(MessageBroker *messageBroker) :
    QWidget(NULL)
{
    messageBroker_m = messageBroker;
    messageBroker_m->registerPreferenceWidget(this);

    setFixedSize(AppInfo::PREFERENCE_WINDOW_WIDTH, AppInfo::PREFERENCE_WINDOW_HEIGHT);

    QHBoxLayout *domainLayout = new QHBoxLayout();
    domainLayout->addWidget(new QLabel("Server Domain or IP:"));
    domainLine_m = new QLineEdit(this);
    domainLine_m->setFixedWidth(AppInfo::PREFERENCE_LINEEDIT_WIDTH);
    domainLayout->addWidget(domainLine_m);

    QHBoxLayout *portLayout = new QHBoxLayout();
    portLayout->addWidget(new QLabel("Server Port number:"));
    portLine_m = new QLineEdit(this);
    portLine_m->setFixedWidth(AppInfo::PREFERENCE_LINEEDIT_WIDTH);
    portLayout->addWidget(portLine_m);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    messageLabel_m = new QLabel("");
    buttonLayout->addWidget(messageLabel_m);
    QPushButton *setDefaultButton = new QPushButton("set default", this);
    setDefaultButton->setFixedWidth(AppInfo::PREFERENCE_BUTTON_WIDTH);
    connect(setDefaultButton, SIGNAL(clicked()), this, SLOT(setDefaultClicked()));
    buttonLayout->addWidget(setDefaultButton);
    QPushButton *updateButton = new QPushButton("update", this);
    updateButton->setFixedWidth(AppInfo::PREFERENCE_BUTTON_WIDTH);
    connect(updateButton, SIGNAL(clicked()), this, SLOT(updateClicked()));
    buttonLayout->addWidget(updateButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(5,5,5,5);
    mainLayout->setSpacing(5);
    mainLayout->addWidget(new QLabel("Server settings for updating product rule."));
    mainLayout->addLayout(domainLayout);
    mainLayout->addLayout(portLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void PreferenceWidget::fillFields(){
    QString domain = messageBroker_m->messagePreferenceWidget_getDomain();
    int port = messageBroker_m->messagePreferenceWidget_getPort();

    domainLine_m->setText(domain);
    portLine_m->setText(QString::number(port));
}

void PreferenceWidget::setDefaultClicked(){
    qDebug() << "setDefaultClicked()";
    QString resultMessage = messageBroker_m->messagePreferenceWidget_initialize();
    messageLabel_m->setText(resultMessage);
}

void PreferenceWidget::updateClicked(){
    qDebug() << "updateClicked()";
    QString domain = domainLine_m->text();
    bool ok = true;
    int port = (portLine_m->text()).toInt(&ok);
    if(!ok){
        messageLabel_m->setText("value of port number field have problem.");
        return;
    }

    QString resultMessage = messageBroker_m->messagePreferenceWidget_update(domain, port);
    messageLabel_m->setText(resultMessage);
}

void PreferenceWidget::clearMessage(){
    messageLabel_m->setText("");
}
