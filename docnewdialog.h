#ifndef DOCNEWDIALOG_H
#define DOCNEWDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QAbstractButton>
#include <QSqlTableModel>

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
    void on_comboBox2Region_activated(int idx);

    void on_comLinkButRro_clicked();

private:
    Ui::DocNewDialog *ui;
    int docID;
    QString docType;
    QPixmap *pixOk;
    QPixmap *pixError;
    bool serOK, begOK, endOK, diapOK, reg2OK, rroOK;
    QString serial;
    int numberBegin, numberEnd,colStamps;
    QString docNumber;
    QSqlTableModel *modelRegion;
    int idStorage;
    int idStatus;

    void createUI();
    void resetData();
    void documentCreate();
    QString genDocNumber(int id);
    void createComboRegion();
    bool validStamps();


};

#endif // DOCNEWDIALOG_H
