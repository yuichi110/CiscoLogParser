#ifndef MWC_PRODUCTPICKER_H
#define MWC_PRODUCTPICKER_H

#include <QtWidgets>
#include <QtNetwork>

#include "core_messagebroker.h"
#include "log_abstractlogparser.h"
#include "log_nexuslogparser.h"

class MessageBroker;

class ProductPicker : public QListWidget
{

    Q_OBJECT
public:
    explicit ProductPicker(QWidget *parent, MessageBroker *messageBroker);
    QString getSelectedProduct();

private:
    MessageBroker *messageBroker_m;

signals:

public slots:
    void selectedItemChanged();

};

#endif // MWC_PRODUCTPICKER_H
