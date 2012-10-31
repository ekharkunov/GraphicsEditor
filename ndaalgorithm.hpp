#ifndef NDAALGOITHM_HPP
#define NDAALGOITHM_HPP

#include "algorithmInterface.hpp"

class QPoint;

class NDAAlgorithm : public AlgorithmInterface
{
    Q_OBJECT
public:
    explicit NDAAlgorithm(MainScene *sc, QObject *parent = 0);
    virtual ~NDAAlgorithm();
    void execute(QVector<QPoint> &args);
    void doStep();
    bool eventFilter(QObject *obj, QEvent *event);
    QIcon icon() const;
    QString name() const;
    QString tooltip() const;
private:
    QList<QStandardItem*> createRow(int step, qreal x, qreal y, QPoint point);

    QPoint mStartPoint;
    QPoint mEndPoint;
    QPoint mCurrentPoint;
    qreal mDx;
    qreal mDy;
    qreal mCurrentX;
    qreal mCurrentY;
    int mCurrentStep;
};

#endif // NDAALGOITHM_HPP
