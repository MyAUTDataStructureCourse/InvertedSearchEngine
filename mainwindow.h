#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "stack.h"

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

    void on_pbAddFile_clicked();

    void on_pbAddDir_clicked();

    void on_cmdInput_returnPressed();

    void on_pbBuild_clicked();

    void on_pbSWBrowse_clicked();

    void on_pbSWBuild_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;

    Stack<QString> before;
    Stack<QString> after;
    bool eventFilter(QObject *obj, QEvent *event);

    void addToList(QString value);
};

#endif // MAINWINDOW_H
