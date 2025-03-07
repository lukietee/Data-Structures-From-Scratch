#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct listNode {
   int myId;
   int myInv;
   listNode *next;
   int hashCode;

   listNode(int, int, listNode *);
};

listNode::listNode(int id, int inv, listNode *tempNext) {
   myId = id;
   myInv = inv;
   next = tempNext;

   hashCode =
       abs(static_cast<int>(myId * tan(myId) * sin(myId) * sqrt(myId))) % 599;
}

typedef listNode *listPtr;

class HashTable {
 public:
   int size;
   int capacity;
   vector<listNode *> myHashTable;

   HashTable() {
      size = 0;
      capacity = 600;
      myHashTable.resize(capacity);
   }

   HashTable(int numSlots) {
      size = 0;
      capacity = numSlots;
      myHashTable.resize(capacity);
   }

   int getSize() { return size; }

   int getCapacity() { return capacity; }

   void add(listNode *node) {
      listNode *newerNode =
          new listNode(node->myId, node->myInv, myHashTable[node->hashCode]);
      myHashTable[node->hashCode] = newerNode;

      size++;
   }

   listNode *find(listNode *node) {
      for (int i = 0; i < capacity; i++) {
         listNode *tempNode = myHashTable[i];

         while (tempNode != nullptr) {
            if (node->myId == tempNode->myId) {
               return tempNode;
            }

            else {
               tempNode = tempNode->next;
            }
         }
      }
   }

   int getNumberOfNulls() {
      int nullCounter = 0;
      int hashIndex = 0;
      listNode *tempNode = myHashTable[hashIndex];

      while (hashIndex < myHashTable.size()) {
         if (myHashTable[hashIndex] == nullptr) {
            nullCounter++;
         }

         hashIndex++;
      }

      return nullCounter;
   }

   int getLongestList() {
      int largestSize = 0;
      int tempSize = 0;

      for (int i = 0; i < capacity; i++) {
         tempSize = 0;
         listNode *tempNode = myHashTable[i];

         while (tempNode != nullptr) {
            tempSize++;

            tempNode = tempNode->next;
         }

         if (tempSize > largestSize) {
            largestSize = tempSize;
         }
      }

      return largestSize;
   }

   void printHashTable() {
      for (int i = 0; i < capacity; i++) {
         listNode *tempNode = myHashTable[i];
         cout << i << ")  ";

         while (tempNode != nullptr) {
            cout << "Id = " << tempNode->myId << " Inv = " << tempNode->myInv
                 << "\t";
            tempNode = tempNode->next;
         }

         cout << "\n";
      }
   }

   void testFind() {
      int idToFind;
      listNode *location;

      cout << "Testing search algorithm\n";
      cout << "Enter Id value to search for (-1 to quit) --> ";
      cin >> idToFind;

      while (idToFind >= 0) {
         listNode tempNode(idToFind, 0, nullptr);

         location = find(&tempNode);

         if (location == nullptr) {
            cout << "Id = " << idToFind << " No such part in stock\n";
         } else {
            cout << "Id = " << location->myId << "Inv = " << location->myInv
                 << " found in hash table.\n";
         }

         cout << "\n";
         cout << "Enter Id value to search for (-1 to quit) --> ";
         cin >> idToFind;
      }
   }

   void stats() {
      double numNulls =
          (getNumberOfNulls() / static_cast<double>(capacity)) * 100.0;
      double avgLength = 0;
      int nonNullLists = capacity - getNumberOfNulls();

      if (nonNullLists > 0) {
         avgLength = static_cast<double>(getSize()) / nonNullLists;
      }

      cout << "Percentage of Null Pointers --> " << numNulls << "%\n";
      cout << "Average Length Non-Null Linked Lists --> " << avgLength << "\n";
      cout << "Longest Linked List --> " << getLongestList() << "\n";
   }

   void loadFile(string filename) {
      ifstream reader(filename);
      int id, inv;

      while (reader >> id >> inv) {
         listNode *newNode = new listNode(id, inv, nullptr);
         add(newNode);
      }

      reader.close();
   }
};

void mainMenu(HashTable hasher) {
   char choice;

   do {
      cout << "HashTable Menu\n";
      cout << "(1) Read a file from disk\n";
      cout << "(2) Print HashTable\n";
      cout << "(3) Search\n";
      cout << "(4) Stats\n";
      cout << "(Q) Quit\n";
      cout << "Choice ---> ";
      cin >> choice;

      switch (choice) {
      case '1':
         hasher.loadFile("file400.txt");
         cout << "File has been loaded\n";
         cout << "\n";
         break;
      case '2':
         hasher.printHashTable();
         cout << "\n";
         break;
      case '3':
         hasher.testFind();
         cout << "\n";
         break;
      case '4':
         hasher.stats();
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

int main() {
   HashTable hashing;

   mainMenu(hashing);
}