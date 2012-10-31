#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <QtGui/QMainWindow>
#include <QMap>

class MainScene;
class QGraphicsView;
class QTableView;
class AlgorithmInterface;

class Widget : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    virtual ~Widget();
    void registerAlgorithm(AlgorithmInterface *algorithm);
    void unregisterAlgorithm(AlgorithmInterface *algorithm);
private:
    MainScene *mScene;
    QGraphicsView *mGraphicsView;
    QTableView *mTableView;
    QToolBar *mToolBar;

    QMap<AlgorithmInterface*, QAction*> mRegisteredAlg2Action;

private slots:
    void clearScene();

public slots:
    void algorithmChanged();


};

#endif // WIDGET_HPP
