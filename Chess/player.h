#ifndef PLAYER_H
#define PLAYER_H

#include <pieces.h>
#include <QObject>

class Player : public QObject
{
    Q_OBJECT

    friend class Board;
    QList <Piece*> pieces;

signals:
    pieceChosen(QPoint pos);
    moveGenerated(QPoint pos);

private slots:
    void choosePiece(QPoint pos);
    void generateMove(QPoint pos);

public:
    Player();
    ~Player();
    Player(Player const& p);
};

#endif // PLAYER_H
