#include "mainwindow.h"
#include <QApplication>
#include <pieces.h>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //return a.exec();
    /*QVector <Piece*> pieces;
    Bishop *bop = new Bishop(QPoint(f,5));
    pieces.push_back((Piece*)bop);
    King k(QPoint(d,4));
    Rook r(QPoint(d,4));
    Bishop b(QPoint(d,4));
    Queen q(QPoint(d,4));
    Knight n(QPoint(d,4));
    Pawn p(QPoint(d,4));*/
    //return k.MovePattern(QPoint(a,3), pieces);
    //return r.MovePattern(QPoint(e,5), pieces);
    //return b.MovePattern(QPoint(d,1), pieces);
    //return q.MovePattern(QPoint(d,1), pieces);
    //return n.MovePattern(QPoint(c,5), pieces);
    return n.MovePattern(QPoint(f,5), pieces);
}
