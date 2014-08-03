#ifndef CORE_APPINFO_H
#define CORE_APPINFO_H

#include <QtGui>

class AppInfo
{
public:
    // app
    static const QString APP_NAME;
    static const QString APP_DESCRIPTION;
    static const QString APP_ICON;
    static const QString APP_STYLE_FUSION;
    static const QString LICENSE;
    static const int MAJOR_VERSION;
    static const int MINOR_VERSION;
    static const QString DROP_ICON;

    //preference
    static const QString PREF_DBFILE_PATH;
    static const QString SERVER_DEFAULT_DOMAIN;
    static const int SERVER_DEFAULT_PORT;

    // main window
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const int WINDOW_MARGIN;
    static const int WINDOW_SPACING;
    static const int DROP_ZONE_WIDTH;
    static const int DROP_ZONE_HEIGHT;
    static const int BUTTON_WIDTH;
    static const int PROGRESS_DIALOG_WIDTH;
    static const int PROGRESS_DIALOG_HEIGHT;

    // widget
    static const int PREFERENCE_WINDOW_WIDTH;
    static const int PREFERENCE_WINDOW_HEIGHT;
    static const int PREFERENCE_LINEEDIT_WIDTH;
    static const int PREFERENCE_BUTTON_WIDTH;
    static const int JSON_WINDOW_MIN_WIDTH;
    static const int JSON_WINDOW_MIN_HEIGHT;
    static const int JSON_WINDOW_BUTTON_WIDTH;

    // about
    static const int ABOUT_WINDOW_WIDTH_WINDOWS;
    static const int ABOUT_WINDOW_WIDTH_MAC;
    static const int ABOUT_WINDOW_HEIGHT_WINDOWS;
    static const int ABOUT_WINDOW_HEIGHT_MAC;
    static const int ABOUT_WINDOW_ICON_WIDTH;
    static const int ABOUT_WINDOW_ICON_HEIGHT;
    static const QString ABOUT_ICON_TAC;
    static const QString ABOUT_ICON_QT;
    static const QString ABOUT_ICON_SQLITE;

    // authour
    static const QString AUTHOR;
    static const QString MY_TITLE;
    static const QString MAIL_ADDRESS;
    static const QString WEB_PAGE_URL;
    static const QString AUTHOR_PAGE_URL;
    static const QString CONTACT_URL;
    static const QString REPORT_BUG_URL;
    static const QString GIT_PAGE_URL;

    // debug
    static const bool DEBUG_MESSAGE_BROKER;
    static const bool DEBUG_CLV_DATA_ACCESSOR;
    static const bool DEBUG_MAIN_WINDOW;
    static const bool DEBUG_PRODUCT_PICKER;
    static const bool DEBUG_DROP_ZONE;
    static const bool DEBUG_MENUBAR;
    static const bool DEBUG_PROGRESS_DIALOG;
    static const bool DEBUG_LOG_PARSER;

private:
    AppInfo();
};

#endif // CORE_APPINFO_H
