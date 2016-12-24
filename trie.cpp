#include "trie.h"

TrieNode::TrieNode()
{
    for (int i = 0; i < MAX_ALPH; ++i) {
        children[i] = nullptr;
    }

    isWord = false;

    this->word_head = NULL;
    this->word_last = NULL;
}

Trie::Trie()
{
    this->root = new TrieNode;
}

void Trie::add(QString word, FileWordNode *pos_in_file)
{
    word = word.toLower();

    TrieNode *pointer = this->root;

    int childIndex;

    for (int i = 0; i < word.size(); ++i) {
        childIndex = word.at(i).toLatin1() - 'a';
        if(!pointer->children[childIndex])
            pointer->children[childIndex] = new TrieNode;
        pointer = pointer->children[childIndex];
    }
    if(pointer->isWord)
    {
        pointer->word_last->next_equal = pos_in_file;
        pos_in_file->last_equal = pointer->word_last;
        pointer->word_last = pos_in_file;
        pos_in_file->next_equal = NULL;
    }
    else
    {
        pointer->word_head = pos_in_file;
        pointer->word_last = pos_in_file;
        pointer->isWord = true;
    }
}

FileWordPositionWrapper Trie::search(QString word)
{
    word = word.toLower();

    TrieNode *pointer = this->root;

    int childIndex;

    for (int i = 0; i < word.size(); ++i) {
        childIndex = word.at(i).toLatin1() - 'a';
        if(pointer->children[childIndex])
            pointer = pointer->children[childIndex];
        else
            return FileWordPositionWrapper(NULL, NULL);
    }

    if(pointer->isWord)
        return FileWordPositionWrapper(pointer->word_head, pointer->word_last);
    else
        return FileWordPositionWrapper(NULL, NULL);
}

QStringList Trie::listAllWords()
{

}

void Trie::freeMemory()
{

}

Trie::~Trie()
{
    freeMemory();
}
