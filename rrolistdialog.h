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
    explicit RroListDialog(bool type, QWidget *parent = 0);
    ~RroListDialog();

private slots:
    void on_lineEditFind_textChanged(const QString &arg1);

    void on_checkBox_clicked();

    void on_toolButtonNew_clicked();

    void on_toolButtonEdit_clicked();

    void on_toolButtonDelete_clicked();

    void on_tableView_doubleClicked(const QModelIndex &idx);

    void on_pushButton_clicked();

    void on_pushButtonSelect_clicked();

private:
    Ui::RroListDialog *ui;
    QSqlRelationalTableModel *modelRro;
    QString filter;
    bool vozvrat;
    int rroSelected;

private:
    void createUI();
public:
    int getRro();
};

#endif // RROLISTDIALOG_H
