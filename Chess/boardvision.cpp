#include "boardvision.h"

BoardVision::BoardVision(QWidget *widget)
{
    int i,j,k=0,hor,ver;
    Border *border[4]={ NULL };
    baseWidget=widget;
    //borderDisplay
    {
    border[0]->outline(baseWidget,80,35,0);
    border[1]->outline(baseWidget,80,567,0);
    border[2]->outline(baseWidget,80,55,1);
    border[2]->outline(baseWidget,612,55,1);
    }

    //Create 64 tiles (allocating memories to the objects of Tile class)
    ver=55;
    for(i=7;i>=0;i--)
    {
        hor=100;
        for(j=0;j<8;j++)
        {
            tile[i][j] = new Tile(baseWidget);
            tile[i][j]->tileColor=(i+j)%2;
            tile[i][j]->piece=0;
            tile[i][j]->row=i+1;
            tile[i][j]->col=j+1;
            tile[i][j]->tileNum=k++;
            tile[i][j]->tileDisplay();
            tile[i][j]->setGeometry(hor,ver,64,64);
            connect(tile[i][j],SIGNAL( clicked(QPoint) ), this, SLOT( tileClicked(QPoint) ) );
            hor+=64;
        }
        ver+=64;
    }

    //b pawns
    for(j=0;j<8;j++)
    {
        tile[1][j]->piece=1;
        tile[1][j]->pieceColor=1;
        tile[1][j]->display(Piece::P);
         //w pawns
        tile[6][j]->piece=1;
        tile[6][j]->pieceColor=0;
        tile[6][j]->display(Piece::P);
    }
    //white and black remaining elements
    for(j=0;j<8;j++)
    {
        tile[0][j]->piece=1;
        tile[0][j]->pieceColor=1;
        tile[7][j]->piece=1;
        tile[7][j]->pieceColor=0;
    }
    {
    tile[0][0]->display(Piece::R);
    tile[0][1]->display(Piece::N);
    tile[0][2]->display(Piece::B);
    tile[0][3]->display(Piece::Q);
    tile[0][4]->display(Piece::K);
    tile[0][5]->display(Piece::B);
    tile[0][6]->display(Piece::N);
    tile[0][7]->display(Piece::R);
    }

    {
    tile[7][0]->display(Piece::R);
    tile[7][1]->display(Piece::N);
    tile[7][2]->display(Piece::B);
    tile[7][3]->display(Piece::Q);
    tile[7][4]->display(Piece::K);
    tile[7][5]->display(Piece::B);
    tile[7][6]->display(Piece::N);
    tile[7][7]->display(Piece::R);
    }
    Controller *c = new Controller();
    c->initializeGame(false);
    connect(this,SIGNAL(wantMove(QPoint,QPoint)),c,SLOT(makeMove(QPoint,QPoint)) );
    connect(c,SIGNAL(moveMade(QList<Player*>)),this,SLOT(setupedMove(QList<Player*>)));
}
void BoardVision::buttons(){
    QListWidget *listWgt = new QListWidget(baseWidget);
    DB *db = new DB();
    db->openDB();
    listWgt->setGeometry(900,590,150,60);
    listWgt->addItems(db->tableList());
    connect( listWgt, SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onListClicked(QListWidgetItem*)));
    QPushButton *dButton= new QPushButton("Загрузить партию",baseWidget);
    dButton->setGeometry(700,590,150,20);
    connect( dButton, SIGNAL(clicked()),this,SLOT(moveList()));
   QPushButton *saButton= new QPushButton("Сохранить партию",baseWidget);
    saButton->setGeometry(700,620,150,20);
   QPushButton *seButton= new QPushButton("Искать партию",baseWidget);
    seButton->setGeometry(700,650,150,20);
    db->closeDB();
}

void BoardVision::setupedMove(QList<Player*> pl){
    for(int i=7;i>=0;i--)
    {
        for(int j=0;j<8;j++)
        {
            tile[i][j]->piece=0;
            tile[i][j]->clear();
        }
     }
    for (int i=0; i<pl[0]->getPieces().length();i++){
        //qDebug() <<pl[0]->getPieces()[i]->getPosition();
    tile[pl[0]->getPieces()[i]->getPosition().y()-1][pl[0]->getPieces()[i]->getPosition().x()-1]->pieceColor=true;
    tile[pl[0]->getPieces()[i]->getPosition().y()-1][pl[0]->getPieces()[i]->getPosition().x()-1]->piece=1;
    tile[pl[0]->getPieces()[i]->getPosition().y()-1][pl[0]->getPieces()[i]->getPosition().x()-1]->display(pl[0]->getPieces()[i]->getType());
    }
    for (int i=0; i<pl[1]->getPieces().length();i++){
        //qDebug() <<pl[1]->getPieces()[i]->getPosition();
    tile[pl[1]->getPieces()[i]->getPosition().y()-1][pl[1]->getPieces()[i]->getPosition().x()-1]->pieceColor=false;
    tile[pl[1]->getPieces()[i]->getPosition().y()-1][pl[1]->getPieces()[i]->getPosition().x()-1]->piece=1;
    tile[pl[1]->getPieces()[i]->getPosition().y()-1][pl[1]->getPieces()[i]->getPosition().x()-1]->display(pl[1]->getPieces()[i]->getType());
    }
}

void BoardVision::tileClicked(QPoint p)
{
    tile[p.x()-1][p.y()-1]->checked=true;
    //qDebug()<<p.x()-1<<p.y()-1<<tile[p.x()-1][p.y()-1]->row <<tile[p.x()-1][p.y()-1]->col  <<tile[p.x()-1][p.y()-1]->checked;
    count++;
    fromto <<p;
    if(count==2){
        count=0;
        emit wantMove(fromto[0],fromto[1]);
        fromto.clear();
    }

}

void BoardVision::moveList()
{
    DB *db = new DB();
    db->openDB();
    //QLabel *moves = new QLabel(baseWidget);
    QTableWidget *moves = new QTableWidget(db->recordCount(table),2,baseWidget);
    moves->setGeometry(660,35,250,550);
    moves->setStyleSheet("QLabel {background-color: white;}");
    //QString t="";
    //t=table+'\n'+db->readMovesS(table)+'\n';
    //moves->setText(t);
    QPoint* p = new QPoint[2];
    for(int row=0; row!=moves->rowCount(); ++row){
        p=db->readMove(table,row);
        QTableWidgetItem *newItem = new QTableWidgetItem(db->intToChar(p[0].x())+QString::number(p[0].y()),QTableWidgetItem::Type);
        moves->setItem(row, 0, newItem);
        newItem = new QTableWidgetItem(db->intToChar(p[1].x())+QString::number(p[1].y()),QTableWidgetItem::Type);
        moves->setItem(row, 1, newItem);
    }
   // moves->selectRow(0);
    db->closeDB();
    moves->show();
    //moves->selectRow(3);
}
void BoardVision::onListClicked(QListWidgetItem *item){
    //qDebug() <<item->text();
    table=item->text();
}
