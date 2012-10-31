#include "mainscene.hpp"
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

MainScene::MainScene(QObject *parent) :
    QGraphicsScene(parent)
{
    QGraphicsLineItem *line;
    QPen pen(Qt::DashLine);
    //draw net
    setSceneRect(0,0, WIDTH, HEIGTH);
    for (int i = 1; i < WIDTH/EDGE_LENGTH; ++i)
    {
        line = new QGraphicsLineItem;
        line->setPen(pen);
        line->setLine(i*EDGE_LENGTH, 0, i*EDGE_LENGTH, HEIGTH);
        addItem(line);
    }
    for (int i = 1; i < HEIGTH/EDGE_LENGTH; ++i)
    {
        line = new QGraphicsLineItem;
        line->setPen(pen);
        line->setLine(0, i*EDGE_LENGTH, WIDTH, i*EDGE_LENGTH);
        addItem(line);
    }
}

MainScene::~MainScene()
{

}

void MainScene::drawPixel(QPoint point, QColor color)
{
    if (itemAt(point.x() * EDGE_LENGTH + 2, point.y() * EDGE_LENGTH + 2))
    {
        qDebug()<<"Pixel is already been drawn";
        return;
    }
    QGraphicsRectItem *item = new QGraphicsRectItem;
    QBrush br(color, Qt::SolidPattern);
    item->setBrush(br);
    item->setRect(point.x()*EDGE_LENGTH, point.y()*EDGE_LENGTH, EDGE_LENGTH, EDGE_LENGTH);
    addItem(item);
}

QPoint &MainScene::convertFromRealCoordinate(QPoint realPoint)
{
    QPoint point(realPoint.x() / EDGE_LENGTH, realPoint.y() / EDGE_LENGTH);
    return point;
}

void MainScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QPoint p = event->scenePos().toPoint();
    QPoint p1 = convertFromRealCoordinate(p);

    if (event->button() == Qt::LeftButton)
    {
        drawPixel(p1);
    }
    if (event->button() == Qt::RightButton)
    {
        QGraphicsRectItem *item = qgraphicsitem_cast<QGraphicsRectItem*>(itemAt(p));
        if (item)
            removeItem(item);
    }
}

void MainScene::createNet()
{
    QGraphicsLineItem *line;
    QPen pen(Qt::DashLine);
    //draw net
    setSceneRect(0,0, WIDTH, HEIGTH);
    for (int i = 1; i < WIDTH/EDGE_LENGTH; ++i)
    {
        line = new QGraphicsLineItem;
        line->setPen(pen);
        line->setLine(i*EDGE_LENGTH, 0, i*EDGE_LENGTH, HEIGTH);
        addItem(line);
    }
    for (int i = 1; i < HEIGTH/EDGE_LENGTH; ++i)
    {
        line = new QGraphicsLineItem;
        line->setPen(pen);
        line->setLine(0, i*EDGE_LENGTH, WIDTH, i*EDGE_LENGTH);
        addItem(line);
    }
}
