#ifndef THREADNEWDOC_H
#define THREADNEWDOC_H
#include <QThread>

class ThreadNewDoc : public QThread
{
    Q_OBJECT
public:
    explicit ThreadNewDoc(QString str);
    void run();
private:
    QString strSQL;
};

#endif // THREADNEWDOC_H
