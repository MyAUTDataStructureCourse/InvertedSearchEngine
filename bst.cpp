#include "bst.h"
#include <QDebug>
#include <stack>

BSTNode::BSTNode(QString word, FileWordNode *pos_in_file)
{
    this->word = word;
    this->word_head = pos_in_file;
    this->word_last = pos_in_file;
    this->leftChild = NULL;
    this->rightChild = NULL;
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
                pointer = pointer->leftChild;
            }
            else        //      Two nodes have equal vaules
            {
                pointer->word_last->next_equal = pos_in_file;
                pos_in_file->last_equal = pointer->word_last;
                pointer->word_last = pos_in_file;
                pos_in_file->next_equal = NULL;
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

FileWordPositionWrapper BST::search(QString word)
{
    BSTNode *pointer = this->root;
    while(pointer)
    {
        if(QString::compare(pointer->word,word, Qt::CaseInsensitive) == 0)
        {
            qDebug() << pointer->word;

            qDebug() << pointer->word_head->last->word;

            qDebug() << pointer->word_last->word;
            if(pointer->word_last->last_equal != NULL)
                qDebug() << "Thiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii sis the buh";
            return FileWordPositionWrapper(pointer->word_head, pointer->word_last);
        }
        else if(QString::compare(pointer->word,word, Qt::CaseInsensitive) < 0)
        {
            pointer = pointer->leftChild;
        }
        else if(QString::compare(pointer->word,word, Qt::CaseInsensitive) > 0)
        {
            pointer = pointer->rightChild;
        }
    }

    return FileWordPositionWrapper(NULL, NULL);
}

QStringList BST::listAllWords()
{
    QStringList wordList;
    listAllWordsInOrderWithFileName(this->root,wordList);

    return wordList;
}

void BST::listAllWordsInOrderWithFileName(BSTNode *root, QStringList &list)
{

//    if(root = NULL)
//        return;
//    listAllWordsInOrderWithFileName(root->leftChild, list);
//    list.append(root->word);
//    listAllWordsInOrderWithFileName(root->rightChild, list);

    std::stack<BSTNode *> nodeStack;
    BSTNode *node = this->root;

    while(true)
    {
        if(node)
        {
            nodeStack.push(node);
            node = node->leftChild;
        }
        else
        {
            if (!nodeStack.empty())
            {
                node = nodeStack.top();
                list.append(node->word);
                nodeStack.pop();
                node = node->rightChild;
            }
            else
            {
                // Stack is empty and there is no pointer to travers so it's done
                break;
            }
        }
    }
}
