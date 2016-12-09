#include "stoptree.h"
#include "terminal.h"

StopTree::StopTree()
{

}

StopTreeObject &StopTreeObject::getInstace()
{
    static StopTreeObject instance();

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

void StopTreeObject::buildTree()
{

}

StopTreeObject::~StopTreeObject()
{
    delete tree;
}

void BSTStop::add(QString word)
{

}

bool BSTStop::isExisted(QString word)
{

}
