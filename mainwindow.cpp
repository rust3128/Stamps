#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regionsdialog.h"

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
