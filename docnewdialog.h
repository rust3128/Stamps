#ifndef DOCNEWDIALOG_H
#define DOCNEWDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QAbstractButton>

namespace Ui {
class DocNewDialog;
}

class DocNewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DocNewDialog(int ID, QString Type, QWidget *parent = 0);
    ~DocNewDialog();

private slots:
    void on_lineEditSerial_textChanged(const QString &arg1);
    void on_lineEditBeginNum_textChanged(const QString &arg1);
    void on_lineEditEndNum_textChanged(const QString &arg1);
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::DocNewDialog *ui;
    int docID;
    QString docType;
    QPixmap *pixOk;
    QPixmap *pixError;
    bool serOK, begOK, endOK, diapOK;
    QString serial;
    int numberBegin, numberEnd;

    void createUI();
    void resetData();
    void documentCreate();
    QString genDocNumber(int id);

};

#endif // DOCNEWDIALOG_H
