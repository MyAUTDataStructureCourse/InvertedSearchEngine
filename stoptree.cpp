#include "stoptree.h"
#include "terminal.h"
#include <QTextStream>
#include <QTime>
#include <QDebug>

StopTree::StopTree()
{

}

StopTreeObject::StopTreeObject()
{
    stopTree = NULL;
}

StopTreeObject &StopTreeObject::getInstace()
{
    static StopTreeObject instance;

    return instance;
}

void StopTreeObject::setStopWordFilePath(QString filePath)
{
    QFile file(filePath);
    if(file.exists())
    {
        Terminal::getInstance().writeLine("File \"" + filePath + "\" is set for stop words file successfully.");
        this->filePath = filePath;
    }
    else
    {
        Terminal::getInstance().writeLine("err : File \"" + filePath + "\" is not exists.");
    }
}

void StopTreeObject::buildBST()
{
    stopTree = new BSTStop;
}

void StopTreeObject::buildTrie()
{
    stopTree = new TrieStop;
}

void StopTreeObject::buildTST()
{
    stopTree = new TSTStop;
}

void StopTreeObject::buildTree()
{
    qDebug() << QString("this line executed here ");

    QTime timer;        // Timer for measuring the time elapsed for adding stop words to their tree

    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        Terminal::getInstance().writeLine("Reading from file : \"" + filePath + "\" ...");

        QTextStream in(&file);

        timer.start();  // Start the timer

        int wordCound = 0;
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList list = line.split(QRegExp("\\W+"), QString::SkipEmptyParts);


            for(int i = 0; i < list.size(); i++)
            {
                stopTree->add(QString(list[i]).toLower());
                wordCound ++;
            }
        }


        int time = timer.elapsed();
        Terminal::getInstance().writeLine(QString("%1 word(s) added to tree in %2 ms.").arg(wordCound).arg(time));
        file.close();

        Terminal::getInstance().writeLine("File : \"" + filePath + "\" closed.");
    }
    else
    {
        Terminal::getInstance().writeLine("Unable to open the file : \"" + filePath + "\".");
    }
}

bool StopTreeObject::isExisted(QString word)
{
    return this->stopTree->isExisted(word);
}

StopTreeObject::~StopTreeObject()
{
    delete stopTree;
}

BSTStopNode::BSTStopNode(QString &word)
{
    this->value = word;
    leftChild = NULL;
    rightChild = NULL;
}

BSTStop::BSTStop()
{
    this->root = NULL;
}

void BSTStop::add(QString word)
{

    BSTStopNode *newNode = new BSTStopNode(word);

    if(this->root != NULL)
    {

        BSTStopNode *pointer = this->root;
        BSTStopNode *parent = NULL;

        while(pointer)
        {
            parent = pointer;
            if(QString::compare(pointer->value, word, Qt::CaseInsensitive) == 0)
            {
                return;
            }
            else if(QString::compare(pointer->value, word, Qt::CaseInsensitive) > 0)
            {
                pointer = pointer->leftChild;
            }
            else if(QString::compare(pointer->value, word, Qt::CaseInsensitive) < 0)
            {
                pointer = pointer->rightChild;
            }
        }

        if(QString::compare(parent->value, word, Qt::CaseInsensitive) > 0)
            parent->leftChild = newNode;
        else if(QString::compare(parent->value, word, Qt::CaseInsensitive) < 0)
            parent->rightChild = newNode;

    }
    else
    {
        root = newNode;
    }
}

bool BSTStop::isExisted(QString word)
{
    BSTStopNode *pointer = this->root;

    while(pointer)
    {

        if(QString::compare(pointer->value, word, Qt::CaseInsensitive) == 0)
        {
            return true;
        }
        else if(QString::compare(pointer->value, word, Qt::CaseInsensitive) > 0)
        {
            pointer = pointer->leftChild;
        }
        else if(QString::compare(pointer->value, word, Qt::CaseInsensitive) < 0)
        {
            pointer = pointer->rightChild;
        }
    }

    return false;
}

void TSTStop::add(QString word)
{

}

bool TSTStop::isExisted(QString word)
{

}

void TrieStop::add(QString word)
{

}

bool TrieStop::isExisted(QString word)
{

}
