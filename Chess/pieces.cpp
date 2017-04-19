#include "pieces.h"

Piece *Piece::CreateSimplePiece(PieceType type, QPoint pos)
{
    switch(type){
    case K:
        return new King(pos);
        break;
    case Q:
        return new Queen(pos);
        break;
    case R:
        return new Rook(pos);
        break;
    case B:
        return new Bishop(pos);
        break;
    case N:
        return new Knight(pos);
        break;
    case P:
        return new Pawn(pos);
        break;
    default: return NULL;
    }
}

Piece::~Piece()
{

}

Piece *Piece::CreatePiece(bool isGraphic, PieceType type, QPoint pos)
{
    //if(isGraphic)
        //return CreateGraphicPiece(type, pos);
    //else
        return CreateSimplePiece(type, pos);
}

bool Piece::isSamePosition(QPoint pos){
    return Piece::pos.x() == pos.x() && Piece::pos.y() == pos.y();
}

QPoint Piece::getPosition(){
    return pos;
}

void Piece::setPosition(QPoint pos){
    if(!isSamePosition(pos))
        Piece::pos = pos;
}

PieceType Piece::getType(){
    return type;
}

King::King(QPoint pos){
    Piece::pos = pos;
    type = K;
}

King::~King()
{

}

King::MovePattern(QPoint newPos, const QList <Piece*> &pieces)
{
    if(!isSamePosition(newPos) && abs(pos.x() - newPos.x()) <= 1 &&  abs(pos.y() - newPos.y()) <= 1)
        return true;
    else
        return false;
}

Queen::Queen(QPoint pos){
    Piece::pos = pos;
    type = Q;
}

Queen::~Queen()
{

}

Queen::MovePattern(QPoint newPos, const QList <Piece*> &pieces)
{
    int diffX = pos.x() -  newPos.x();
    int diffY = pos.y() - newPos.y();
    if(!isSamePosition(newPos) && (abs(diffY) == 0 || abs(diffX) == 0 ||  abs(diffY) == abs(diffX)))
         {
                for(int i =0; i< pieces.size(); i++){
                    int diffIntersectsX = pieces[i]->getPosition().x() -  newPos.x();
                    int diffIntersectsY = pieces[i]->getPosition().y() -  newPos.y();
                    if(abs(diffIntersectsY) < abs(diffY) ||
                            abs(diffIntersectsX) < abs(diffX) ||
                            (abs(diffIntersectsX) == abs(diffIntersectsY) &&
                            abs(diffIntersectsX) < abs(diffX))){
                        return false;
                    }
                }
                return true;
    } else {
        return false;
    }
}

Rook::Rook(QPoint pos){
    Piece::pos = pos;
    type = R;
}

Rook::~Rook()
{

}

Rook::MovePattern(QPoint newPos, const QList <Piece*> &pieces)
{
    int diffX = pos.x() -  newPos.x();
    int diffY = pos.y() - newPos.y();
    if(!isSamePosition(newPos) &&
            (abs(diffY) == 0 || abs(diffX) == 0))
    {
           for(int i =0; i<pieces.length(); i++){
               int diffIntersectsX = pieces[i]->getPosition().x() -  newPos.x();
               int diffIntersectsY = pieces[i]->getPosition().y() -  newPos.y();
               if(abs(diffIntersectsY) < abs(diffY) ||
                       abs(diffIntersectsX) < abs(diffX))
                   return false;
           }
           return true;
       }
       else
           return false;
}

Bishop::Bishop(QPoint pos){
    Piece::pos = pos;
    type = B;
}

Bishop::~Bishop()
{

}

Bishop::MovePattern(QPoint newPos, const QList <Piece*> &pieces)
{
    int diffX = pos.x() -  newPos.x();
    int diffY = pos.y() - newPos.y();
    if(!isSamePosition(newPos) &&
            abs(diffY) == abs(diffX) )
    {
           for(int i =0; i<pieces.length(); i++){
               int diffIntersectsX = pieces[i]->getPosition().x() -  newPos.x();
               int diffIntersectsY = pieces[i]->getPosition().y() -  newPos.y();
               if(abs(diffIntersectsX) == abs(diffIntersectsY) &&
                      abs(diffIntersectsX) < abs(diffX) )
                   return false;
           }
           return true;
       }
       else
           return false;
}

Knight::Knight(QPoint pos){
    Piece::pos = pos;
    type = N;
}

Knight::~Knight()
{

}

Knight::MovePattern(QPoint newPos, const QList <Piece*> &pieces)
{
    int diffX = pos.x() -  newPos.x();
    int diffY = pos.y() - newPos.y();
    if(!isSamePosition(newPos) &&
            ((abs(diffY) == 2 &&  abs(diffX) == 1)
             || (abs(diffX) == 2 &&  abs(diffY) == 1)))
           return true;
       else
           return false;
}

Pawn::Pawn(QPoint pos){
    Piece::pos = pos;
    type = P;
}

Pawn::~Pawn()
{

}

Pawn::MovePattern(QPoint newPos, const QList <Piece*> &pieces)
{
    int diffX = newPos.x() - pos.x();
    int diffY = newPos.y() - pos.y();
    if (!isSamePosition(newPos)){
       if(diffY == 1 && diffX == 0){
        for(int i =0; i<pieces.length(); i++){
            int diffIntersectsX = pieces[i]->getPosition().x() -  newPos.x();
            int diffIntersectsY = pieces[i]->getPosition().y() -  newPos.y();
            if(diffIntersectsX == 0 && diffIntersectsY == 0)
                return false;
        }
        return true;
       } else{
           if(diffY == 1 && abs(diffX) == 1){
           for(int i =0; i<pieces.length(); i++){
               int diffIntersectsX = pieces[i]->getPosition().x() -  newPos.x();
               int diffIntersectsY = pieces[i]->getPosition().y() -  newPos.y();
               if(diffIntersectsX == 0 && diffIntersectsY == 0)
                   return true;
           }
          }
           return false;
       }
   }
   else
       return false;
}
