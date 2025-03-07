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
void insertInOrder(listType&, int, int);
listNode* find(listType&, int, int);
bool remove(listType&, int, int);
void clearList(listType&);
int countNodes(listType&);
void printList(listType&);
void backwards(listType&, listNode*);
void printBackwards(listType&);

void testFind(listType&);
void testDelete(listType&);
void mainMenu(listType&);



void loadFile(listType& list, string fileName)
{
    ifstream reader(fileName);
    int id, inv;

    while (reader >> id >> inv)
    {
        insertInOrder(list, id, inv);
    }

    reader.close();
}

void insertInOrder(listType& temp, int id, int inv)
{
    listNode* newNode = new listNode(id, inv, nullptr);

    //EMPTY LIST
    if (temp.first == nullptr)
    {
        temp.first = newNode;
        temp.last = temp.first;
    }

    //ADD BEFORE FIRST
    else if (temp.first->myId > id)
    {
        if (temp.last == nullptr)
        {
            temp.first = newNode;
            temp.last = temp.first;
        }

        else
        {
            listNode* newerNode = new listNode(id, inv, temp.first);
            temp.first = newerNode;
        }
    }

    //DUPLICATE 
    //BACK OF LIST
    else if (temp.last->myId <= id)
    {
        if (temp.first == nullptr)
        {
            temp.first = newNode;
            temp.last = temp.first;
        }

        else
        {
            temp.last->next = newNode;
            temp.last = temp.last->next;
        }
    }

    //INSERT IN THE MIDDLE
    else
    {
        listNode* front = temp.first->next;
        listNode* back = temp.first;

        while (front->myId < id)
        {
            front = front->next;
            back = back->next;
        }

        listNode* newestNode = new listNode(id, inv, front);
        back->next = newestNode;
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

listNode* find(listType& temp, int id, int inv)
{
    //EMPTY LIST
    listNode* temper = temp.first;

    if (temp.first == nullptr)
    {
        return nullptr;
    }

    while (temper != nullptr)
    {
        if (temper->myId == id)
        {
            return temper;
        }

        else
        {
            temper = temper->next;
        }
    }

    return nullptr;
}

bool remove(listType& temp, int id, int inv)
{
    listNode* front = temp.first->next;
    listNode* back = temp.first;

    //EMPTY LIST
    if (temp.first == nullptr)
    {
        return false;
    }

    //REMOVE FIRST NODE
    if (back->myId == id)
    {
        temp.first = front;

        if (temp.first == nullptr)
        {
            temp.last = nullptr;
        }

        return true;
    }

    while (front != nullptr)
    {
        if (front->myId == id)
        {
            //LAST CHECKER

            if (front->next == nullptr)
            {
                temp.last = back;
                temp.last->next = nullptr;
                return true;
            }

            back->next = front->next;
            return true;
        }

        else
        {
            front = front->next;
            back = back->next;
        }
    }

    return false;
}

void clearList(listType& list)
{
    list.first = nullptr;
    list.last = nullptr;
}

int countNodes(listType& list)
{
    listNode* temp = list.first;
    int count = 0;

    if (list.first == nullptr)
    {
        return count;
    }

    while (temp->next != nullptr)
    {
        temp = temp->next;
        count++;
    }

    count++;
    return count;
}

void backwards(listType& list, listNode* temp)
{
    if (temp->next == nullptr)
    {
        cout << list.last->myId << "\t" << list.last->myInv << "\n";
    }

    else
    {
        backwards(list, temp->next);
        cout << temp->myId << "\t" << temp->myInv << "\n";
    }
}

void printBackwards(listType& list)
{
    backwards(list, list.first);
    cout << "\n";
}

void testFind(listType& list)
{
    int idToFind;
    listNode* location;

    cout << "Testing search algorithm\n";
    cout << "Enter Id value to search for (-1 to quit) --> ";
    cin >> idToFind;

    while (idToFind >= 0)
    {
        location = find(list, idToFind, 0);

        if (location == nullptr)
        {
            cout << "Id = " << idToFind << " No such part in stock";
        }

        else
        {
            cout << "Id = " << location->myId << " " << "Inv = " << location->myInv;
        }

        cout << "\n";
        cout << "Enter Id value to search for (-1 to quit) --> ";
        cin >> idToFind;
    }
}

void testDelete(listType& list)
{
    int idToDelete;

    cout << "Testing delete algorithm\n";
    cout << "Enter Id value to delete (-1 to quit) --> ";
    cin >> idToDelete;

    while (idToDelete >= 0)
    {
        if (remove(list, idToDelete, 0))
        {
            cout << "Id = " << idToDelete << " was deleted\n";
        }

        else
        {
            cout << "Id = " << idToDelete << "  No such part in stock\n";
        }

        cout << "\n";
        cout << "Enter Id value to delete (-1 to quit) --> ";
        cin >> idToDelete;
    }
}

void mainMenu(listType& list)
{
    char choice;

    do
    {
        cout << "Linked List algorithm menu\n";
        cout << "(1) Read data from disk\n";
        cout << "(2) Print ordered list\n";
        cout << "(3) Search list\n";
        cout << "(4) Delete from list\n";
        cout << "(5) Clear entire list\n";
        cout << "(6) Count nodes in list\n";
        cout << "(7) Print list backwards\n";
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
            cout << "The list printed inorder\n";
            printList(list);
            cout << "\n";
            break;
        case '3':
            testFind(list);
            cout << "\n";
            break;
        case '4':
            testDelete(list);
            cout << "\n";
            break;
        case '5':
            clearList(list);
            cout << "Entire list cleared\n";
            cout << "\n";
            break;
        case '6':
            cout << "Number of nodes = " << countNodes(list) << "\n";
            cout << "\n";
            break;
        case '7':
            cout << "The list printed backwards\n";
            printBackwards(list);
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