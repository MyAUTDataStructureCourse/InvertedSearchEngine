
#include "tree.h"
#include "bst.h"
#include "tst.h"
#include "trie.h"

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
