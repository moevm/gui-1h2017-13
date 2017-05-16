#include "controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
    delete board;
}

void Controller::initializeGame(bool viewType)
{
    board = Board::CreateBoard(viewType);
    createWhitePlayer();
    createBlackPlayer();
    currPlayerIndex = 0;
}

void Controller::refreshGame()
{
     bool prevt = board->getViewType();
     delete board;
     board = Board::CreateBoard(prevt);
     createWhitePlayer();
     createBlackPlayer();
     currPlayerIndex = 0;
}

void Controller::destroyGame()
{
    delete board;
    board = NULL;
}

void Controller::moveTransmission()
{
    if(currPlayerIndex + 1 < board->getPlayersAmount()){
        currPlayerIndex++;
    }
    else {
        currPlayerIndex = 0;
    }
}

void Controller::moveBackTransmission()
{
    if(currPlayerIndex < 1){
        currPlayerIndex = board->getPlayersAmount() - 1;
    }
    else {
        currPlayerIndex --;
    }
}

void Controller::createWhitePlayer()
{
    int playerIndex = board->getPlayersAmount() - 1;
    board->addPlayer();
    //king
    board->addPlayerPiece(playerIndex, Piece::K, QPoint(Board::e,1));
    kings.append(board->getPlayerPiece(playerIndex, QPoint(Board::e,1)));
    //queen
    board->addPlayerPiece(playerIndex, Piece::Q,QPoint(Board::d,1));
    //bishops
    board->addPlayerPiece(playerIndex, Piece::B,QPoint(Board::f,1));
    board->addPlayerPiece(playerIndex, Piece::B,QPoint(Board::c,1));
    //knights
    board->addPlayerPiece(playerIndex, Piece::N,QPoint(Board::g,1));
    board->addPlayerPiece(playerIndex, Piece::N,QPoint(Board::b,1));
    //rooks
    board->addPlayerPiece(playerIndex, Piece::R,QPoint(Board::h,1));
    board->addPlayerPiece(playerIndex, Piece::R,QPoint(Board::a,1));
    //pawns
    for(int i=Board::a; i<=Board::h; i++){
        board->addPlayerPiece(playerIndex, Piece::P,QPoint(i,2));
    }
}

void Controller::createBlackPlayer()
{
    int playerIndex = board->getPlayersAmount() - 1;
    board->addPlayer();
    //king
    board->addPlayerPiece(playerIndex, Piece::K, QPoint(Board::e,8));
    kings.append(board->getPlayerPiece(playerIndex, QPoint(Board::e,8)));
    //queen
    board->addPlayerPiece(playerIndex, Piece::Q,QPoint(Board::d,8));
    //bishops
    board->addPlayerPiece(playerIndex, Piece::B,QPoint(Board::f,8));
    board->addPlayerPiece(playerIndex, Piece::B,QPoint(Board::c,8));
    //knights
    board->addPlayerPiece(playerIndex, Piece::N,QPoint(Board::g,8));
    board->addPlayerPiece(playerIndex, Piece::N,QPoint(Board::b,8));
    //rooks
    board->addPlayerPiece(playerIndex, Piece::R,QPoint(Board::h,8));
    board->addPlayerPiece(playerIndex, Piece::R,QPoint(Board::a,8));
    //pawns
    for(int i=Board::a; i<=Board::h; i++){
        board->addPlayerPiece(playerIndex, Piece::P,QPoint(i,7));
    }
}

//Добавить проверку шаха/мата! сделано, не тестировалось
//Добавить удаление при сьедении фигуры! сделано, не тестировалось
//Добавить превращение пешки в фигуру после прохождения доски
//Обозначить ситуацию el passant и ограничить движение пешек взад-вперед
//Реализовать механизм рокировки
//
void Controller::makeMove( QPoint from,  QPoint to)
{
    if(board!=NULL)
    {
        Piece* copy = board->createCopy(to);
        int copyPlayerIndex = board->getPiecePlayerIndex(to);
        //if(!eatenPiece->isEmpty())
        //{
            //eatenPiece = Piece::CreatePiece(board->getViewType(),eatenPiece->getType(),eatenPiece->getPosition());
            board->deletePlayerPiece(copyPlayerIndex, to);
        //}
            //int KingXcoord = kings[currPlayerIndex]->getPosition().x();
        if(board->changePlayerPiecePosition(currPlayerIndex, from, to)){
            QPoint kingPosition = kings[currPlayerIndex]->getPosition();
            int prevPlayerIndex = currPlayerIndex;
            moveTransmission();
            if(board->isPlayerPieceUnderAttack(prevPlayerIndex, kingPosition)){ //check condition
                moveBackTransmission();
                if(!copy->isEmpty())
                {
                    board->addPlayerPiece(copyPlayerIndex, copy->getType(), copy->getPosition());
                    delete copy;
                }
            }
        }
        //qDebug()<<board->getPlayers();
       // emit moveMade(board->getPlayers());
    }
    else{
        qWarning("Game is not initialized!");
    }
}
