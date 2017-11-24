#ifndef RROLISTDIALOG_H
#define RROLISTDIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>


namespace Ui {
class RroListDialog;
}

class RroListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RroListDialog(QWidget *parent = 0);
    ~RroListDialog();

private:
    Ui::RroListDialog *ui;
    QSqlRelationalTableModel *modelRro;

private:
    void createUI();
};

#endif // RROLISTDIALOG_H
