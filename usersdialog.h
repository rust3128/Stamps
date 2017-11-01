#ifndef USERSDIALOG_H
#define USERSDIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>
#include <QItemSelection>


namespace Ui {
class UsersDialog;
}

class UsersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UsersDialog(QWidget *parent = 0);
    ~UsersDialog();

private slots:
    void on_pbNew_clicked();
    void on_pbEdit_clicked();
    void userSelectionChanged(QItemSelection selection);

private:
    Ui::UsersDialog *ui;
    QSqlRelationalTableModel *modelUsers;
    QDataWidgetMapper *mapper;

    void createUI();
};

#endif // USERSDIALOG_H
