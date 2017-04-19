#ifndef PIECES_H
#define PIECES_H
#include <QPoint>
#include <QList>

enum PieceType {K, Q, R, B, N, P}; //King, queen, rook, bishop, knight, pawn

class Piece
{
public:
    virtual ~Piece();
    static Piece *CreatePiece(bool isGraphic,PieceType type, QPoint pos = QPoint());
    bool isSamePosition(QPoint pos);
    QPoint getPosition();
    void setPosition(QPoint pos);
    PieceType getType();
    virtual MovePattern(QPoint newPos, const QList <Piece*> &pieces) = 0;
private:
    //Factory methods
    static Piece *CreateSimplePiece(PieceType type, QPoint pos = QPoint());
    // Empty graphic factory method
    static Piece *CreateGraphicPiece(PieceType type, QPoint pos = QPoint());
protected:
    QPoint pos;
    PieceType type;
};

class King : public Piece
{
    public:
    King(QPoint pos = QPoint());
    ~King();
    MovePattern(QPoint newPos, const QList <Piece*> &pieces);
};

class Queen : public Piece
{
    public:
    Queen(QPoint pos = QPoint());
    ~Queen();
    MovePattern(QPoint newPos, const QList <Piece*> &pieces);
};

class Rook : public Piece
{
    public:
    Rook(QPoint pos = QPoint());
    ~Rook();
    MovePattern(QPoint newPos, const QList <Piece*> &pieces);
};

class Bishop : public Piece
{
    public:
    Bishop(QPoint pos = QPoint());
    ~Bishop();
    MovePattern(QPoint newPos, const QList <Piece*> &pieces);
};

class Knight : public Piece
{
    public:
    Knight(QPoint pos = QPoint());
    ~Knight();
    MovePattern(QPoint newPos, const QList <Piece*> &pieces);
};

class Pawn : public Piece
{
    public:
    Pawn(QPoint pos = QPoint());
    ~Pawn();
    MovePattern(QPoint newPos, const QList <Piece*> &pieces);
};

#endif // PIECES_H
