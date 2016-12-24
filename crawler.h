#ifndef CRAWLER_H
#define CRAWLER_H

#include<string>
#include<vector>
#include <QString>

#define BST_TREE_TYPE 0
#define TST_TREE_TYPE 1
#define TRIE_TREE_TYPE 2

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
    FileWordNode *last_equal;
    FileWordNode *next_equal;
    int line_num;
    int file_id;

    FileWordNode();
    FileWordNode(QString word, int line_num, int file_id);
};

class Crawler
{
private:
    std::vector<QString> files_paths;
    std::vector<QString> dir_paths;

    Crawler();

    void tokenizeString(QStringList &tokes,QString &line);

    void freeMemory();

public:
    static Crawler& getInstance();

    std::vector<FileWordNode *> file_words_starts;

    void crawlAll();
    void build(int type);
    void add_directory(QString dir_path);
    QStringList listFiles(int dir_id = 0);
    QStringList listOfCrawledFiles();
    void addFilesOfDirectoriesToFilelist();
    QString getDir(int dir_id = 0);

    QString getFileName(int id);

    bool isFileExistedInList(QString path);

    /**
     * @brief crawlFile
     * a fucntion to parse the tree and add it to the linked list
     * @param file_path
     * @return
     */
    bool crawlFile(QString file_path);

    bool add_file_to_list(QString file_path);

    void buildTree();

    ~Crawler();
};

QString linkedListToString(FileWordNode *node);

#endif // CRAWLER_H
