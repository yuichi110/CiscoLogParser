#ifndef TEST_COMPONENTTESTER_H
#define TEST_COMPONENTTESTER_H

#include <QApplication>
#include "dao_clvdataaccessor.h"
#include "dao_preferencedataaccessor.h"
#include "json_productrule.h"
#include "json_jsonparser.h"
#include "log_nexuslogparser.h"

class ComponentTester
{
public:
    ComponentTester();
    void testPreference();
    void testDatabase1();
    int testDatabase2(int argc, char *argv[]);
};

#endif // TEST_COMPONENTTESTER_H
