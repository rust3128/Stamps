#ifndef RRODIALOG_H
#define RRODIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QAbstractButton>

namespace Ui {
class RroDialog;
}

class RroDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RroDialog(int id, QWidget *parent = 0);
    ~RroDialog();

private slots:
    void on_toolButtonVlasnik_clicked();

    void on_toolButtonModel_clicked();

    void on_toolButtonVersion_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::RroDialog *ui;
    int rroID;
    QSqlTableModel *modelVlasnik;
    QSqlTableModel *modelRro;
    QSqlTableModel *modelPo;

private:
    void createUI();
    bool validateData();
    void databaseChange();
};

#endif // RRODIALOG_H
