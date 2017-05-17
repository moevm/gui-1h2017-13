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
    color= new Tile(baseWidget);
    color->tileColor=0;
    color->piece=0;
    color->row=0;
    color->col=0;
    color->tileNum=0;
    color->tileDisplay();
    color->setGeometry(30,620,50,50);
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

    c = new Controller();
    c->initializeGame(false);
    connect(this,SIGNAL(wantMove(QPoint,QPoint)),c,SLOT(makeMove(QPoint,QPoint)) );
    connect(c,SIGNAL(moveMade(QList<Player*>,unsigned int)),this,SLOT(setupedMove(QList<Player*>,unsigned int)));
}
void BoardVision::buttons(){
    listWgt = new QListWidget(baseWidget);
    DB *db = new DB();
    db->openDB();
    listWgt->setGeometry(900,590,150,60);
    listWgt->addItems(db->tableList());
    connect( listWgt, SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onListClicked(QListWidgetItem*)));
    QPushButton *dButton= new QPushButton("Загрузить партию",baseWidget);
    dButton->setGeometry(700,590,150,20);
    connect( dButton, SIGNAL(clicked()),this,SLOT(moveList()));

    QPushButton *backButton= new QPushButton("<",baseWidget);
    backButton->setGeometry(400,600,50,20);
    connect( backButton, SIGNAL(clicked()),this,SLOT(backMove()));
    QPushButton *nextButton= new QPushButton(">",baseWidget);
    nextButton->setGeometry(550,600,50,20);
    connect( nextButton, SIGNAL(clicked()),this,SLOT(nextMove()));
    QPushButton *clearButton= new QPushButton("Очистить",baseWidget);
    clearButton->setGeometry(450,600,90,20);
    connect( clearButton, SIGNAL(clicked()),this,SLOT(clearBoard()));

   QPushButton *saButton= new QPushButton("Сохранить партию",baseWidget);
    saButton->setGeometry(700,620,150,20);
   QPushButton *seButton= new QPushButton("Искать партию",baseWidget);
    seButton->setGeometry(700,650,150,20);
    db->closeDB();
}
void BoardVision::initBoard(){
    for(int i=7;i>=0;i--)
    {
        for(int j=0;j<8;j++)
        {
            tile[i][j]->piece=0;
            tile[i][j]->clear();
        }
     }
    for(int j=0;j<8;j++)
    {
        tile[1][j]->piece=1;
        tile[1][j]->pieceColor=1;
        tile[1][j]->display(Piece::P);
         //w pawns
        tile[6][j]->piece=1;
        tile[6][j]->pieceColor=0;
        tile[6][j]->display(Piece::P);
    }
    for(int j=0;j<8;j++)
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
}

void BoardVision::clearBoard(){
    c->refreshGame();
    //index=-1;
    //color->tileColor=0;
    //movesTable->clear();
    //initBoard();
}

void BoardVision::backMove(){
    if(index>0){
        DB *db = new DB();
        db->openDB();
        QPoint* moves = new QPoint[2];
        index--;
        moves=db->readMove(table,index && table !="");
        movesTable->selectRow(index);
        db->closeDB();
        emit wantMove(moves[1],moves[0]);
    }
}

void BoardVision::nextMove(){
    DB *db = new DB();
    db->openDB();
    if(index<db->recordCount(table) && table !=""){
        QPoint* moves = new QPoint[2];
    index++;
    moves=db->readMove(table,index);
    movesTable->selectRow(index);
    emit wantMove(moves[0],moves[1]);
    }
    db->closeDB();
}
void BoardVision::setupedMove(QList<Player*> pl,unsigned int play){
    for(int i=7;i>=0;i--)
    {
        for(int j=0;j<8;j++)
        {
            tile[i][j]->piece=0;
            tile[i][j]->clear();
        }
     }
    color->tileColor=play;
    color->tileDisplay();
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
    //qDebug()<<p.x()-1<<p.y()-1<<tile[p.x()-1][p.y()-1]->row <<tile[p.x()-1][p.y()-1]->col  <<tile[p.x()-1][p.y()-1]->checked;
    fromto <<p;
    if(tile[fromto[0].y()-1][fromto[0].x()-1]->piece){
        tile[fromto[0].y()-1][fromto[0].x()-1]->checked=true;
        tile[fromto[0].y()-1][fromto[0].x()-1]->tileDisplay();
    }
    if(fromto.length()>0 && fromto[0]!=p){
        count++;
        if(count==2){
            count=1;
           // qDebug()<<tile[fromto[0].y()-1][fromto[0].x()-1]->piece;
            if(tile[fromto[0].y()-1][fromto[0].x()-1]->piece)
            {
                tile[p.y()-1][p.x()-1]->checked=true;
                tile[p.y()-1][p.x()-1]->tileDisplay();
                emit wantMove(fromto[0],p);
                tile[p.y()-1][p.x()-1]->checked=false;
                tile[p.y()-1][p.x()-1]->tileDisplay();
                tile[fromto[0].y()-1][fromto[0].x()-1]->checked=false;
                tile[fromto[0].y()-1][fromto[0].x()-1]->tileDisplay();
            }
            fromto.clear();
        }
    }
}

void BoardVision::moveList()
{
    DB *db = new DB();
    db->openDB();
    //QLabel *moves = new QLabel(baseWidget);
    movesTable = new QTableWidget(db->recordCount(table),2,baseWidget);
    movesTable->setGeometry(660,35,250,550);
    movesTable->setStyleSheet("QLabel {background-color: white;}");
    //QString t="";
    //t=table+'\n'+db->readMovesS(table)+'\n';
    //moves->setText(t);
    QPoint* p = new QPoint[2];
    for(int row=0; row!=movesTable->rowCount(); ++row){
        p=db->readMove(table,row);
        QTableWidgetItem *newItem = new QTableWidgetItem(db->intToChar(p[0].x())+QString::number(p[0].y()),QTableWidgetItem::Type);
        movesTable->setItem(row, 0, newItem);
        newItem = new QTableWidgetItem(db->intToChar(p[1].x())+QString::number(p[1].y()),QTableWidgetItem::Type);
        movesTable->setItem(row, 1, newItem);
    }
   // moves->selectRow(0);
    db->closeDB();
    movesTable->show();
    //moves->selectRow(3);
}
void BoardVision::onListClicked(QListWidgetItem *item){
    //qDebug() <<item->text();
    table=item->text();
}
