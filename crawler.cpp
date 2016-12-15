#include "crawler.h"
#include <QFile>
#include <QTextStream>
#include "terminal.h"
#include <QDebug>
#include "tree.h"
#include "stoptree.h"
#include <QTime>
#include <QDir>

WordPosition::WordPosition()
{

}

WordPosition::WordPosition(int file_id, int line_num, int sentence_num, std::__cxx11::string last_word, std::__cxx11::string next_word)
{
    this->file_id = file_id;
    this->line_num = line_num;
    this->sentence_num = sentence_num;
    this->last_word = last_word;
    this->next_word = next_word;
}

Crawler::Crawler()
{

}

FileWordNode::FileWordNode()
{
    this->next = NULL;
    this->last = NULL;
}

FileWordNode::FileWordNode(QString word,int line_num)
{
    FileWordNode();
    this->word = word;
    this->line_num = line_num;
}

void Word::add_position(WordPosition position)
{
    this->positions.push_back(position);
}

Crawler& Crawler::getInstance()
{
    static Crawler instance;
    return instance;
}

void Crawler::buildTree()
{
    int sumWordsCount = 0;
    int sumTime = 0;

    int fileNum = file_words_starts.size();

    int wordCount = 0;
    int timeElapsed;

    QTime timer;

    for (int i = 0; i < fileNum; ++i)
    {
        wordCount = 0;

        FileWordNode *pointer = file_words_starts[i]->next;

        timer.start();

        while(pointer)
        {

            if( ! StopTreeObject::getInstace().isExisted(pointer->word))
            {
                qDebug() << "this is my line that is running here";
                TreeObject::getInstance().getTree()->add(pointer->word,pointer);
                wordCount ++;
            }
            qDebug() << "this is my file";
            pointer = pointer->next;
        }

        timeElapsed = timer.elapsed();

        sumTime += timeElapsed;
        sumWordsCount += wordCount;

        Terminal::getInstance().writeLine(QString("File \"" + this->files_paths[i] + "\" added %1 words to the tree in %2 ms.").arg(wordCount).arg(timeElapsed));
    }

    Terminal::getInstance().writeLine(QString(""));
    Terminal::getInstance().writeLine(QString(""));

    Terminal::getInstance().writeLine(QString("Totally %1 file(s) added %2 words to the tree in %3 ms.").arg(fileNum).arg(sumWordsCount).arg(sumTime));
}

void Crawler::tokenizeString(QStringList &tokens,QString &line)
{
    tokens = line.split(QRegExp("\\W+"), QString::SkipEmptyParts);
}

bool Crawler::crawlFile(QString file_path)
{
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        Terminal::getInstance().writeError("error : Can't open \"" + file_path + "\"");
        return false;
    }

    this->file_words_starts.push_back(new FileWordNode());

    FileWordNode *last = this->file_words_starts[this->file_words_starts.size() - 1];

    QTextStream input(&file);
    QString line;
    QStringList wordsList;

    int line_num = 1;
    int wordCount = 1;

    while(!input.atEnd())
    {
        line = input.readLine();
        tokenizeString(wordsList, line);

        for(int i = 0; i < wordsList.size(); i++)
        {
            last->next = new FileWordNode(wordsList[i], line_num);
            last->next->last = last;
            last = last->next;
            last->next = NULL;
            wordCount ++;
        }

        line_num++;
    }

    Terminal::getInstance().writeLine(QString("File \"" + file_path + "\" crawled and %1 words detected.").arg(wordCount));

    return true;
}

void Crawler::add_directory(QString dir_path)
{

    dir_paths.push_back(dir_path);

}

QStringList Crawler::listFiles(int dir_id)
{


    QDir dir(dir_paths[dir_id]);

    dir.setNameFilters(QStringList("*.txt"));
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);



    QStringList fileList = dir.entryList();

    return fileList;

}

void Crawler::addFilesOfDirectoriesToFilelist()
{
    for (int i = 0; i < dir_paths.size(); ++i)
    {
        QDir dir(dir_paths[i]);

        dir.setNameFilters(QStringList("*.txt"));
        dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);


        QStringList fileList = dir.entryList();
        for (int j = 0; j < fileList.size(); ++j)
        {
            add_file_to_list(QString("%1/%2").arg(dir.absolutePath()).arg(fileList.at(j)));
        }
    }
}

void Crawler::crawlAll()
{
    Terminal::getInstance().writeLine("Start crawling on files ....");
    for(int i = 0; i < files_paths.size(); i++)
    {
        crawlFile(files_paths[i]);
    }
    Terminal::getInstance().writeLine(QString("%1 file(s) crawled.").arg(files_paths.size()));
}

bool Crawler::add_file_to_list(QString file_path)
{
    QFile file(file_path);
    if(file.exists())
    {
        files_paths.push_back(file_path);
        Terminal::getInstance().writeLine("File : \"" + file_path + "\" successfully added to the files' list.");
    }
    else {
        Terminal::getInstance().writeLine("File : \"" + file_path + "\" does not exist.");
    }
}

bool Crawler::isFileExistedInList(QString path)
{
    for (int i = 0; i < files_paths.size(); ++i) {
        if(QString::compare(path, files_paths[i], Qt::CaseSensitive) == 0)
            return true;
    }

    return false;
}

QString Crawler::getDir(int dir_id)
{
    return dir_paths[dir_id];
}

void Crawler::build(int type)
{
    switch (type) {
    case BST_TREE_TYPE:

        break;

    case TST_TREE_TYPE:

        break;

    case TRIE_TREE_TYPE:

        break;
    default:
        break;
    }
}

QStringList Crawler::listOfCrawledFiles()
{
    QStringList res;
    for (int i = 0; i < files_paths.size(); ++i)
    {
        res.append(files_paths[i]);
    }

    return res;
}

void Crawler::freeMemory()
{
    // Todo implement free memory function
}

Crawler::~Crawler()
{
    freeMemory();
}
