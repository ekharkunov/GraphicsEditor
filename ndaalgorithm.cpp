#include "ndaalgorithm.hpp"
#include <QIcon>
#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

NDAAlgorithm::NDAAlgorithm(MainScene *sc, QObject *parent) :
    AlgorithmInterface(sc, parent),
    mStartPoint(QPoint()),
    mEndPoint(QPoint()),
    mCurrentPoint(QPoint()),
    mDx(0.),
    mDy(0.),
    mCurrentX(0.),
    mCurrentY(0.),
    mCurrentStep(0)
{
    mCalculationTable = new QStandardItemModel(0, 4);
    mCalculationTable->setHeaderData(0, Qt::Horizontal, tr("Step"));
    mCalculationTable->setHeaderData(1, Qt::Horizontal, tr("X"));
    mCalculationTable->setHeaderData(2, Qt::Horizontal, tr("Y"));
    mCalculationTable->setHeaderData(3, Qt::Horizontal, tr("Result point"));
}

NDAAlgorithm::~NDAAlgorithm()
{

}

void NDAAlgorithm::execute(QVector<QPoint> &args)
{
    if (args.count() != 2)
        emit error("");
    mCalculationTable->removeRows(0, mCalculationTable->rowCount());
    mStartPoint = args.at(0);
    mEndPoint = args.at(1);
    mCurrentPoint = mStartPoint;
    mCurrentStep = 1;
    int dx = qAbs(mStartPoint.x() - mEndPoint.x()) , dy = qAbs(mStartPoint.y() - mEndPoint.y());
    mDx = dx - dy >= 0 ? 1 : (double)dx/dy;
    mDy = dx - dy < 0 ? 1 : (double)dy/dx;
    if (mStartPoint.x() > mEndPoint.x())
        mDx *= -1;
    if (mStartPoint.y() > mEndPoint.y())
        mDy *= -1;
    qDebug()<<"Start point: "<<mStartPoint;
    qDebug()<<"End point: "<<mEndPoint;
    qDebug()<<"pixel: "<<mCurrentPoint;
    mCurrentX = mStartPoint.x();
    mCurrentY = mStartPoint.y();
    mCalculationTable->appendRow(createRow(mCurrentStep, mCurrentX, mCurrentY, mCurrentPoint));
    mScene->drawPixel(mCurrentPoint);
    do
    {
        doStep();
        qDebug()<<"pixel: "<<mCurrentPoint;
    } while (mCurrentPoint != mEndPoint);
}

void NDAAlgorithm::doStep()
{
    mCurrentX += mDx;
    mCurrentY += mDy;
    mCurrentPoint.setX((int)(mCurrentX + 0.5));
    mCurrentPoint.setY((int)(mCurrentY + 0.5));
    mScene->drawPixel(mCurrentPoint);
    ++mCurrentStep;
    mCalculationTable->appendRow(createRow(mCurrentStep, mCurrentX + 0.5, mCurrentY + 0.5, mCurrentPoint));
}

bool NDAAlgorithm::eventFilter(QObject *obj, QEvent *event)
{
    if (obj != mScene)
        return false;
    switch (event->type())
    {
    case QEvent::GraphicsSceneMousePress :
    {
        QGraphicsSceneMouseEvent *scEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (scEvent->button() == Qt::LeftButton)
        {
            if (mStartPoint.isNull())
                mStartPoint = mScene->convertFromRealCoordinate(
                            scEvent->scenePos().toPoint()
                            );
            else
            {
                mEndPoint = mScene->convertFromRealCoordinate(
                            scEvent->scenePos().toPoint()
                            );
                QVector<QPoint> args;
                args.append(mStartPoint);
                args.append(mEndPoint);
                execute(args);
                mStartPoint = QPoint();
                mEndPoint = QPoint();
            }
        }
        else
        {
            mStartPoint = QPoint();
            mEndPoint = QPoint();
        }
        break;
    }
    case QEvent::KeyPress :
    {
        if (static_cast<QKeyEvent*>(event)->key() == Qt::Key_Escape)
            mStartPoint = QPoint();
        break;
    }
    {
    default :
            break;
        }
    }
    return false;
}

QIcon NDAAlgorithm::icon() const
{
    return QIcon();
}

QString NDAAlgorithm::name() const
{
    return tr("Segment");
}

QString NDAAlgorithm::tooltip() const
{
    return tr("Segment (NDA)");
}

QList<QStandardItem *> NDAAlgorithm::createRow(int step, qreal x, qreal y, QPoint point)
{
    QList<QStandardItem*> list;
    list.append(new QStandardItem(QString::number(step)));
    list.append(new QStandardItem(QString::number(x)));
    list.append(new QStandardItem(QString::number(y)));
    list.append(new QStandardItem("(" + QString::number(point.x()) + ", " + QString::number(point.y()) + ")"));
    return list;
}

