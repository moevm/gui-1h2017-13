#ifndef DB_H
#define DB_H

#include <QDebug>
#include <QtSql>

class DB
{
private:
    QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName(QDir::currentPath()+"/chess.db");
    //QSqlQuery q;
public:
    DB()
    {
        //db= QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("C:/Users/Niktesla/Desktop/Projects/gui-1h2017-13.git/Chess/chess.db");
    }
    ~DB(){

    }

    bool openDB()
    {
        QSqlQuery q;
        bool ok = db.open();
        //qDebug() <<db.tables();
        //qDebug() <<q.lastError().text();
        return ok;
    }
    void closeDB(){
        db.close();
    }
    QString intToChar(int i)
    {
        QString s;
        switch (i) {
        case 1:
            s='a';
            break;
        case 2:
            s='b';
            break;
        case 3:
            s='c';
            break;
        case 4:
            s='d';
            break;
        case 5:
            s='e';
            break;
        case 6:
            s='f';
            break;
        case 7:
            s='g';
            break;
        case 8:
            s='h';
            break;
        default:
            s='no';
            break;
        }
        return s;
    }

    QSqlError createTable(const QString &name)
    {
         QSqlQuery q;
        if (!q.exec("create table "+name+"(id integer primary key, from1 integer(1), from2 integer(1), to1 integer(1),to2 integer(1))"))
           return q.lastError();
        return QSqlError();
    }
    QStringList tableList()
    {
        //qDebug() << db.tables();
        return db.tables();
    }
    bool containsTable(const QString &name)
    {
        //qDebug() << db.tables();
        return db.tables().contains(name);
    }

    int recordCount(const QString &name)
    {
         QSqlQuery q;
         q.exec("SELECT count(*) FROM "+name);
         q.next();
         return q.value(0).toString().toInt();
    }
    QSqlError deleteTable(const QString &name)
    {
         QSqlQuery q;
        if (!q.exec("drop table "+name))
           return q.lastError();
        return QSqlError();
    }
    QSqlError writeMove(const QString &table,QPoint *from, QPoint* to)
    {
        QSqlQuery q;
        if (!q.prepare("insert into  "+table+"(from1,from2, to1, to2) values(?, ?, ?, ?)"))
            return q.lastError();
        q.addBindValue(from->x());
        q.addBindValue(from->y());
        q.addBindValue(to->x());
        q.addBindValue(to->y());
        q.exec();
        return QSqlError();
    }
    QSqlError writeMove(const QString &table,QPoint from, QPoint to)
    {
        QSqlQuery q;
        if (!q.prepare("insert into  "+table+"(from1,from2, to1, to2) values(?, ?, ?, ?)"))
            return q.lastError();
        q.addBindValue(from.x());
        q.addBindValue(from.y());
        q.addBindValue(to.x());
        q.addBindValue(to.y());
        q.exec();
        return QSqlError();
    }
    QPoint* readMove(const QString &table, int i)
    {
        QSqlQuery q;
        //q.exec("SELECT count(*) FROM "+table);
        //q.next();
        //int n= q.value(0).toString().toInt();
        QPoint* moves = new QPoint[2];

        q.exec("SELECT id,from1,from2, to1, to2 FROM "+table);
        int k=0;
        while (q.next())
        {
            //qDebug() << q.value(0).toString() << q.value(1).toString() << q.value(2).toString() << q.value(3).toString()<< q.value(4).toString();
            if(i==k)
            {
                moves[0]=QPoint(q.value(1).toString().toInt(),q.value(2).toString().toInt());
                moves[1]=QPoint(q.value(3).toString().toInt(),q.value(4).toString().toInt());
            }
            k++;
        }
        return moves;
    }
    QStringList readMovesS(const QString &name)
    {
        QPoint* moves = new QPoint[2];
        QString s="";  
        QStringList sl;
        for(int i=0; i<recordCount(name); i++)
        {
            moves=readMove(name,i);
            sl<<QString::number(moves[0].x())<<QString::number(moves[0].y())<<QString::number(moves[1].x())<<QString::number(moves[1].y());
            //QTextStream(&s)<<intToChar(moves[0].x())<<'-'<<moves[0].y()<<" -> "<<intToChar(moves[1].x())<<'-'<<moves[1].y()<<'\n';
        }
        return sl;
    }
    QString searchDebute(QPoint deb[])
    {

        QSqlQuery q;
        QPoint* moves = new QPoint[2];
        QStringList list=db.tables();
        int k=0,i;
        for(i =0;i<list.count();i++ )
        {
            QString table = list[i];
            q.exec("SELECT id,from1,from2, to1, to2 FROM "+table);
            k=0;
            while (q.next())
            {
                //qDebug() << q.value(0).toString() << q.value(1).toString() << q.value(2).toString() << q.value(3).toString()<< q.value(4).toString();
                if(k<12)
                {
                    moves[0]=QPoint(q.value(1).toString().toInt(),q.value(2).toString().toInt());
                    moves[1]=QPoint(q.value(3).toString().toInt(),q.value(4).toString().toInt());
                }
                else break;
                if(deb[k]!=moves[0] || deb[k+1]!=moves[1])
                    break;
                k=k+2;

            }
            if(k==12) break;
        }
      if(k==12)  return list[i];
      return "false";
    }

