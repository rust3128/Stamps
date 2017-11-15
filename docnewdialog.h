#ifndef DOCNEWDIALOG_H
#define DOCNEWDIALOG_H

#include <QDialog>

namespace Ui {
class DocNewDialog;
}

class DocNewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DocNewDialog(int ID, QString Type, QWidget *parent = 0);
    ~DocNewDialog();

private:
    Ui::DocNewDialog *ui;
    int docID;
    QString docType;

    void createUI();

};

#endif // DOCNEWDIALOG_H
