#include <QApplication>
#include "mainwindow.h"
#include "board.h"
#include "db.h"
#include "boardvision.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *myWidget = new QWidget();
    myWidget->setGeometry(100,100,1070,700);
    BoardVision *bv = new BoardVision(myWidget);
    bv->buttons();
    myWidget->show();
    return a.exec();
}



//int main(int argc, char *argv[])
//{
//    //QApplication a(argc, argv);
//    //MainWindow w;
//    //w.show();

//    //return a.exec();
//    QVector <Piece*> pieces;
//    //Bishop *bop = new Bishop(QPoint(f,5));
//    //pieces.push_back((Piece*)bop);
//    King k(QPoint(d,4));
//    Rook r(QPoint(d,4));
//    Bishop b(QPoint(d,4));
//    Queen q(QPoint(d,4));
//    Knight n(QPoint(d,4));
//    Pawn p(QPoint(d,4));
//    //return k.MovePattern(QPoint(a,3), pieces);
//    //return r.MovePattern(QPoint(e,5), pieces);
//    //return b.MovePattern(QPoint(d,1), pieces);
//    //return q.MovePattern(QPoint(d,1), pieces);
//    //return p.MovePattern(QPoint(d,3), pieces);
//    //return n.MovePattern(QPoint(d,5), pieces);
//}
