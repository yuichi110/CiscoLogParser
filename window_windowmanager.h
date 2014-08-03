#ifndef WINDOW_WINDOWMANAGER_H
#define WINDOW_WINDOWMANAGER_H

#include <QtGui>
#include <QtWidgets>

#include "core_messagebroker.h"
#include "window_preferencewidget.h"
#include "window_jsontestwidget.h"
#include "window_aboutwidget.h"

class PreferenceWidget;

class WindowManager
{
public:
    WindowManager(QWidget *parent, MessageBroker *messageBroker);
    void openPreferenceWindow();
    void openJsonTestWindow();
    void openAboutWindow();

private:
    MessageBroker *messageBroker_m;
    PreferenceWidget *preferenceWindow_m;
    JsonTestWidget *jsonTestWindow_m;
    //AboutWidget *aboutWindow_m;

};

#endif // WINDOW_WINDOWMANAGER_H
