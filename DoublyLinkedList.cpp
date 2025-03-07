#include <iostream>
#include <fstream>

using namespace std;

struct listNode
{
    int myId;
    int myInv;
    listNode* next;

    listNode(int, int, listNode*);
};

listNode::listNode(int id, int inv, listNode* tempNext)
{
    myId = id;
    myInv = inv;
    next = tempNext;
}

typedef listNode* listPtr;

struct listType
{
    listPtr first;
    listPtr last;
};

void loadFile(listType&, string);
void insertNotInOrder(listType&, int, int);
void printList(listType&);
void reverseList(listPtr&);
listType mergeSort(listType&);
void remove(listType&, int, int);

void split(listType&, listType&);
listType merge(listType&, listType&);
int countNodes(listType&);
void mainMenu(listType&);



void loadFile(listType& list, string fileName)
{
    ifstream reader(fileName);
    int id, inv;

    while (reader >> id >> inv)
    {
        insertNotInOrder(list, id, inv);
    }

    reader.close();
}

void insertNotInOrder(listType& temp, int id, int inv)
{
    listNode* newNode = new listNode(id, inv, nullptr);

    // EMPTY LIST
    if (temp.first == nullptr)
    {
        temp.first = newNode;
        temp.last = temp.first;
    }
    else
    {
        // INSERT AT THE END
        temp.last->next = newNode;
        temp.last = newNode;
    }
}


void printList(listType& list)
{
    listNode* current = list.first;

    while (current != nullptr)
    {
        cout << current->myId << "\t" << current->myInv << "\n";
        current = current->next;
    }
}

void reverseList(listPtr& root)
{
    listPtr back = nullptr;
    listPtr node = root;
    listPtr front = nullptr;

    while (node != nullptr)
    {
        front = node->next;
        node->next = back;
        back = node;
        node = front;
    }

    //voided inittialy on .first
    root = back;
}

void split(listType& listA, listType& listB)
{
    listB.first = nullptr;
    listB.last = nullptr;

    int mid = countNodes(listA) / 2;

    listPtr temp = listA.first;
    listPtr previous = nullptr;

    for (int i = 0; i < mid && temp != nullptr; ++i)
    {
        previous = temp;
        temp = temp->next;
    }

    if (previous != nullptr)
    {
        previous->next = nullptr;
    }

    if (temp != nullptr)
    {
        listB.first = temp;
        listB.last = listA.last;
        listA.last = previous;
    }
}




listType merge(listType& listA, listType& listB)
{
    listType mergedList;
    mergedList.first = nullptr;
    mergedList.last = nullptr;

    listPtr tempA = listA.first;
    listPtr tempB = listB.first;

    while (tempA != nullptr && tempB != nullptr)
    {
        if (tempA->myId < tempB->myId)
        {
            insertNotInOrder(mergedList, tempA->myId, tempA->myInv);
            tempA = tempA->next;
        }
        else
        {
            insertNotInOrder(mergedList, tempB->myId, tempB->myInv);
            tempB = tempB->next;
        }
    }


    while (tempA != nullptr)
    {
        insertNotInOrder(mergedList, tempA->myId, tempA->myInv);
        tempA = tempA->next;
    }


    while (tempB != nullptr)
    {
        insertNotInOrder(mergedList, tempB->myId, tempB->myInv);
        tempB = tempB->next;
    }

    return mergedList;
}


listType mergeSort(listType& listA)
{
    listType listB;
    listB.first = nullptr;
    listB.last = nullptr;

    if (countNodes(listA) <= 1)
    {
        return listA;
    }

    split(listA, listB);

    listA = mergeSort(listA);
    listB = mergeSort(listB);

    return merge(listA, listB);
}



int countNodes(listType& list)
{
    listNode* temp = list.first;
    int count = 0;

    while (temp != nullptr)
    {
        temp = temp->next;
        count++;
    }

    return count;
}


void remove(listType& temp, int id, int inv)
{
    listNode* front = temp.first->next;
    listNode* back = temp.first;

    // EMPTY LIST
    if (temp.first == nullptr)
    {
        return;
    }

    // REMOVE FIRST NODE
    if (back->myId == id)
    {
        temp.first = front;

        if (temp.first == nullptr)
        {
            temp.last = nullptr;
        }

        return;
    }

    while (front != nullptr)
    {
        if (front->myId == id)
        {
            // LAST CHECKER

            if (front->next == nullptr)
            {
                temp.last = back;
                temp.last->next = nullptr;
                return;
            }

            back->next = front->next;
            return;
        }
        else
        {
            front = front->next;
            back = back->next;
        }
    }
}


void mainMenu(listType& list)
{
    char choice;

    do
    {
        cout << "Linked List algorithm menu\n";
        cout << "(1) Read data from disk\n";
        cout << "(2) Print list\n";
        cout << "(3) Recursive Merge Sort\n";
        cout << "(4) Reverse List\n";
        cout << "(Q) Quit\n";
        cout << "Choice ---> ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            loadFile(list, "file50.txt");
            cout << "\n";
            break;
        case '2':
            cout << "The list printed\n";
            printList(list);
            cout << "\n";
            break;
        case '3':
            list = mergeSort(list);
            cout << "\n";
            break;

        case '4':
            reverseList(list.first);
            cout << "List reversed\n";
            cout << "\n";
            break;
        case 'Q':
        case 'q':
            cout << "Exiting the program\n";
            cout << "\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            cout << "\n";
            break;
        }

    } while (toupper(choice) != 'Q');
}

int main()
{
    listType list;
    list.first = nullptr;
    list.last = nullptr;

    mainMenu(list);
}