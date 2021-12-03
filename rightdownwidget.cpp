#include <QStandardItemModel>
#include <QStringList>
#include "rightdownwidget.h"

rightDownWidget::rightDownWidget(QWidget *parent) : QWidget(parent) {
    tablewidget = new tableWidget;
    tablewidget->setParent(this);

    QStringList header;
    header << tr("t") << tr("r");

    //tablewidget->setColumnWidth(2, 5);
    tablewidget->show();
}
