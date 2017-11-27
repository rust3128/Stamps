#ifndef VERSIONPODIALOG_H
#define VERSIONPODIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class VersionPODialog;
}

class VersionPODialog : public QDialog
{
    Q_OBJECT

public:
    explicit VersionPODialog(QWidget *parent = 0);
    ~VersionPODialog();

private slots:
    void on_pbAdd_clicked();

    void on_pbExit_clicked();

    void on_pbEdit_clicked();

    void on_pbDel_clicked();

private:
    Ui::VersionPODialog *ui;
    QSqlTableModel *model;
    void createUI();
};

#endif // VERSIONPODIALOG_H
