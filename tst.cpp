#include "tst.h"

TSTNode::TSTNode(char chr)
{
    this->chr = chr;
    this->biggerChild = nullptr;
    this->selfChild = nullptr;
    this->smallerChild = nullptr;
    this->isWord = false;

    word_head = NULL;
    word_last = NULL;
}

TST::TST()
{

}

void TST::add(QString word, FileWordNode *pos_in_file)
{
    word = word.toLower();

    TSTNode *pointer;
    if(!this->root)
    {

        this->root = new TSTNode(word[0].toLatin1());
        pointer = this->root;
        for (int i = 1; i < word.size(); ++i) {
            pointer->selfChild = new TSTNode(word[i].toLatin1());
            pointer = pointer->selfChild;
        }
    }
    else
    {
        int i = 0;

        pointer = this->root;
        char chrWord;

        for (; i < word.size() - 1;) {
            chrWord = word[i].toLatin1();
            if (chrWord < pointer->chr) {
                if (!pointer->smallerChild)
                    pointer->smallerChild = new TSTNode(chrWord);
                pointer = pointer->smallerChild;
            } else if (chrWord > pointer->chr) {
                if (!pointer->biggerChild)
                    pointer->biggerChild = new TSTNode(chrWord);
                pointer = pointer->biggerChild;
            } else {
                if (!pointer->selfChild)
                    pointer->selfChild = new TSTNode(word[i + 1].toLatin1());
                pointer = pointer->selfChild;
                i++;
            }
        }


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

FileWordPositionWrapper TST::search(QString word)
{
    word = word.toLower();

    int i = 0;
    if(!this->root)
        return FileWordPositionWrapper(NULL, NULL);

    TSTNode *pointer = this->root;
    char chrWord;

    for (; i < word.size() - 1;) {

        chrWord = word[i].toLatin1();
        if(chrWord < pointer->chr)
        {
            if (!pointer->smallerChild)
                return FileWordPositionWrapper(NULL, NULL);
            else
                pointer = pointer->smallerChild;
        }
        else if(chrWord > pointer->chr)
        {
            if (!pointer->biggerChild)
                return FileWordPositionWrapper(NULL, NULL);
            pointer = pointer->biggerChild;
        }
        else
        {
            if(! pointer->selfChild)
                return FileWordPositionWrapper(NULL, NULL);
            pointer = pointer->selfChild;
            i++;
        }
    }

    if(pointer->isWord)
    {
        return FileWordPositionWrapper(pointer->word_head, pointer->word_last);
    }
    else
    {
        return FileWordPositionWrapper(NULL, NULL);
    }
}

QStringList TST::listAllWords()
{

}
