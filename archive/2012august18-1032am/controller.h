#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QStringList>
#include "view.h"
#include "model.h"

#include <QDebug>


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();
    
signals:
    
public slots:
    void refreshItemViewData();
    void refreshBookResViewItemList();

private:
    View * v;
    Model * m;
    
};

#endif // CONTROLLER_H
