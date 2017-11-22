#ifndef VLASNIKDIALOG_H
#define VLASNIKDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QItemSelection>
#include <QAbstractButton>

namespace Ui {
class VlasnikDialog;
}

class VlasnikDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VlasnikDialog(QWidget *parent = 0);
    ~VlasnikDialog();
private slots:
    void userSelectionChanged(QItemSelection selection);

    void on_pbNew_clicked();

    void on_pbEdit_clicked();

    void on_pbDelete_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_pbClose_clicked();

private:
    Ui::VlasnikDialog *ui;
    QSqlTableModel *modelVlasnik;
    QDataWidgetMapper *mapper;

private:
    void createUI();
};

#endif // VLASNIKDIALOG_H
