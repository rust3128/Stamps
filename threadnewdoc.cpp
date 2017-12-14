#include "threadnewdoc.h"
#include <QDebug>
#include <QSqlQuery>


ThreadNewDoc::ThreadNewDoc(QString str) : strSQL(str)
{

}

void ThreadNewDoc::run()
{
    qDebug() << "Запрос из потока" << strSQL;
    QSqlQuery q;
        if(q.exec(strSQL)) qDebug() << "Не удалось выполнить запрос";
}
