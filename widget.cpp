#include "widget.hpp"
#include "mainscene.hpp"
#include "ndaalgorithm.hpp"
#include <QGridLayout>
#include <QGraphicsView>
#include <QTableView>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QHeaderView>

Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
{
    mToolBar = new QToolBar("Instrument bar");
    mToolBar->setAllowedAreas(Qt::TopToolBarArea);
    addToolBar(mToolBar);

    mScene = new MainScene;
    mGraphicsView = new QGraphicsView(mScene, this);
    mTableView = new QTableView;
    mTableView->verticalHeader()->hide();

    QWidget *mainWidget = new QWidget(this);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(mGraphicsView, 0, 0);
    mainLayout->addWidget(mTableView, 0, 2);
    mainLayout->setColumnStretch(0, 50);
    mainLayout->setColumnStretch(2, 25);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    QMenu *menu = menuBar()->addMenu(tr("Edit"));
    menu->addAction(tr("Clear"), this, SLOT(clearScene()));


    registerAlgorithm(new NDAAlgorithm(mScene));
}

Widget::~Widget()
{
    delete mToolBar;
    delete mScene;
    delete mGraphicsView;
    delete mTableView;
}

void Widget::registerAlgorithm(AlgorithmInterface *algorithm)
{
    QAction *action = mToolBar->addAction(algorithm->icon(), algorithm->name());
    action->setToolTip(algorithm->name());
    connect(action, SIGNAL(triggered()), algorithm, SLOT(activate()));
    connect(algorithm, SIGNAL(algorithmActivated()), this, SLOT(algorithmChanged()));
    mRegisteredAlg2Action[algorithm] = action;
}

void Widget::unregisterAlgorithm(AlgorithmInterface *algorithm)
{
    if (!mRegisteredAlg2Action.contains(algorithm))
        return;
    QAction *action = mRegisteredAlg2Action.value(algorithm);
    action->setCheckable(true);
    mToolBar->removeAction(action);
    disconnect(action, SIGNAL(triggered()));
    disconnect(algorithm, SIGNAL(algorithmActivated()));
}

void Widget::clearScene()
{
    mScene->clear();
    mScene->createNet();
}

void Widget::algorithmChanged()
{
    AlgorithmInterface *alg = static_cast<AlgorithmInterface*>(sender());
    if (!alg)
        return;
    mTableView->setModel(alg->calculationTable());
}
