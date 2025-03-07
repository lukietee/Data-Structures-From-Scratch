#ifndef LISTNODE_H
#define LISTNODE_H

template <class itemType>
class listNode
{
public:
    listNode();
    listNode(itemType);
    itemType& getValue();
    void setValue(itemType);
    void setNext(listNode* target);
    listNode* getNext() const;

private:
    itemType value;
    listNode* next;
};

template <class itemType>
listNode<itemType>::listNode() : value(), next(nullptr)
{

}

template <class itemType>
listNode<itemType>::listNode(itemType val) : value(val), next(nullptr)
{

}

template<class itemType>
itemType& listNode<itemType>::getValue()
{
    return value;
}

template<class itemType>
void listNode<itemType>::setValue(itemType target)
{
    value = target;
}

template<class itemType>
void listNode<itemType>::setNext(listNode* target)
{
    next = target;
}

template<class itemType>
listNode<itemType>* listNode<itemType>::getNext() const
{
    return next;
}

#endif