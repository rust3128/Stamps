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

private slots:
    void on_lineEditFind_textChanged(const QString &arg1);

    void on_checkBox_clicked();

private:
    Ui::RroListDialog *ui;
    QSqlRelationalTableModel *modelRro;
    QString filter;

private:
    void createUI();
};

#endif // RROLISTDIALOG_H
