#ifndef DOCUMENTSDIALOG_H
#define DOCUMENTSDIALOG_H

#include <QDialog>

namespace Ui {
class DocumentsDialog;
}

class DocumentsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DocumentsDialog(QWidget *parent = 0);
    ~DocumentsDialog();

private:
    Ui::DocumentsDialog *ui;
};

#endif // DOCUMENTSDIALOG_H
