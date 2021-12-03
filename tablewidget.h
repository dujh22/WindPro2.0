#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H
#include <QTableView>
#include <QTableWidgetItem>
class QStandardItemModel;
class tableWidget : public QTableView {
    Q_OBJECT
public slots:
//    void dataChangedSlot(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int> ());
    void slotitemChanged(QTableWidgetItem *);
public:
    tableWidget(QWidget *parent = 0);
    void update1();
    QStandardItemModel* _model;
    // QTableWidget * _tablewidget;
    ~tableWidget();
};

#endif  // TABLEWIDGET_H
