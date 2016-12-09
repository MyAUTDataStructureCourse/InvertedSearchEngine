
#include "tree.h"
#include "bst.h"

Tree::Tree()
{

}



void TreeObject::initTree(const short tree_type)
{
    switch (tree_type) {
    case Tree::BST_TREE:
        this->tree = new BST;
        break;
    case Tree::TST_TREE:

        break;
    case Tree::TRIE_TREE:

        break;
    }
}

Tree *TreeObject::getTree()
{
    return this->tree;
}
