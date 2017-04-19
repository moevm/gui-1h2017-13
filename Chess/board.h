#ifndef BOARD_H
#define BOARD_H

#include <player.h>

enum l_letters {a = 1, b, c, d, e, f, g, h};

class Board
{
    QList <Player* > players;
    bool piecesType; // false means simple(console) and true means graphic
private:
     Board(){};
     bool isPlayerIndexCorrect(const int &playerIndex);
     bool isOnBoard(Piece *p);
    //Factory methods
    static Board *CreateSimpleBoard(bool boardType);
    // Empty graphic factory method
    static Board *CreateGraphicBoard(bool boardType);
public:
    static Board* CreateBoard(bool isGraphic);
    const QList <Piece*> getPieces();
    void addPlayer(const Player &p);
    bool deletePlayer(const int &playerIndex);
    bool addPiece(Piece *p, const int &playerIndex);
    bool deletePiece(const QPoint &pos);
};

#endif // BOARD_H
