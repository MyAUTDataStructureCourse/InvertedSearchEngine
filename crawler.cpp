#include "crawler.h"
#include <log.h>
#include <QFile>
#include <QTextStream>
#include "terminal.h"

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

bool Crawler::add_file(QString file_path)
{
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    this->files_paths.push_back(file_path);
    this->file_words_starts.push_back(new FileWordNode());

    FileWordNode *last = this->file_words_starts[this->file_words_starts.size() - 1];

    QTextStream input(&file);
    QString line;
    QStringList wordsList;

    int line_num = 1;

    while(!input.atEnd())
    {
        line = input.readLine();
        wordsList = line.split(QRegExp("\\W+"), QString::SkipEmptyParts);
        for(int i = 0; i < wordsList.size(); i++)
        {
            last->next = new FileWordNode(wordsList[i], line_num);
            last->next->last = last;
            last = last->next;

        }

        line_num++;
    }

    return true;
}
void Crawler::add_directory(std::__cxx11::string dir_path)
{

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
