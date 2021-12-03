#ifndef RIGHTTOPWIDGET_H
#define RIGHTTOPWIDGET_H

#include <QListWidget>
#include <QStackedWidget>
#include <QWidget>

#include "conditionwidget.h"
#include "measuresetwidget.h"
#include "parameterswidget.h"
#include "pickwidget.h"
#include "updatewidget.h"
#include "subpaint.h"

class MainWindow;

extern QWidget * tempww;

class rightTopWidget : public QWidget {
    Q_OBJECT
   public:
    explicit rightTopWidget(QWidget *parent = nullptr);
    void updateLeftTop();
    void updateLeftDown();
    void paint_data_delta();

    QStackedWidget *stackedWidget;
    parametersWidget *parameterswidget;
    conditionWidget *conditionwidget;
    measuresetWidget *measuresetwidget;
    pickWidget *pickwidget;
    updateWidget *updatewidget;
    subpaint *subpaintwidget;

   signals:

   public slots:
   private:
};

#endif  // RIGHTTOPWIDGET_H
