#include "tree.h"
#include "bst.h"
#include "tst.h"
#include "trie.h"
#include <QDebug>

FileWordPositionWrapper::FileWordPositionWrapper(FileWordNode *start, FileWordNode *end)
{
    this->start = start;
    this->end = end;
}

Tree::Tree()
{

}


TreeObject::TreeObject()
{

}

void TreeObject::initTree(const short tree_type)
{
    switch (tree_type) {
    case Tree::BST_TREE:
        this->tree = new BST;
        break;
    case Tree::TST_TREE:
        this->tree = new TST;
        break;
    case Tree::TRIE_TREE:
        this->tree = new Trie;
        break;
    }
}

Tree *TreeObject::getTree()
{
    return this->tree;
}

TreeObject &TreeObject::getInstance()
{
    static TreeObject instance;
    
    return instance;
}

QStringList TreeObject::listAllWords()
{
    return this->tree->listAllWords();
}

QStringList TreeObject::searchWord(QString word)
{
    QStringList list;
    FileWordPositionWrapper res = tree->search(word);

    FileWordNode *pointer = res.start;
    while (pointer != NULL)
    {
        list.append(Crawler::getInstance().getFileName(pointer->file_id));
        pointer = pointer->next_equal;
    }

    return list;
}

QStringList TreeObject::searchQuery(QString query)
{

}
