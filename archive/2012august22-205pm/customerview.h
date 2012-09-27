#ifndef CUSTOMERVIEW_H
#define CUSTOMERVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QMap>
#include "customer.h"

class CustomerView : public QWidget
{
    Q_OBJECT
public:
    explicit CustomerView(QWidget *parent = 0);
    void initializeData();

    // FROM CONTROLLER
    void loadData(QMap<quint32, Customer> data);
    
signals:
    // TO CONTROLLER
    void refreshData();
    
public slots:

protected:
    QSize sizeHint() const;

private:
    QTableWidgetItem * newEntry(QString text);

    QVBoxLayout *customerLayout;

    QTableWidget *customerTable;
    
};

#endif // CUSTOMERVIEW_H
