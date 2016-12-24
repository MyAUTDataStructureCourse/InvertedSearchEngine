#ifndef TST_H
#define TST_H
#include "tree.h"
#include <QStringList>

struct TSTNode
{
    char chr;
    TSTNode *smallerChild;
    TSTNode *selfChild;
    TSTNode *biggerChild;
    bool isWord;

    FileWordNode *word_head;
    FileWordNode *word_last;

    TSTNode(char chr);
};


class TST :public Tree
{
    TSTNode *root;
public:
    TST();
    void add(QString word, FileWordNode *pos_in_file);
    FileWordPositionWrapper search(QString word);
    QStringList listAllWords();
};

#endif // TST_H
