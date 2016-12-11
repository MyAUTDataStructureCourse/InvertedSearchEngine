#ifndef STOPTREE_H
#define STOPTREE_H

#include <QString>
#include <vector>

#define NUM_OF_ENGLISH_LETTERS 26

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


// A node of ternary search tree
struct TSTStopNode
{
    char data;

    // True if this character is last character of one of the words
    unsigned isEndOfString = 1;

    TSTStopNode *left, *eq, *right;
};


class TSTStop : public StopTree
{

    TSTStopNode *root;


    void insert(char *word);
    void insertUtil(TSTStopNode** root, char *word);
    TSTStopNode *newNode(char data);
    void traverseTSTUtil(TSTStopNode *root, char* buffer, int depth);
    void traverseTST();
    int searchTST(TSTStopNode *root, char *word);
    int search(char *word);

public:

    TSTStop();
    void add(QString word);
    bool isExisted(QString word);

};




class TrieStopNode {
public:
    TrieStopNode() { mContent = ' '; mMarker = false; }
    ~TrieStopNode() {}
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    bool wordMarker() { return mMarker; }
    void setWordMarker() { mMarker = true; }
    TrieStopNode* findChild(char c);
    void appendChild(TrieStopNode* child) { mChildren.push_back(child); }
    std::vector<TrieStopNode*> children() { return mChildren; }

private:
    char mContent;
    bool mMarker;
    std::vector<TrieStopNode*> mChildren;
};

class TrieStop : public StopTree {
public:
    TrieStop();
    ~TrieStop();
    void add(QString s);
    bool isExisted(QString s);
    void deleteWord(QString s);
private:
    TrieStopNode* root;
};

#endif // STOPTREE_H
