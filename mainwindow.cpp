#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regionsdialog.h"
#include "usersdialog.h"
#include "storagedialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRegions_triggered()
{
    RegionsDialog *regionsDlg = new RegionsDialog();
    regionsDlg->exec();
}

void MainWindow::on_actionUsers_triggered()
{
    UsersDialog *userDlg = new UsersDialog();
    userDlg->exec();
}

void MainWindow::on_actionStorage_triggered()
{
    StorageDialog *storageDlg = new StorageDialog(this);
    storageDlg->exec();
}
