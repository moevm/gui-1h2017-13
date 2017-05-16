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
    board->addPlayer();
    int playerIndex = board->getPlayersAmount() - 1;
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
    board->addPlayer();
    int playerIndex = board->getPlayersAmount() - 1;
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
//Реализовать механизм рокировки сделано, не тестировалось
//Ограничить движение пешки только вперед для каждого из игроков
//Добавить превращение пешки в фигуру после прохождения доски
//Обозначить ситуацию el passant
void Controller::makeMove(const QPoint &from, const QPoint& to)
{
    if(board!=NULL)
    {
        Piece* pieceToMove = board->getPlayerPiece(currPlayerIndex, from);
        if(!pieceToMove->isEmpty()){ // "empty" clicks block
            Piece* pieceToMoveCopy = board->createCopy(from);
            Piece* pieceToEatCopy = board->createCopy(to);
            unsigned int pieceToEatCopyPlayerIndex = board->getPiecePlayerIndex(to);
            if(!pieceToEatCopy->isEmpty() && pieceToEatCopyPlayerIndex != currPlayerIndex && from!=to)
            {
                board->deletePlayerPiece(pieceToEatCopyPlayerIndex, to);
            }
            //QPoint kingPrevPosition = kings[currPlayerIndex]->getPosition();

            if(board->changePlayerPiecePosition(currPlayerIndex, from, to)){ //move
                QPoint kingPosition = kings[currPlayerIndex]->getPosition();
                int prevPlayerIndex = currPlayerIndex;
                moveTransmission();

                switch(pieceToMoveCopy->getType())
                {
                case Piece::K:
                    // casteling condition
                    if(pieceToMoveCopy->getPosition().x() - pieceToMove->getPosition().x() == 2)// left casteling
                    {
                        Piece* kingCopy = board->createCopy(to);
                        board->deletePlayerPiece(prevPlayerIndex, to);
                        board->changePlayerPiecePosition(prevPlayerIndex, QPoint(Board::a, kingCopy->getPosition().y()), QPoint(kingCopy->getPosition().x()+1,kingCopy->getPosition().y()));
                        board->addPlayerPiece(prevPlayerIndex, kingCopy->getType(), kingCopy->getPosition(), kingCopy->getState());
                        kings[prevPlayerIndex] = board->getPlayerPiece(prevPlayerIndex, to);
                        delete kingCopy;
                    }
                    else if(pieceToMoveCopy->getPosition().x() - pieceToMove->getPosition().x() == -2)// right casteling
                    {
                        Piece* kingCopy = board->createCopy(to);
                        board->deletePlayerPiece(prevPlayerIndex, to);
                        board->changePlayerPiecePosition(prevPlayerIndex, QPoint(Board::h, kingCopy->getPosition().y()), QPoint(kingCopy->getPosition().x()-1,kingCopy->getPosition().y()));
                        board->addPlayerPiece(prevPlayerIndex, kingCopy->getType(), kingCopy->getPosition(), kingCopy->getState());
                        kings[prevPlayerIndex] = board->getPlayerPiece(prevPlayerIndex, to);
                        delete kingCopy;
                    }
                    break;
                case Piece::P:
                    //Pawns movement processing

                    /*if((abs(diffY) == 1 || abs(diffY) == 2) && diffX == 0){
                     for(int i =0; i<pieces.length(); i++){
                         int diffIntersectsX = pieces[i]->getPosition().x() -  newPos.x();
                         int diffIntersectsY = pieces[i]->getPosition().y() -  newPos.y();
                         if(diffIntersectsX == 0 && diffIntersectsY == 0 && pieces[i]->getType()==P)
                             return false;
                     }
                     return true;
                    } else{
                        if(abs(diffY) == 1 && abs(diffX) == 1)
                        {
                             for(int i =0; i<pieces.length(); i++)
                             {
                                 int diffIntersectsX = pieces[i]->getPosition().x() -  newPos.x();
                                 int diffIntersectsY = pieces[i]->getPosition().y() -  newPos.y();
                                 if((diffIntersectsX == 0 && diffIntersectsY == 0) ||
                                         (abs(diffIntersectsX) == 0 && abs(diffIntersectsY) == 1))
                                     return true;
                             }
                       }
                        return false;
                    }
                }
                 return false;*/
                    break;
                default:
                    break;
                }

                if(board->isPlayerPieceUnderAttack(prevPlayerIndex, kingPosition)){ //check condition
                    moveBackTransmission();
                    board->changePlayerPiecePosition(currPlayerIndex, to, from);
                    if(!pieceToEatCopy->isEmpty())
                    {
                        board->addPlayerPiece(pieceToEatCopyPlayerIndex, pieceToEatCopy->getType(), pieceToEatCopy->getPosition(), pieceToEatCopy->getState());
                        delete pieceToEatCopy;
                    }
                }
            }
            else
            {
                board->addPlayerPiece(pieceToEatCopyPlayerIndex, pieceToEatCopy->getType(), pieceToEatCopy->getPosition(), pieceToEatCopy->getState());
            }
            delete pieceToMoveCopy;
            delete pieceToEatCopy;
            emit moveMade(board->getPlayers(), currPlayerIndex);
        }
        else{
            delete pieceToMove;
        }
    }
    else{
        qWarning("Game is not initialized!");
    }
}
