#ifndef TST_H
#define TST_H
#include "tree.h"

class TST :public Tree
{
public:
    TST();
    void add(QString word, FileWordNode *pos_in_file);
    FileWordNode *search(QString word);
};

#endif // TST_H