    QString searchDebute(QVector<QPoint> &deb)
    {
        if(deb.count()<6) return "false";
        QSqlQuery q;
        QVector<QPoint> p;
        //q.exec("SELECT count(*) FROM "+table);
        //q.next();
        //int n= q.value(0).toString().toInt();
        QStringList list=db.tables();
        int k=0,i;
        for(i =0;i<list.count();i++ )
        {
            QString table = list[i];
            q.exec("SELECT id,from1,from2, to1, to2 FROM "+table);
            k=0;
            while (q.next())
            {
                //qDebug() << q.value(0).toString() << q.value(1).toString() << q.value(2).toString() << q.value(3).toString()<< q.value(4).toString();
                if(k<12)
                {
                    p<<(QPoint(q.value(1).toString().toInt(),q.value(2).toString().toInt()));
                    p<<(QPoint(q.value(3).toString().toInt(),q.value(4).toString().toInt()));
                }
                else break;
                k=k+2;

            }
            qSort(p.begin(),p.end(),lessThan);
            qSort(deb.begin(),deb.end(),lessThan);
            //qDebug() << p << deb;
            if(p==deb) break;
            p.clear();
        }
      if(p==deb)  return list[i];
      return "false";
    }

    static bool lessThan( const QPoint & e1, const QPoint & e2 )
    {
        int d1=e1.x()*e1.x()+e1.y()*e1.y();
        int d2=e2.x()*e2.x()+e2.y()*e2.y();
        if(d1==d2) return e1.x()<e2.x();
        return d1<d2;
    }

    void al23_barbo(){
        if(openDB()){
            deleteTable("Al_barbo");
            createTable("Al_barbo");
            writeMove("Al_barbo",new QPoint(5,2),new QPoint(5,4));
            writeMove("Al_barbo",new QPoint(5,7),new QPoint(5,5));
            writeMove("Al_barbo",new QPoint(7,1),new QPoint(6,3));
            writeMove("Al_barbo",new QPoint(2,8),new QPoint(3,6));
            writeMove("Al_barbo",new QPoint(6,1),new QPoint(3,4));
            writeMove("Al_barbo",new QPoint(6,8),new QPoint(3,5));
            writeMove("Al_barbo",new QPoint(5,1),new QPoint(7,1));//rok
            writeMove("Al_barbo",new QPoint(8,1),new QPoint(6,1));
            writeMove("Al_barbo",new QPoint(4,7),new QPoint(4,6));
            writeMove("Al_barbo",new QPoint(3,2),new QPoint(3,3));
            writeMove("Al_barbo",new QPoint(4,8),new QPoint(6,6));
            writeMove("Al_barbo",new QPoint(4,2),new QPoint(4,3));
            writeMove("Al_barbo",new QPoint(8,7),new QPoint(8,6));
            writeMove("Al_barbo",new QPoint(3,1),new QPoint(5,3));
            writeMove("Al_barbo",new QPoint(3,5),new QPoint(2,6));
            writeMove("Al_barbo",new QPoint(5,3),new QPoint(2,6));
            writeMove("Al_barbo",new QPoint(1,7),new QPoint(2,6));
            writeMove("Al_barbo",new QPoint(8,2),new QPoint(8,3));
            writeMove("Al_barbo",new QPoint(7,8),new QPoint(5,7));
            writeMove("Al_barbo",new QPoint(6,3),new QPoint(8,2));
            writeMove("Al_barbo",new QPoint(5,7),new QPoint(7,6));
            writeMove("Al_barbo",new QPoint(2,1),new QPoint(4,2));
            writeMove("Al_barbo",new QPoint(7,6),new QPoint(6,4));
            writeMove("Al_barbo",new QPoint(4,2),new QPoint(6,3));
            writeMove("Al_barbo",new QPoint(6,6),new QPoint(7,6));
            writeMove("Al_barbo",new QPoint(7,2),new QPoint(7,3));
            writeMove("Al_barbo",new QPoint(6,4),new QPoint(8,3));
            writeMove("Al_barbo",new QPoint(7,1),new QPoint(7,2));
            writeMove("Al_barbo",new QPoint(8,3),new QPoint(6,4));
            writeMove("Al_barbo",new QPoint(7,2),new QPoint(8,1));
            writeMove("Al_barbo",new QPoint(3,8),new QPoint(8,3));
            writeMove("Al_barbo",new QPoint(6,1),new QPoint(7,1));
            writeMove("Al_barbo",new QPoint(7,6),new QPoint(8,5));
            writeMove("Al_barbo",new QPoint(7,3),new QPoint(6,4));
            writeMove("Al_barbo",new QPoint(5,5),new QPoint(6,4));
            writeMove("Al_barbo",new QPoint(8,2),new QPoint(7,4));
            writeMove("Al_barbo",new QPoint(8,3),new QPoint(7,4));
            writeMove("Al_barbo",new QPoint(8,1),new QPoint(7,2));
            writeMove("Al_barbo",new QPoint(8,5),new QPoint(8,3));
            //QVector <QPoint> v;
            //v<<QPoint(5,2)<<QPoint(5,4)<<QPoint(5,7)<<QPoint(5,5)<<QPoint(7,1)<<QPoint(6,3)<<
                   // QPoint(2,8)<< QPoint(3,6)<<QPoint(6,1)<<QPoint(3,4)<<QPoint(6,8)<<QPoint(3,5);
            //qDebug()<<searchDebute(v);
        }
        closeDB();
    }

