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
    void buildTree();

    ~StopTreeObject();
};

class BSTStop : public StopTree
{
    void add(QString word);
    bool isExisted(QString word);
};

#endif // STOPTREE_H
