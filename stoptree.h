#ifndef STOPTREE_H
#define STOPTREE_H
#include <QString>

class StopTree
{
public:
    StopTree();
    virtual void add(QString word) = 0;
    virtual bool isExisted(QString word) = 0;
};

class StopTreeObject
{
private:

    StopTree *stopTree;
    StopTreeObject();
    QString filePath;

public:
    static StopTreeObject &getInstace();
    void setStopWordFilePath(QString filePath);

    void buildBST();
    void buildTrie();
    void buildTST();


    void buildTree();
    bool isExisted(QString word);

    ~StopTreeObject();
};

struct BSTStopNode
{
    BSTStopNode(QString &word);
    QString value;
    BSTStopNode *leftChild;
    BSTStopNode *rightChild;
};

class BSTStop : public StopTree
{
    BSTStopNode *root;
public:
    BSTStop();
    void add(QString word);
    bool isExisted(QString word);
};

class TSTStop : public StopTree
{
public:
    void add(QString word);
    bool isExisted(QString word);
};

class TrieStop : public StopTree
{
public:
    void add(QString word);
    bool isExisted(QString word);
};

#endif // STOPTREE_H
