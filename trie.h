#ifndef TRIE_H
#define TRIE_H
#include "tree.h"
#include <QStringList>

#define MAX_ALPH 26

struct TrieNode
{
    bool isWord;
    TrieNode *children[MAX_ALPH];

    FileWordNode *word_head;
    FileWordNode *word_last;

    TrieNode();
};


class Trie : public Tree
{
    TrieNode *root;

    void freeMemory();

public:
    void add(QString word, FileWordNode *pos_in_file);
    FileWordPositionWrapper search(QString word);
    QStringList listAllWords();


    Trie();

    ~Trie();
};

#endif // TRIE_H
