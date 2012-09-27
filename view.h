#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QAction>
#include <QActionGroup>
#include <QWidget>
#include <QIcon>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QCursor>
#include <QSize>
#include <QToolBar>
#include <QPoint>
#include <QStatusBar>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>

#include "customerview.h"
#include "reservationview.h"
#include "itemview.h"
#include "bookreservationview.h"
#include "itemavailabilityview.h"

#include <QDebug>

class View : public QMainWindow
{
    Q_OBJECT
    
public:
    View(QWidget *parent = 0);
    ~View();
    CustomerView * getCustomerView();
    ReservationView * getReservationView();
    ItemView * getItemView();
    BookReservationView * getBookReservationView();
    ItemAvailabilityView * getItemAvailabilityView();

signals:
    void clearDatabase();

public slots:
    void showItemAvail(QString title, int itemID);
    void showBookReservationView(QDate date);
    void showBookReservationView();
    void bookReservationDialogEnded();
    void clearDatabaseDialog();

private slots:
    void showResView();
    void showItemView();
    void showCustomerView();
    void showAbout();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    QVBoxLayout *viewLayout;
    QStackedWidget *stackedWidget;

    QWidget *centralWidget;
    QLabel *viewFooter;

    CustomerView *customerView;
    ReservationView *reservationView;
    ItemView *itemView;
    BookReservationView *bookResView;
    ItemAvailabilityView *itemAvailView;

    // toolbar actions
    QAction *resViewAction;
    QAction *cusViewAction;
    QAction *itemViewAction;
    QActionGroup *viewActionGroup;
    QAction *bookResAction;

    // file menu actions
    QAction *connectAction;
    QAction *clearAction;
    QAction *quitAction;

    // view menu actions
    // ** taken care of with toolbar

    // add menu actions
    QAction *addItemAction;
    QAction *addCustomerAction;
    // ** add reservation taken care of

    // help menu actions
    QAction *aboutAction;

    QToolBar *viewToolBar;
    QToolBar *newToolBar;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *addMenu;
    QMenu *helpMenu;

    QSize storedSize;


};

#endif // VIEW_H
