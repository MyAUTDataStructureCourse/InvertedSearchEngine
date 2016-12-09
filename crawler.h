#ifndef CRAWLER_H
#define CRAWLER_H

#include<string>
#include<vector>
#include <QString>

class WordPosition
{
private:
    int file_id;
    int line_num;
    int sentence_num;
    std::string last_word;
    std::string next_word;
public:
    WordPosition();
    WordPosition(int file_id, int line_num, int sentence_num, std::string last_word, std::string next_word);
};

class Word
{
private:
    std::string word_value;
    std::vector<WordPosition> positions;
public:
    void add_position(WordPosition position);

};

struct FileWordNode
{
    QString word;
    FileWordNode *last;
    FileWordNode *next;
    int line_num;

    FileWordNode();
    FileWordNode(QString word, int line_num);
};

class Crawler
{
private:
    std::vector<QString> files_paths;

    Crawler();

public:
    std::vector<FileWordNode *> file_words_starts;

    static Crawler& getInstance(){
        static Crawler instance;
        return instance;
    }

    void add_directory(std::string dir_path);
    bool add_file(QString file_path);

    bool add_file_to_list(QString file_path);
};

#endif // CRAWLER_H
