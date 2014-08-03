#include "window_windowmanager.h"

WindowManager::WindowManager(QWidget *parent, MessageBroker *messageBroker)
{
    messageBroker_m = messageBroker;
    messageBroker_m->registerWindowManager(this);

    preferenceWindow_m = new PreferenceWidget(messageBroker);
    jsonTestWindow_m = new JsonTestWidget();
    //aboutWindow_m = new AboutWidget();
}

void WindowManager::openPreferenceWindow(){
    preferenceWindow_m->fillFields();
    preferenceWindow_m->clearMessage();
    preferenceWindow_m->show();
}

void WindowManager::openJsonTestWindow(){
    jsonTestWindow_m->clear();
    jsonTestWindow_m->show();
}

void WindowManager::openAboutWindow(){
    //aboutWindow_m->show();
    AboutWidget::getInstance()->show();
}
