#include "clientlistview.h"

ClientListView::ClientListView(QWidget *parent)
    : BackgroundedFrame{parent} {
    clientWidgetList = new QListWidget(this);

}
