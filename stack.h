#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "listNode.h"

using namespace std;

template <class itemType>
class stack
{
private:
    listNode<itemType>* root;

public:
    stack()
    {
        root = nullptr;
    }

    void push(itemType newItem)
    {
        if (root == nullptr)
        {
            root = new listNode<itemType>(newItem);
        }

        else
        {
            listNode<itemType>* temp = root;
            while (temp->getNext() != nullptr)
            {
                temp = temp->getNext();
            }

            temp->setNext(new listNode<itemType>(newItem));
        }
    }

    bool empty()
    {
        if (root == nullptr)
        {
            return true;
        }

        return false;
    }

    void pop()
    {
        //none in stack
        if (root == nullptr)
        {
            cout << "Pop empty stack.\n";
        }

        //one in stack
        else if (root->getNext() == nullptr)
        {
            delete root;
            root = nullptr;
        }

        //back of the line
        else
        {
            listNode<itemType>* temp = root;
            listNode<itemType>* prev = nullptr;

            while (temp->getNext() != nullptr)
            {
                prev = temp;
                temp = temp->getNext();
            }

            delete temp;
            prev->setNext(nullptr);
        }
    }

    int size() const
    {
        int count = 0;
        listNode<itemType>* temp = root;
        while (temp != nullptr)
        {
            count++;
            temp = temp->getNext();
        }
        return count;
    }


    itemType& top()
    {
        if (root == nullptr)
        {
            cout << "Stack is empty\n";
        }

        else
        {
            listNode<itemType>* temp = root;

            while (temp->getNext() != nullptr)
            {
                temp = temp->getNext();
            }

            return temp->getValue();
        }
    }

    void loadFile(stack<itemType>& stack, string fileName)
    {
        ifstream reader(fileName);
        int id, inv;

        while (reader >> id >> inv)
        {
            push({ id, inv });
        }

        reader.close();
    }


};

#endif