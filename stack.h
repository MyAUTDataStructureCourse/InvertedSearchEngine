#ifndef STACK_H
#define STACK_H


template <class type>
class StackNode
{
public:
    type data;
    StackNode *last;
};

template <class type> class Stack {
private:
    long size;
    StackNode <type>*head;

public:
    Stack();
    void push(type data);
    type *pop(type &data);
    type last();
    bool isEmpty();
    long getSize();
    ~Stack();

};

template <class type> Stack<type>::Stack()
{
    this->size = 0;
    this->head = nullptr;
}

template <class type> void Stack<type>::push(type data)
{
    size++;
    StackNode <type>*newNode = new StackNode<type>;
    newNode->data = data;
    newNode->last = this->head;
    this->head = newNode;
}

template <class type> type *Stack<type>::pop(type &data)
{
    size--;
    data = head->data;
    StackNode <type>*lastTemp = head->last;
    delete head;
    head = lastTemp;
    return &data;
}
template <class type> type Stack<type>::last()
{
    return (head->data)? head->data: nullptr;
}
template <class type> bool Stack<type>::isEmpty()
{
    return this->size == 0;
}

template <class type> long Stack<type>::getSize()
{
    return this->size;
}

template <class type> Stack<type>::~Stack()
{
    StackNode<type> *pointer = this->head;
    while(pointer)
    {
        StackNode<type> *temp = pointer;
        delete temp;
        pointer = pointer->last;
    }
}


#endif // STACK_H
