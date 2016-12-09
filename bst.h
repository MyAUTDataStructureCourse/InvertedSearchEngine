#ifndef BST_H
#define BST_H

#include <QString>
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

public:
    BST();
    void add(QString word, FileWordNode *pos_in_file);
    FileWordNode *search(QString word);
};

#endif // BST_H
