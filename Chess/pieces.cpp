#include "pieces.h"


King::MovePattern(QPoint newPos, const QVector <Piece*> &pieces)
{
    if( isOnBoard(newPos) && !isSamePosition(newPos) && abs(pos.x() - newPos.x()) <= 1 &&  abs(pos.y() - newPos.y()) <= 1)
        return true;
    else
        return false;
}

Queen::MovePattern(QPoint newPos, const QVector <Piece*> &pieces)
{
    if(isOnBoard(newPos) && !isSamePosition(newPos) &&
            (abs(pos.y() - newPos.y()) == 0 || abs(pos.x() - newPos.x()) == 0 ||  abs(pos.y() - newPos.y()) == abs(pos.x() - newPos.x()))
            )
    {
           for(int i =0; i< pieces.size(); i++)
               if(abs(pieces[i]->getPosition().y() -  newPos.y()) < abs(pos.y() - newPos.y()) ||
                       abs(pieces[i]->getPosition().x() -  newPos.x()) < abs(pos.x() -  newPos.x()) ||
                       (abs(pieces[i]->getPosition().x() -  newPos.x()) == abs(pieces[i]->getPosition().y() -  newPos.y()) &&
                       abs(pieces[i]->getPosition().x() -  newPos.x()) < abs(pos.x() - newPos.x())))
                   return false;
           return true;
       }
       else
           return false;
}

Rook::MovePattern(QPoint newPos, const QVector <Piece*> &pieces)
{
    if(isOnBoard(newPos) && !isSamePosition(newPos) &&
            (abs(pos.y() - newPos.y()) == 0 || abs(pos.x() - newPos.x()) == 0))
    {
           for(int i =0; i<pieces.length(); i++)
               if(abs(pieces[i]->getPosition().y() -  newPos.y()) < abs(pos.y() - newPos.y()) ||
                       abs(pieces[i]->getPosition().x() -  newPos.x()) < abs(pos.x() -  newPos.x()))
                   return false;
           return true;
       }
       else
           return false;
}

Bishop::MovePattern(QPoint newPos, const QVector <Piece*> &pieces)
{
    if(isOnBoard(newPos) && !isSamePosition(newPos) &&
            abs(pos.y() - newPos.y()) == abs(pos.x() - newPos.x()) )
    {
           for(int i =0; i<pieces.length(); i++)
               if(abs(pieces[i]->getPosition().x() -  newPos.x()) == abs(pieces[i]->getPosition().y() -  newPos.y()) &&
                      abs(pieces[i]->getPosition().x() -  newPos.x()) < abs(pos.x() - newPos.x()) )
                   return false;
           return true;
       }
       else
           return false;
}

Knight::MovePattern(QPoint newPos, const QVector <Piece*> &pieces)
{
    if(isOnBoard(newPos) && !isSamePosition(newPos) &&
            ((abs(pos.y() - newPos.y()) == 2 &&  abs(pos.x() - newPos.x()) == 1)
             || (abs(pos.x() - newPos.x()) == 2 &&  abs(pos.y() - newPos.y()) == 1)))
           return true;
       else
           return false;
}

Pawn::MovePattern(QPoint newPos, const QVector <Piece*> &pieces)
{
   if (isOnBoard(newPos) && !isSamePosition(newPos)){
       if(newPos.y() - pos.y() == 1 && newPos.x() - pos.x() == 0){
        for(int i =0; i<pieces.length(); i++)
            if(pieces[i]->getPosition().x() == newPos.x() && pieces[i]->getPosition().y() == newPos.y())
                return false;
        return true;
       }
       else{
           if(newPos.y() - pos.y() == 1 && abs(newPos.x() - pos.x()) == 1){
           for(int i =0; i<pieces.length(); i++)
               if(pieces[i]->getPosition().x() == newPos.x() && pieces[i]->getPosition().y() == newPos.y())
                   return true;
           }
           return false;
       }
   }
   else
       return false;
}
