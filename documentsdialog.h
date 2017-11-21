#ifndef DOCUMENTSDIALOG_H
#define DOCUMENTSDIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>

namespace Ui {
class DocumentsDialog;
}

class DocumentsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DocumentsDialog(QWidget *parent = 0);
    ~DocumentsDialog();

private slots:
    void on_toolButtonNewDoc_clicked();

private:
    Ui::DocumentsDialog *ui;
    QSqlRelationalTableModel *modelDocs;

private:
    void setupModelDocs(const QStringList &headers);
    void createUI();

};

#endif // DOCUMENTSDIALOG_H
