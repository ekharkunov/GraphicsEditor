#ifndef MAINSCENE_HPP
#define MAINSCENE_HPP

#include <QGraphicsScene>

#define EDGE_LENGTH 15
#define HEIGTH 1200
#define WIDTH 1200


class MainScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MainScene(QObject *parent = 0);
    virtual ~MainScene();
    //! @param point Point in custom coordinate
    void drawPixel(QPoint point, QColor color = QColor("black"));
    QPoint& convertFromRealCoordinate(QPoint realPoint);
    void createNet();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MAINSCENE_HPP
