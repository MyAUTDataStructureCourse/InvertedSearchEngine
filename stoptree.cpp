#include "stoptree.h"
#include "terminal.h"
#include <QTextStream>
#include <QTime>
#include <QDebug>

#define TRIE_NULL_CHAR ' '
#define MAX 50

StopTree::StopTree()
{

}

StopTreeObject::StopTreeObject()
{
    stopTree = NULL;
}

StopTreeObject &StopTreeObject::getInstace()
{
    static StopTreeObject instance;

    return instance;
}

void StopTreeObject::setStopWordFilePath(QString filePath)
{
    QFile file(filePath);
    if(file.exists())
    {
        Terminal::getInstance().writeLine("File \"" + filePath + "\" is set for stop words file successfully.");
        this->filePath = filePath;
    }
    else
    {
        Terminal::getInstance().writeLine("err : File \"" + filePath + "\" is not exists.");
    }
}

void StopTreeObject::buildBST()
{
    stopTree = new BSTStop;
}

void StopTreeObject::buildTrie()
{
    stopTree = new TrieStop;
}

void StopTreeObject::buildTST()
{
    stopTree = new TSTStop;
}

void StopTreeObject::buildTree()
{
    qDebug() << QString("this line executed here ");

    QTime timer;        // Timer for measuring the time elapsed for adding stop words to their tree

    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        Terminal::getInstance().writeLine("Reading from file : \"" + filePath + "\" ...");

        QTextStream in(&file);

        timer.start();  // Start the timer

        int wordCound = 0;
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList list = line.split(QRegExp("\\W+"), QString::SkipEmptyParts);


            for(int i = 0; i < list.size(); i++)
            {
                stopTree->add(QString(list[i]).toLower());
                wordCound ++;
            }
        }


        int time = timer.elapsed();
        Terminal::getInstance().writeLine(QString("%1 word(s) added to tree in %2 ms.").arg(wordCound).arg(time));
        file.close();

        Terminal::getInstance().writeLine("File : \"" + filePath + "\" closed.");
    }
    else
    {
        Terminal::getInstance().writeLine("Unable to open the file : \"" + filePath + "\".");
    }
}

bool StopTreeObject::isExisted(QString word)
{
    return this->stopTree->isExisted(word);
}

StopTreeObject::~StopTreeObject()
{
    delete stopTree;
}

BSTStopNode::BSTStopNode(QString &word)
{
    this->value = word;
    leftChild = NULL;
    rightChild = NULL;
}

BSTStop::BSTStop()
{
    this->root = NULL;
}

void BSTStop::add(QString word)
{

    BSTStopNode *newNode = new BSTStopNode(word);

    if(this->root != NULL)
    {

        BSTStopNode *pointer = this->root;
        BSTStopNode *parent = NULL;

        while(pointer)
        {
            parent = pointer;
            if(QString::compare(pointer->value, word, Qt::CaseInsensitive) == 0)
            {
                return;
            }
            else if(QString::compare(pointer->value, word, Qt::CaseInsensitive) > 0)
            {
                pointer = pointer->leftChild;
            }
            else if(QString::compare(pointer->value, word, Qt::CaseInsensitive) < 0)
            {
                pointer = pointer->rightChild;
            }
        }

        if(QString::compare(parent->value, word, Qt::CaseInsensitive) > 0)
            parent->leftChild = newNode;
        else if(QString::compare(parent->value, word, Qt::CaseInsensitive) < 0)
            parent->rightChild = newNode;

    }
    else
    {
        root = newNode;
    }
}

bool BSTStop::isExisted(QString word)
{
    BSTStopNode *pointer = this->root;

    while(pointer)
    {

        if(QString::compare(pointer->value, word, Qt::CaseInsensitive) == 0)
        {
            return true;
        }
        else if(QString::compare(pointer->value, word, Qt::CaseInsensitive) > 0)
        {
            pointer = pointer->leftChild;
        }
        else if(QString::compare(pointer->value, word, Qt::CaseInsensitive) < 0)
        {
            pointer = pointer->rightChild;
        }
    }

    return false;
}

void TSTStop::add(QString word)
{
    insert(word.toLatin1().data());
}

