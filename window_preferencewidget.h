#ifndef WINDOW_PREFERENCEWIDGET_H
#define WINDOW_PREFERENCEWIDGET_H

#include <QWidget>
#include "core_appinfo.h"
#include "core_messagebroker.h"

class PreferenceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PreferenceWidget(MessageBroker *messageBroker);
    void fillFields();
    void clearMessage();

private:
    MessageBroker *messageBroker_m;
    QLineEdit *domainLine_m;
    QLineEdit *portLine_m;
    QLabel *messageLabel_m;
signals:

private slots:
    void setDefaultClicked();
    void updateClicked();
};

#endif // WINDOW_PREFERENCEWIDGET_H
