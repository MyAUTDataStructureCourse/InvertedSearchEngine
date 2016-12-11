#ifndef TRIE_H
#define TRIE_H
#include "tree.h"


class Trie : public Tree
{
public:
    void add(QString word, FileWordNode *pos_in_file);
    FileWordNode *search(QString word);

    Trie();
};

#endif // TRIE_H