bool TSTStop::isExisted(QString word)
{
    return search(word.toLatin1().data());
}

TSTStop::TSTStop()
{
    root = NULL;
}

int TSTStop::search(char *word)
{
    return searchTST(root, word);
}
// A utility function to create a new ternary search tree node
TSTStopNode* TSTStop::newNode(char data)
{
    TSTStopNode* temp = (TSTStopNode *) malloc(sizeof(TSTStopNode));
    temp->data = data;
    temp->isEndOfString = 0;
    temp->left = temp->eq = temp->right = NULL;
    return temp;
}

void TSTStop::insert(char *word)
{
    insertUtil(&root, word);
}
// Function to insert a new word in a Ternary Search Tree
void TSTStop::insertUtil(TSTStopNode** root, char *word)
{
    // Base Case: Tree is empty
    if (!(*root))
        *root = newNode(*word);

    // If current character of word is smaller than root's character,
    // then insert this word in left subtree of root
    if ((*word) < (*root)->data)
        insertUtil(&( (*root)->left ), word);

        // If current character of word is greate than root's character,
        // then insert this word in right subtree of root
    else if ((*word) > (*root)->data)
        insertUtil(&( (*root)->right ), word);

        // If current character of word is same as root's character,
    else
    {
        if (*(word+1))
            insertUtil(&( (*root)->eq ), word+1);

            // the last character of the word
        else
            (*root)->isEndOfString = 1;
    }
}

// A recursive function to traverse Ternary Search Tree
void TSTStop::traverseTSTUtil(TSTStopNode* root, char* buffer, int depth)
{
    if (root)
    {
        // First traverse the left subtree
        traverseTSTUtil(root->left, buffer, depth);

        // Store the character of this node
        buffer[depth] = root->data;
        if (root->isEndOfString)
        {
            buffer[depth+1] = '\0';
            printf( "%s\n", buffer);
        }

        // Traverse the subtree using equal pointer (middle subtree)
        traverseTSTUtil(root->eq, buffer, depth + 1);

        // Finally Traverse the right subtree
        traverseTSTUtil(root->right, buffer, depth);
    }
}

// The main function to traverse a Ternary Search Tree.
// It mainly uses traverseTSTUtil()
void TSTStop::traverseTST()
{
    char buffer[MAX];
    traverseTSTUtil(root, buffer, 0);
}

// Function to search a given word in TST
int TSTStop::searchTST(TSTStopNode *root, char *word)
{
    if (!root)
        return 0;

    if (*word < (root)->data)
        return searchTST(root->left, word);

    else if (*word > (root)->data)
        return searchTST(root->right, word);

    else
    {
        if (*(word+1) == '\0')
            return root->isEndOfString;

        return searchTST(root->eq, word+1);
    }
}


TrieStopNode* TrieStopNode::findChild(char c)
{
    for ( int i = 0; i < mChildren.size(); i++ )
    {
        TrieStopNode* tmp = mChildren.at(i);
        if ( tmp->content() == c )
        {
            return tmp;
        }
    }

    return NULL;
}

TrieStop::TrieStop()
{
    root = new TrieStopNode();
}

TrieStop::~TrieStop()
{
    // Free memory
}

void TrieStop::add(QString s)
{
    TrieStopNode* current = root;

    if ( s.length() == 0 )
    {
        current->setWordMarker(); // an empty word
        return;
    }

    for ( int i = 0; i < s.length(); i++ )
    {
        TrieStopNode* child = current->findChild(s.at(i).toLatin1());
        if ( child != NULL )
        {
            current = child;
        }
        else
        {
            TrieStopNode* tmp = new TrieStopNode();
            tmp->setContent(s.at(i).toLatin1());
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setWordMarker();
    }
}


bool TrieStop::isExisted(QString s)
{
    TrieStopNode* current = root;

    while ( current != NULL )
    {
        for ( int i = 0; i < s.length(); i++ )
        {
            TrieStopNode* tmp = current->findChild(s.at(i).toLatin1());
            if ( tmp == NULL )
                return false;
            current = tmp;
        }

        if ( current->wordMarker() )
            return true;
        else
            return false;
    }

    return false;
}