    void Murphy(){
        //DB *db = new DB();
        if(openDB()){
            deleteTable("ChessMorphy");
            createTable("ChessMorphy");
            writeMove("ChessMorphy",new QPoint(5,2),new QPoint(5,4));
            writeMove("ChessMorphy",new QPoint(5,7),new QPoint(5,5));
            writeMove("ChessMorphy",new QPoint(7,1),new QPoint(6,3));
            writeMove("ChessMorphy",new QPoint(4,7),new QPoint(4,6));
            writeMove("ChessMorphy",new QPoint(4,2),new QPoint(4,4));
            writeMove("ChessMorphy",new QPoint(3,8),new QPoint(7,4));
            writeMove("ChessMorphy",new QPoint(4,4),new QPoint(5,5));
            writeMove("ChessMorphy",new QPoint(7,4),new QPoint(6,3));
            writeMove("ChessMorphy",new QPoint(4,1),new QPoint(6,3));
            writeMove("ChessMorphy",new QPoint(4,6),new QPoint(5,5));
            writeMove("ChessMorphy",new QPoint(6,1),new QPoint(3,4));
            writeMove("ChessMorphy",new QPoint(7,8),new QPoint(6,6));
            writeMove("ChessMorphy",new QPoint(6,3),new QPoint(2,3));
            writeMove("ChessMorphy",new QPoint(4,8),new QPoint(5,7));
            writeMove("ChessMorphy",new QPoint(2,1),new QPoint(3,3));
            writeMove("ChessMorphy",new QPoint(3,7),new QPoint(3,6));
            writeMove("ChessMorphy",new QPoint(3,1),new QPoint(7,5));
            writeMove("ChessMorphy",new QPoint(2,7),new QPoint(2,5));
            writeMove("ChessMorphy",new QPoint(3,3),new QPoint(2,5));
            writeMove("ChessMorphy",new QPoint(3,6),new QPoint(2,5));
            writeMove("ChessMorphy",new QPoint(3,4),new QPoint(2,5));
            writeMove("ChessMorphy",new QPoint(2,8),new QPoint(4,7));
            writeMove("ChessMorphy",new QPoint(5,1),new QPoint(3,1)); //рокировка
            writeMove("ChessMorphy",new QPoint(1,1),new QPoint(4,1));
            writeMove("ChessMorphy",new QPoint(1,8),new QPoint(4,8));
            writeMove("ChessMorphy",new QPoint(4,1),new QPoint(4,7));
            writeMove("ChessMorphy",new QPoint(4,8),new QPoint(4,7));
            writeMove("ChessMorphy",new QPoint(8,1),new QPoint(4,1));
            writeMove("ChessMorphy",new QPoint(5,7),new QPoint(5,6));
            writeMove("ChessMorphy",new QPoint(2,5),new QPoint(4,7));
            writeMove("ChessMorphy",new QPoint(6,6),new QPoint(4,7));
            writeMove("ChessMorphy",new QPoint(4,4),new QPoint(5,5));
            writeMove("ChessMorphy",new QPoint(2,3),new QPoint(2,8));
            writeMove("ChessMorphy",new QPoint(4,7),new QPoint(2,8));
            writeMove("ChessMorphy",new QPoint(4,1),new QPoint(4,8));
           // QPoint m[12]={QPoint(5,2),QPoint(5,4),QPoint(5,7),QPoint(5,5),QPoint(7,1),QPoint(6,3),
                  //  QPoint(4,7), QPoint(4,6),QPoint(4,2),QPoint(4,4),QPoint(3,8),QPoint(7,4)};
        }
        closeDB();
    }
};


#endif // DB_H
