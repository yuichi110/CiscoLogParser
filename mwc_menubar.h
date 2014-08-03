#ifndef MWC_MENUBAR_H
#define MWC_MENUBAR_H

#include <QtWidgets>
#include "core_appinfo.h"
#include "core_messagebroker.h"

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    explicit MenuBar(QWidget *parent, MessageBroker *messageBroker);

private:
    MessageBroker *messageBroker_m;

signals:

public slots:
    void openPreferenceClicked();
    void openAboutClicked();

    void setLogsClicked();
    //void setCsvFileClicked();
    void parseClicked();
    void clearClicked();

    void minimizeClicked();
    void openJsonTesterClicked();

    void openHelpPageClicked();
    void reportNewBugClicked();
    void contactToAuthorClicked();
    void updateCategorizeRuleClicked();
    void checkSoftwareUpdateClicked();
};

#endif // MWC_MENUBAR_H
