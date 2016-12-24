#ifndef BST_H
#define BST_H

#include <QString>
#include <QStringList>
#include "tree.h"

struct BSTNode
{
    QString word;
    BSTNode *leftChild;
    BSTNode *rightChild;

    FileWordNode *word_head;
    FileWordNode *word_last;
    BSTNode();
    BSTNode(QString word, FileWordNode *pos_in_file);
};

class BST : public Tree
{
    BSTNode *root;
    void listAllWordsInOrderWithFileName(BSTNode *root, QStringList &list);

public:
    BST();
    void add(QString word, FileWordNode *pos_in_file);
    FileWordPositionWrapper search(QString word);
    QStringList listAllWords();
};

#endif // BST_H
