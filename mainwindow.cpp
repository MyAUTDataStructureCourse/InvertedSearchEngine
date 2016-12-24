#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <crawler.h>
#include <QMessageBox>
#include "terminal.h"
#include <QDebug>
#include "stoptree.h"
#include "tree.h"
#include <QDirIterator>
#include "cmdline.h"
#include "progressbar.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel;
    ui->fileList->setModel(model);
    Terminal::getInstance().setObject(ui->cmdOutput);
    ui->cmdInput->installEventFilter(this);

    ui->cbTreeType->addItem("Binary Search Tree");
    ui->cbTreeType->addItem("TST");
    ui->cbTreeType->addItem("Trie");

    ui->cmdInput->setVisible(false);
    ProgressBar::getInstance().setCommandLineWidget(ui->cmdInput);
    ProgressBar::getInstance().setProgressBarWidget(ui->prbPrgress);

    ProgressBar::getInstance().toggleToCMDLine();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbAddFile_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text Files (*.txt)"));
    if(!fileName.isEmpty())
    {
        if(Crawler::getInstance().add_file_to_list(fileName))
            addToList(fileName);
    }
}

void MainWindow::addToList(QString value)
{
    QStandardItem *item;
    item = new QStandardItem();
    item->setData( value, Qt::DisplayRole );
    item->setEditable( false );
    model->appendRow( item );
}

void MainWindow::on_pbAddDir_clicked()
{

    QString dirName;
    dirName = QFileDialog::getExistingDirectory(this,"Open Direcotyr");

    if(!dirName.isEmpty())
    {
        Crawler::getInstance().add_directory(dirName);

        Crawler::getInstance().addFilesOfDirectoriesToFilelist();
        QStringList allFiles = Crawler::getInstance().listFiles();

        qDebug() << allFiles.size();
        for(int i = 0; i < allFiles.size(); i++)
        {
            addToList(allFiles[i]);
        }
    }
}

void MainWindow::on_cmdInput_returnPressed()
{
    QString cmd = ui->cmdInput->text();
    Terminal::getInstance().writeLine(">>> " + cmd);
    ui->cmdInput->setText("");
    before.push(cmd);

    CommandLineInterPreter::getInstance().interpreteCommand(cmd);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{   
    if (obj == ui->cmdInput && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        if(key->key() == Qt::Key_Up)
        {
            if(!before.isEmpty())
            {
                after.push(ui->cmdInput->text());
                QString cmd;
                before.pop(cmd);
                ui->cmdInput->setText(cmd);
            }

        }
        else if(key->key() == Qt::Key_Down)
        {
            if(!after.isEmpty())
            {
                before.push(ui->cmdInput->text());
                QString cmd;
                after.pop(cmd);
                ui->cmdInput->setText(cmd);
            }
        }
    }

    return QObject::eventFilter(obj, event);
}

void MainWindow::on_pbBuild_clicked()
{
    Terminal::getInstance().writeLine("Start building ...");
    Crawler::getInstance().crawlAll();

    switch (ui->cbTreeType->currentIndex()) {
    case 0:
        TreeObject::getInstance().initTree(Tree::BST_TREE);
        break;
    case 1:
        TreeObject::getInstance().initTree(Tree::TST_TREE);
        break;
    case 2:
        TreeObject::getInstance().initTree(Tree::TRIE_TREE);
        break;
    default:

        Terminal::getInstance().writeError("err : No tree type is selected.");
        return;
        break;
    }

    Crawler::getInstance().buildTree();
}

void MainWindow::on_pbSWBrowse_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Stop Word File"), QDir::homePath(), tr("Text Files (*.txt)"));
    if(!fileName.isEmpty())
    {
        ui->leSWPath->setText(fileName);
        StopTreeObject::getInstace().setStopWordFilePath(fileName);
    }
}

void MainWindow::on_pbSWBuild_clicked()
{
    switch (ui->cbTreeType->currentIndex()) {
    case 0:
        StopTreeObject::getInstace().buildBST();
        break;
    case 1:
        StopTreeObject::getInstace().buildTST();
        break;
    case 2:
        StopTreeObject::getInstace().buildTrie();
        break;
    default:

        Terminal::getInstance().writeLine("err : No tree type is selected.");
        return;
        break;
    }


    StopTreeObject::getInstace().buildTree();

    if(StopTreeObject::getInstace().isExisted(QString("this")))
        Terminal::getInstance().writeLine("'This' is existed in the stop words lists");

    if(StopTreeObject::getInstace().isExisted(QString("welcome")))
        Terminal::getInstance().writeLine("'Welcome' is existed in the stop words lists");

    if(StopTreeObject::getInstace().isExisted(QString("I")))
        Terminal::getInstance().writeLine("'I' is existed in the stop words lists");
}
