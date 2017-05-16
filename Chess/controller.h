#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "board.h"
#include <QObject>

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
    void makeMove(const QPoint &from, const QPoint &to);

signals:
    void moveMade(QList <Player* > players);
};

#endif // CONTROLLER_H
