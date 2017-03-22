#ifndef PIECES_H
#define PIECES_H
#include <QPoint>
#include <QVector>

enum PieceType {K, Q, R, B, N, P}; //King, queen, rook, bishop, knight, pawn
enum l_letters {a = 1, b, c, d, e, f, g, h}; //

class Piece
{
protected:
    QPoint pos;
    PieceType type;
public:
    bool isOnBoard(QPoint pos){
        return (1 <= pos.y() && pos.y() <= 8 && a <= pos.x() && pos.x() <= h);
    }
    bool isSamePosition(QPoint pos){
        return Piece::pos.x() == pos.x() && Piece::pos.y() == pos.y();
    }
    QPoint getPosition(){return pos;}
    void setPosition(QPoint pos){
        if(isOnBoard(pos) && !isSamePosition(pos))
            Piece::pos = pos;
    }
    PieceType getType(){return type;}
    virtual MovePattern(QPoint newPos, const QVector <Piece*> &pieces) = 0;
};

#endif // PIECES_H

class King : Piece
{
    public:
    King(QPoint pos){
        if(isOnBoard(pos))
            Piece::pos = pos;
        type = K;
    }
    MovePattern(QPoint newPos, const QVector <Piece*> &pieces);
};

class Queen : Piece
{
    public:
    Queen(QPoint pos){
        if(isOnBoard(pos))
            Piece::pos = pos;
        type = Q;
    }
    MovePattern(QPoint newPos, const QVector <Piece*> &pieces);
};

class Rook : Piece
{
    public:
    Rook(QPoint pos){
        if(isOnBoard(pos))
            Piece::pos = pos;
        type = R;
    }
    MovePattern(QPoint newPos, const QVector <Piece*> &pieces);
};

class Bishop : Piece
{
    public:
    Bishop(QPoint pos){
        if(isOnBoard(pos))
            Piece::pos = pos;
        type = B;
    }
    MovePattern(QPoint newPos, const QVector <Piece*> &pieces);
};

class Knight : Piece
{
    public:
    Knight(QPoint pos){
        if(isOnBoard(pos))
            Piece::pos = pos;
        type = N;
    }
    MovePattern(QPoint newPos, const QVector <Piece*> &pieces);
};

class Pawn : Piece
{
    public:
    Pawn(QPoint pos){
        if(isOnBoard(pos))
            Piece::pos = pos;
        type = P;
    }
    MovePattern(QPoint newPos, const QVector <Piece*> &pieces);
};
