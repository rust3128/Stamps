#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionRegions_triggered();
    void on_actionUsers_triggered();
    void on_actionStorage_triggered();

    void on_actionDocs_triggered();

    void on_actionVlasn_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
