#ifndef CHANGEDOCTYPEDIALOG_H
#define CHANGEDOCTYPEDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QPushButton>
#include <QItemSelection>

namespace Ui {
class ChangeDocTypeDialog;
}

class ChangeDocTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeDocTypeDialog(QWidget *parent = 0);
    ~ChangeDocTypeDialog();
    int docTypeIDReturn();
    QString docTypeNameReturn();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void userSelectionChanged(QItemSelection selection);
private:
    Ui::ChangeDocTypeDialog *ui;
    QSqlQueryModel *modelDocs;
    int docTypeID;
    QString docTypeName;

    void createUI();
};

#endif // CHANGEDOCTYPEDIALOG_H
