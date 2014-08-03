#include "core_appinfo.h"

// App Info
const QString AppInfo::APP_NAME = "Cisco Log Parser";
const QString AppInfo::APP_DESCRIPTION = "CLP(Cisco Log Parser) analyzes log files and create CLV file. Another application CLV(Cisco Log Viewer) shows log with ordered style.\nCLP and CLV will help your troubleshooting task.";
const QString AppInfo::APP_STYLE_FUSION = "fusion";
const QString AppInfo::APP_ICON = ":/icon/appicon.png";
const QString AppInfo::LICENSE = "LGPL (Inherits Qt5)";
const int AppInfo::MAJOR_VERSION = 1;
const int AppInfo::MINOR_VERSION = 1;

// Preference
const QString AppInfo::PREF_DBFILE_PATH = "./settings.db";
const QString AppInfo::SERVER_DEFAULT_DOMAIN = "clp.yuichi.com";
const int AppInfo::SERVER_DEFAULT_PORT = 80;

// Main Window
const int AppInfo::WINDOW_WIDTH = 500;
const int AppInfo::WINDOW_HEIGHT = 560;
const int AppInfo::WINDOW_MARGIN = 5;
const int AppInfo::WINDOW_SPACING = 5;
const int AppInfo::DROP_ZONE_WIDTH = 300;
const int AppInfo::DROP_ZONE_HEIGHT = 360;
const int AppInfo::BUTTON_WIDTH = 75;
const int AppInfo::PROGRESS_DIALOG_WIDTH = 300;
const int AppInfo::PROGRESS_DIALOG_HEIGHT = 100;
const QString AppInfo::DROP_ICON = ":/icon/dropImage.png";

// widget
const int AppInfo::PREFERENCE_WINDOW_WIDTH = 400;
const int AppInfo::PREFERENCE_WINDOW_HEIGHT = 150;
const int AppInfo::PREFERENCE_LINEEDIT_WIDTH = 200;
const int AppInfo::PREFERENCE_BUTTON_WIDTH = 100;
const int AppInfo::JSON_WINDOW_MIN_WIDTH = 500;
const int AppInfo::JSON_WINDOW_MIN_HEIGHT = 500;
const int AppInfo::JSON_WINDOW_BUTTON_WIDTH = 100;

// ABOUT
const int AppInfo::ABOUT_WINDOW_WIDTH_WINDOWS = 300;
const int AppInfo::ABOUT_WINDOW_WIDTH_MAC = 250;
const int AppInfo::ABOUT_WINDOW_HEIGHT_WINDOWS = 300;
const int AppInfo::ABOUT_WINDOW_HEIGHT_MAC = 250;
const int AppInfo::ABOUT_WINDOW_ICON_WIDTH = 60;
const int AppInfo::ABOUT_WINDOW_ICON_HEIGHT = 80;
const QString AppInfo::ABOUT_ICON_TAC = ":/icon/tac_icon.png";
const QString AppInfo::ABOUT_ICON_QT = ":/icon/qt_icon.png";
const QString AppInfo::ABOUT_ICON_SQLITE = ":/icon/sqlite_icon.png";




// Author
const QString AppInfo::AUTHOR = "Yuichi Ito";
const QString AppInfo::MY_TITLE = "Cisco Systems. Japan TAC DataCenter Team";
const QString AppInfo::MAIL_ADDRESS = "yuiito@cisco.com";
const QString AppInfo::WEB_PAGE_URL = "http://clv.yuichi.com/";
const QString AppInfo::AUTHOR_PAGE_URL = "http://www.yuichi.com/";
const QString AppInfo::CONTACT_URL = "mailto:%1";
const QString AppInfo::REPORT_BUG_URL = "mailto:%1?Subject=[BUG CLP v%2.%3] TITLE_HERE";
const QString AppInfo::GIT_PAGE_URL = "http://xxxx";

// Debug
const bool AppInfo::DEBUG_MESSAGE_BROKER = false;
const bool AppInfo::DEBUG_CLV_DATA_ACCESSOR = false;
const bool AppInfo::DEBUG_MAIN_WINDOW = false;
const bool AppInfo::DEBUG_PRODUCT_PICKER = false;
const bool AppInfo::DEBUG_DROP_ZONE = false;
const bool AppInfo::DEBUG_MENUBAR = false;
const bool AppInfo::DEBUG_PROGRESS_DIALOG = false;
const bool AppInfo::DEBUG_LOG_PARSER = true;

AppInfo::AppInfo()
{
}
