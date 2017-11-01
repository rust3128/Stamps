#ifndef REGIONSDIALOG_H
#define REGIONSDIALOG_H

#include <QDialog>
#include <QSqlTableModel>


namespace Ui {
class RegionsDialog;
}

class RegionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegionsDialog(QWidget *parent = 0);
    ~RegionsDialog();

private slots:
    void on_pbAdd_clicked();
    void on_pbExit_clicked();
    void on_pbEdit_clicked();

    void on_pbDel_clicked();

private:
    Ui::RegionsDialog *ui;
    QSqlTableModel *model;
    void createUI();
};

#endif // REGIONSDIALOG_H
