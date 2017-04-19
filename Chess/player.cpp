#include "player.h"

void Player::choosePiece(QPoint pos)
{
    emit pieceChosen(pos);
}

void Player::generateMove(QPoint pos)
{
    emit moveGenerated(pos);
}

Player::Player()
{

}

Player::Player(const Player &p)
{
    pieces = p.pieces;
}


Player::~Player()
{
    for(int i=0; i<pieces.length(); i++){
        delete pieces[i];
    }
}
