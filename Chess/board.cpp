#include "board.h"

const QList <Piece *> Board::getPieces()
{
    QList <Piece*> temp;
    for(int i=0; i<players.length(); i++){
        temp.append(players[i]->pieces);
    }
    return temp;
}

bool Board::isPlayerIndexCorrect(const int &playerIndex)
{
    return playerIndex > 0 && playerIndex < players.length();
}

bool Board::isOnBoard(Piece *p)
{
    return  (1 <= p->getPosition().y() && p->getPosition().y() <= 8 &&
             a <= p->getPosition().x() && p->getPosition().x() <= h);
}

Board *Board::CreateSimpleBoard(bool boardType){
    Board* b  = new Board();
    b->piecesType = boardType;
    return b;
}

Board *Board::CreateGraphicBoard(bool boardType)
{
}

Board *Board::CreateBoard(bool isGraphic)
{
    //if(isGraphic)
        //return CreateGraphicBoard(isGraphic);
    //else
        return CreateSimpleBoard(isGraphic);
}

void Board::addPlayer(const Player& p)
{
    players.append(new Player(p));
}

bool Board::deletePlayer(const int &playerIndex)
{
    if(!isPlayerIndexCorrect(playerIndex)){
        return false;
    }
    players.removeAt(playerIndex);
    return true;
}

bool Board::addPiece(Piece *p, const int &playerIndex)
{
    if(!isPlayerIndexCorrect(playerIndex) || !isOnBoard(p)){
        return false;
    }
    for(int i=0; i<players.length(); i++){
        for(int j=0; j<players[i]->pieces.length(); j++){
            if(players[i]->pieces[j]->getPosition() == p->getPosition()){
                return false;
            }
        }
    }
    players[playerIndex]->pieces.append(Piece::CreatePiece(piecesType, p->getType(), p->getPosition()));
    return true;
}

bool Board::deletePiece(const QPoint &pos)
{
    for(int i=0; i<players.length(); i++){
        for(int j=0; j<players[i]->pieces.length(); j++){
            if(players[i]->pieces[j]->getPosition() == pos){
                players[i]->pieces.removeAt(j);
                return true;
            }
        }
    }
    return false;
}



