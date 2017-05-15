#include <QApplication>
#include "mainwindow.h"
#include "board.h"
#include "tile.h"

int count=0,turn=1,max=0;
int wR,wC,bR,bC;
Tile *click1;

Tile *tile[8][8] = { { NULL } };

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

void accessories(QWidget *baseWidget)
{

    QLabel *moves = new QLabel(baseWidget);
    moves->setGeometry(760,35,250,550);
    moves->setStyleSheet("QLabel {background-color: white;}");
    moves->setText();
}

void chessBoard(QWidget *baseWidget, Tile *tile[8][8])
{
    int i,j,k=0,hor,ver;
    Border *border[4]={ NULL };

    //borderDisplay
    {
    border[0]->outline(baseWidget,180,35,0);
    border[1]->outline(baseWidget,180,567,0);
    border[2]->outline(baseWidget,180,55,1);
    border[2]->outline(baseWidget,712,55,1);
    }

    //Create 64 tiles (allocating memories to the objects of Tile class)
    ver=55;
    for(i=0;i<8;i++)
    {
        hor=200;
        for(j=0;j<8;j++)
        {
            tile[i][j] = new Tile(baseWidget);
            tile[i][j]->tileColor=(i+j)%2;
            tile[i][j]->piece=0;
            tile[i][j]->row=i;
            tile[i][j]->col=j;
            tile[i][j]->tileNum=k++;
            tile[i][j]->tileDisplay();
            tile[i][j]->setGeometry(hor,ver,64,64);
            hor+=64;
        }
        ver+=64;
    }

    //white pawns
    for(j=0;j<8;j++)
    {
        tile[1][j]->piece=1;
        tile[1][j]->pieceColor=0;
        tile[1][j]->display('P');
    }

    //black pawns
    for(j=0;j<8;j++)
    {
        tile[6][j]->piece=1;
        tile[6][j]->pieceColor=1;
        tile[6][j]->display('P');
    }

    //white and black remaining elements
    for(j=0;j<8;j++)
    {
        tile[0][j]->piece=1;
        tile[0][j]->pieceColor=0;
        tile[7][j]->piece=1;
        tile[7][j]->pieceColor=1;
    }

    {
    tile[0][0]->display('R');
    tile[0][1]->display('H');
    tile[0][2]->display('B');
    tile[0][3]->display('Q');
    tile[0][4]->display('K');
    tile[0][5]->display('B');
    tile[0][6]->display('H');
    tile[0][7]->display('R');
    }


    {
    tile[7][0]->display('R');
    tile[7][1]->display('H');
    tile[7][2]->display('B');
    tile[7][3]->display('Q');
    tile[7][4]->display('K');
    tile[7][5]->display('B');
    tile[7][6]->display('H');
    tile[7][7]->display('R');
    }

    wR=7;
    wC=4;

    bR=0;
    bC=4;

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget *myWidget = new QWidget();
    myWidget->setGeometry(100,100,1070,600);

    accessories(myWidget);
    chessBoard(myWidget,tile);

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