#ifndef ALGORITHMINTERFACE_HPP
#define ALGORITHMINTERFACE_HPP

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QStandardItemModel>
#include "mainscene.hpp"

class QIcon;

class AlgorithmInterface : public QObject
{
    Q_OBJECT
public:
    explicit AlgorithmInterface(MainScene *sc, QObject *parent = 0) :
        QObject(parent), mScene(sc), mCalculationTable() {}
    virtual ~AlgorithmInterface() {}
    virtual QStandardItemModel *calculationTable() { return mCalculationTable; }
    virtual void execute(QVector<QPoint> &args) = 0;
    virtual void doStep() = 0;
    virtual QIcon icon() const = 0;
    virtual QString name() const = 0;
    virtual QString tooltip() const = 0;
    virtual void setScene(MainScene *scene) { mScene = scene; }
    virtual bool eventFilter(QObject *obj, QEvent *event)
    {
        return false;
    }

public slots:
    void activate()
    {
        mScene->installEventFilter(this);
        emit algorithmActivated();
    }
protected:
    MainScene *mScene;
    QStandardItemModel *mCalculationTable;

signals:
    void error(QString errString);
    void algorithmActivated();
};

#endif // ALGORITHMINTERFACE_HPP
