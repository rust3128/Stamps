#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regionsdialog.h"
#include "usersdialog.h"
#include "storagedialog.h"
#include "documentsdialog.h"
#include "vlasnikdialog.h"
#include "rrolistdialog.h"
#include "modelrrodialog.h"
#include "versionpodialog.h"
#include "usedreportdialog.h"


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

void MainWindow::on_actionDocs_triggered()
{
    DocumentsDialog *docDlg = new DocumentsDialog();
    this->setCentralWidget(docDlg);
    docDlg->exec();
}

void MainWindow::on_actionVlasn_triggered()
{
    VlasnikDialog *vlasDlg = new VlasnikDialog();
    vlasDlg->exec();
}

void MainWindow::on_actionRroList_triggered()
{
    RroListDialog *rroDlg = new RroListDialog(false);
    this->setCentralWidget(rroDlg);
    rroDlg->exec();
}

void MainWindow::on_actionModelRRo_triggered()
{
    ModelRroDialog *modRro  = new ModelRroDialog();
    modRro->exec();
}

void MainWindow::on_actionVersion_triggered()
{
    VersionPODialog *verDlg = new VersionPODialog();
    verDlg->exec();
}

void MainWindow::on_actionUsedStamps_triggered()
{
    UsedReportDialog *useDlg = new UsedReportDialog();
    this->setCentralWidget(useDlg);
    useDlg->exec();
}
