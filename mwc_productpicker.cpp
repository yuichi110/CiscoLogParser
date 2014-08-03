#include "mwc_productpicker.h"

ProductPicker::ProductPicker(QWidget *parent, MessageBroker *messageBroker) :
    QListWidget(parent)
{
    messageBroker_m = messageBroker;
    messageBroker_m->registerProductPicker(this);
    setSelectionMode(QAbstractItemView::SingleSelection);

    QList<QString> productList = messageBroker_m->messageProductPicker_getProductList();
    foreach(QString product, productList){
        addItem(product);
    }

    if(productList.length() > 0){
        setCurrentRow(0);
    }else{
        qDebug() << "Error: No Product";
    }

    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(selectedItemChanged()));
}

QString ProductPicker::getSelectedProduct(){
    QString product = this->currentItem()->text();
    return product;
}

void ProductPicker::selectedItemChanged(){
    messageBroker_m->messageProductPicker_selectedItemChanged();
}
