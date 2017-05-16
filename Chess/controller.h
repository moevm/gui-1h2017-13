#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "board.h"
#include <QObject>
#include <QDebug>
class Controller : public QObject
{
    Q_OBJECT
public:
    Controller();
    ~Controller();
    void initializeGame(bool viewType);
    void refreshGame();
    void destroyGame();

private:
    Board* board;
    QList <Piece* > kings;
    unsigned currPlayerIndex;
    void moveTransmission();
    void moveBackTransmission();
    void createWhitePlayer();
    void createBlackPlayer();

public slots:
    void makeMove(QPoint from, QPoint to);

signals:
    void moveMade(QList <Player* > players);
};
//
#endif // CONTROLLER_H
