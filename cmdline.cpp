#include "cmdline.h"
#include <string.h>
#include "crawler.h"
#include "terminal.h"
#include <QDebug>

CommandLineInterPreter::CommandLineInterPreter()
{

}

CommandLineInterPreter &CommandLineInterPreter::getInstance()
{
    static CommandLineInterPreter instance;

    return instance;
}


void CommandLineInterPreter::list(QStringList params)
{

    if(QString::compare(params[1], "-f", Qt::CaseInsensitive) == 0)
    {
        QStringList fileList = Crawler::getInstance().listFiles();
        Terminal::getInstance().writeLine("List of files in the directory :");
        for (int i = 0; i < fileList.size(); ++i) {
            Terminal::getInstance().writeLine(fileList[i]);
        }
    }
    else if(QString::compare(params[1], "-l", Qt::CaseInsensitive) == 0)
    {
        QStringList fileList = Crawler::getInstance().listOfCrawledFiles();
        Terminal::getInstance().writeLine("List of files crawled into the dictionary :");
        for (int i = 0; i < fileList.size(); ++i) {
            Terminal::getInstance().writeLine(fileList[i]);
        }
    }
    else if(QString::compare(params[1], "-w", Qt::CaseInsensitive) == 0)
    {

    }
}

void CommandLineInterPreter::del(QStringList params)
{

}

void CommandLineInterPreter::add(QStringList params)
{
    QString filePath = QString("%1/%2").arg(Crawler::getInstance().getDir()).arg(params[1]);

    if(Crawler::getInstance().isFileExistedInList(filePath))
    {
        Terminal::getInstance().writeError(QString("err : File :\"%1\" already exists. You may want to update.").arg(filePath));
    }
    else
    {
        qDebug() << filePath;
        Crawler::getInstance().add_file_to_list(filePath);
    }
}

void CommandLineInterPreter::interpreteCommand(QString cmd)
{
    QStringList tokens = cmd.split(' ');
    if(QString::compare(tokens[0], QString("list"), Qt::CaseInsensitive) == 0)
    {
        list(tokens);
    }
    else if(QString::compare(tokens[0], QString("add"), Qt::CaseInsensitive) == 0)
    {
        add(tokens);
    }
    else if(QString::compare(tokens[0], QString("list"), Qt::CaseInsensitive) == 0)
    {

    }

}
