#include "tile.h"

extern int count,turn;
extern QWidget *myWidget;
extern Tile *click1;
extern Tile *tile[8][8];

void Tile::display(char elem)
{
    this->pieceName=elem;

    if(this->pieceColor && this->piece)
    {
        switch(elem)
        {
            case 'P': this->setPixmap(QPixmap(":/Images/pawn_white.svg"));
                      break;
            case 'R': this->setPixmap(QPixmap(":/Images/rook_white.svg"));
                      break;
            case 'H': this->setPixmap(QPixmap(":/Images/knight_white.svg"));
                      break;
            case 'K': this->setPixmap(QPixmap(":/Images/king_white.svg"));
                      break;
            case 'Q': this->setPixmap(QPixmap(":/Images/queen_white.svg"));
                      break;
            case 'B': this->setPixmap(QPixmap(":/Images/bishop_white.svg"));
                      break;
        }
    }

    else if(this->piece)
    {
        switch(elem)
        {
        case 'P': this->setPixmap(QPixmap(":/Images/pawn_black.svg"));
                  break;
        case 'R': this->setPixmap(QPixmap(":/Images/rook_black.svg"));
                  break;
        case 'H': this->setPixmap(QPixmap(":/Images/knight_black.svg"));
                  break;
        case 'K': this->setPixmap(QPixmap(":/Images/king_black.svg"));
                  break;
        case 'Q': this->setPixmap(QPixmap(":/Images/queen_black.svg"));
                  break;
        case 'B': this->setPixmap(QPixmap(":/Images/bishop_black.svg"));
                  break;
        }
    }
    else
        this->clear();
}

void Tile::tileDisplay()
{

    if(this->tileColor)
        this->setStyleSheet("QLabel {background-color: rgb(120, 120, 90);}:hover{background-color: rgb(170,85,127);}");
    else
        this->setStyleSheet("QLabel {background-color: rgb(211, 211, 158);}:hover{background-color: rgb(170,95,127);}");
}
