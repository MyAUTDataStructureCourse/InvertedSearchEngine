#ifndef TREE_H
#define TREE_H

#include <QString>
#include "crawler.h"

struct FileWordPositionWrapper
{
    FileWordPositionWrapper(FileWordNode *start, FileWordNode *end);
    FileWordNode *start;
    FileWordNode *end;
};

class Tree
{
public:
    static const short BST_TREE = 1;
    static const short TRIE_TREE = 2;
    static const short TST_TREE = 3;


    Tree();
    virtual void add(QString word, FileWordNode *pos_in_file) = 0;
    virtual FileWordPositionWrapper search(QString word) = 0;
    virtual QStringList listAllWords() = 0;
};

class TreeObject
{
private:
    TreeObject();
    
public:
    Tree *tree;

    static TreeObject &getInstance();

    void initTree(const short tree_type);
    QStringList listAllWords();
    Tree *getTree();

    QStringList searchWord(QString word);

    QStringList searchQuery(QString query);
};
#endif // TREE_H
