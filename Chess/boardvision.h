#ifndef BOARDVISION_H
#define BOARDVISION_H
#include "tile.h"
#include "db.h"
#include <QListWidget>
#include <QPushButton>
#include <QTableWidget>
#include <controller.h>

class BoardVision : public QObject
{
    Q_OBJECT
    int count=0,turn=1,max=0;
    QVector<QPoint> fromto;
    Tile *click1;

    Tile *tile[8][8] = { { NULL } };
    QString table="";
    QWidget *baseWidget;
public:
    class Border
    {
    public:
        Border();
        void outline(QWidget *baseWidget, int xPos, int yPos, int Pos)
        {
             QLabel *outLabel = new QLabel(baseWidget);

            if(!Pos)
                outLabel->setGeometry(xPos,yPos,552,20);        //Horizontal Borders

            else
                outLabel->setGeometry(xPos,yPos,20,512);        //Vertical Borders

            outLabel->setStyleSheet("QLabel { background-color :rgb(170, 170, 127); color : black; }");
        }
    };
    BoardVision(QWidget *widget);
    void downloadButton();
    signals:
    void wantMove(QPoint from,QPoint to);
private slots:
    void onListClicked(QListWidgetItem* item );
    void moveList();
    void tileClicked(QPoint p);
};

#endif // BOARDVISION_H
