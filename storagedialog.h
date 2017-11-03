#ifndef STORAGEDIALOG_H
#define STORAGEDIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>
#include <QItemSelection>
#include <QAbstractButton>

namespace Ui {
class StorageDialog;
}

class StorageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StorageDialog(QWidget *parent = 0);
    ~StorageDialog();

private slots:
    void userSelectionChanged(QItemSelection selection);

    void on_pbNew_clicked();

    void on_pbEdit_clicked();

    void on_pbDelete_clicked();

    void on_pbClose_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::StorageDialog *ui;
    QSqlRelationalTableModel *modelStorage;
    QDataWidgetMapper *mapper;

    void createUI();
};

#endif // STORAGEDIALOG_H
