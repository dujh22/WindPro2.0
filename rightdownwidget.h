#ifndef RIGHTDOWNWIDGET_H
#define RIGHTDOWNWIDGET_H

#include <QListWidget>
#include <QTableView>
#include <QWidget>

#include "global.h"
#include "tablewidget.h"
class rightDownWidget : public QWidget {
    Q_OBJECT
   public:
    explicit rightDownWidget(QWidget *parent = nullptr);
    tableWidget *tablewidget;
   signals:

   public slots:

   private:
};

#endif  // RIGHTDOWNWIDGET_H
