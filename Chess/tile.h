#ifndef TILE_H
#define TILE_H
#include <QLabel>
#include <QDebug>

class Tile: public QLabel
{
     Q_OBJECT
public:

    //Fields
    int tileColor,piece,pieceColor,row,col,tileNum;
    bool checked=false;
    char pieceName;

    //Constructors
    Tile(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {}
    Tile(const QString& text, QWidget* pParent = 0, Qt::WindowFlags f = 0) : QLabel(text, pParent, f){}

    //Methods
    void display(char elem);
    void tileDisplay();
    void mousePressEvent(QMouseEvent* event) {
           emit clicked(QPoint(row+1,col+1));
        }
signals:
    void clicked(QPoint p);
public slots:
    void slotClicked()
{
    qDebug()<<row << col;
}

};
//
#endif // TILE_H
