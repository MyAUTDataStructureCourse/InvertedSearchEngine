#include "bst.h"
BSTNode::BSTNode(QString word, FileWordNode *pos_in_file)
{
    this->word = word;
    this->word_head = pos_in_file;
    this->word_last = pos_in_file;    
}

BSTNode::BSTNode()
{

}

BST::BST()
{
    this->root = NULL;
}

void BST::add(QString word, FileWordNode *pos_in_file)
{
    BSTNode *newNode = new BSTNode;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->word = word;

    if(this->root)
    {
        BSTNode *pointer = this->root;
        BSTNode *parent = NULL;

        while(pointer)
        {
            parent = pointer;
            if(QString::compare(pointer->word, word, Qt::CaseInsensitive) > 0)
            {
                pointer = pointer->rightChild;
            }
            else if(QString::compare(pointer->word, word, Qt::CaseInsensitive) < 0)
            {
                pointer = pointer->rightChild;
            }
            else        //      Two nodes have equal vaules
            {
                pointer->word_last->next = pos_in_file;
                pos_in_file->last = pointer->word_last;
                pointer->word_last = pos_in_file;
                break;
            }
        }

        if(QString::compare(parent->word, word, Qt::CaseInsensitive) < 0)
        {
            parent->leftChild = newNode;
            parent->leftChild->word_head = pos_in_file;
            parent->leftChild->word_last = pos_in_file;
        }
        else if(QString::compare(parent->word, word, Qt::CaseInsensitive) > 0)
        {
            parent->rightChild = newNode;
            parent->rightChild->word_head = pos_in_file;
            parent->rightChild->word_last = pos_in_file;
        }

    }
    else
    {
        this->root = new BSTNode(word,pos_in_file);
    }
}

FileWordNode *BST::search(QString word)
{
    BSTNode *pointer = this->root;
    while(pointer)
    {
        if(pointer->word == word)
        {
            return pointer->word_head;
        }
        else if(word < pointer->word)
        {
            pointer = pointer->leftChild;
        }
        else if(word > pointer->word)
        {
            pointer = pointer->rightChild;
        }
    }

    return NULL;
}
