#include "boardvision.h"

BoardVision::BoardVision(QWidget *widget)
{
    int i,j,k=0,hor,ver;
    Border *border[4]={ NULL };
    baseWidget=widget;
    //borderDisplay
    {
    border[0]->outline(baseWidget,80,45,0);
    border[1]->outline(baseWidget,80,577,0);
    border[2]->outline(baseWidget,80,65,1);
    border[2]->outline(baseWidget,612,65,1);
    }
    kLabel = new QLabel("",baseWidget);
    kLabel->setGeometry(300,20,40,20);

    //Create 64 tiles (allocating memories to the objects of Tile class)
    ver=65;
    color= new Tile(baseWidget);
    color->tileColor=0;
    color->piece=0;
    color->row=0;
    color->col=0;
    color->tileNum=0;
    color->tileDisplay();
    color->setGeometry(30,620,50,50);
    QLabel *playerLabel = new QLabel("Игрок:",baseWidget);
    playerLabel->setGeometry(30,590,60,20);
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
    connect(c,SIGNAL(moveMade(QList<Player*>,unsigned int,bool)),this,SLOT(setupedMove(QList<Player*>,unsigned int,bool)));
}

BoardVision::~BoardVision(){
    db->openDB();
    db->deleteTable(currTable);
    db->closeDB();
}

void BoardVision::buttons(){
    QLabel *partLabel = new QLabel("Партии:",baseWidget);
    partLabel->setGeometry(930,570,80,20);
    listWgt = new QListWidget(baseWidget);
    db->openDB();
    listWgt->setGeometry(930,590,100,60);
    listWgt->addItems(db->tableList());
    connect( listWgt, SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onListClicked(QListWidgetItem*)));

    currTable="Save_"+QString::number(QDate::currentDate().day())+'_'+QString::number(QDate::currentDate().month());
    if(db->containsTable(currTable))
    {
        saveInd++;
        currTable="Save_"+QString::number(QDate::currentDate().day())+'_'+QString::number(QDate::currentDate().month())+"_"+QString::number(saveInd);
    }
    db->createTable(currTable);
    //qDebug() << db->tableList();

    QPushButton *dButton= new QPushButton("Загрузить партию",baseWidget);
    dButton->setGeometry(700,590,150,20);
    connect( dButton, SIGNAL(clicked()),this,SLOT(moveList()));

    //QPushButton *backButton= new QPushButton("<",baseWidget);
    //backButton->setGeometry(400,600,50,20);
   // connect( backButton, SIGNAL(clicked()),this,SLOT(backMove()));
    QPushButton *nextButton= new QPushButton(">",baseWidget);
    nextButton->setGeometry(550,600,50,20);
    connect( nextButton, SIGNAL(clicked()),this,SLOT(nextMove()));
    //if(movesTable==nullptr) nextButton->setEnabled(false);
    //else nextButton->setEnabled(true);

    QPushButton *clearButton= new QPushButton("Очистить",baseWidget);
    clearButton->setGeometry(455,600,90,20);
    connect( clearButton, SIGNAL(clicked()),this,SLOT(clearBoard()));

   QPushButton *saButton= new QPushButton("Сохранить партию",baseWidget);
    saButton->setGeometry(700,620,150,20);
    connect( saButton, SIGNAL(clicked()),this,SLOT(savedMoves()));
   QPushButton *seButton= new QPushButton("Удалить партию",baseWidget);
   seButton->setGeometry(700,650,150,20);
   connect( seButton, SIGNAL(clicked()),this,SLOT(deletedMoves()));
    db->closeDB();
}

void BoardVision::savedMoves(){
   db->openDB();
    listWgt->addItem(currTable);
    saveInd++;
    currTable="Save_"+QString::number(QDate::currentDate().day())+'_'+QString::number(QDate::currentDate().month())+"_"+QString::number(saveInd);
     db->createTable(currTable);
   db->closeDB();
}

void BoardVision::deletedMoves(){
    listWgt->clear();
    db->openDB();
    db->deleteTable(table);
    QStringList sl =db->tableList();
    //sl.removeLast();
    listWgt->addItems(sl);
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
    index=-1;
    db->openDB();
    db->deleteTable(currTable);
    db->createTable(currTable);
    db->closeDB();
}

void BoardVision::backMove(){
    if(index>-1){
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
void BoardVision::setupedMove(QList<Player*> pl,unsigned int play, bool k){

    QFont font = kLabel->font();
    font.setPointSize(14);
    kLabel->setFont(font);
    kLabel->show();
    if(k)
       kLabel->setText("Шах!");
    else
       kLabel->clear();
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
    fromto <<p;
    if(tile[fromto[0].y()-1][fromto[0].x()-1]->piece){
        tile[fromto[0].y()-1][fromto[0].x()-1]->checked=true;
        tile[fromto[0].y()-1][fromto[0].x()-1]->tileDisplay();
    }
    if(fromto.length()>0 && fromto[0]!=p){
        count++;
        if(count==2){
            count=1;
            if(tile[fromto[0].y()-1][fromto[0].x()-1]->piece)
            {
                tile[p.y()-1][p.x()-1]->checked=true;
                tile[p.y()-1][p.x()-1]->tileDisplay();
                db->openDB();
                db->writeMove(currTable,fromto[0],p);
                db->closeDB();
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
    db->openDB();
    //QLabel *moves = new QLabel(baseWidget);
    movesTable = new QTableWidget(db->recordCount(table),2,baseWidget);
    movesTable->setGeometry(660,35,250,550);
    movesTable->setStyleSheet("QLabel {background-color: white;}");
    movesTable->setHorizontalHeaderLabels(QStringList() << "Откуда" << "Куда");
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
