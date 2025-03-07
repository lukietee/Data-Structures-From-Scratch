#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct treeNode
{
    string myId;
    treeNode* left;
    treeNode* right;

    treeNode(string, treeNode*, treeNode*);
};

treeNode::treeNode(string tempId, treeNode* tempLeft, treeNode* tempRight)
{
    myId = tempId;
    left = tempLeft;
    right = tempRight;
}

typedef treeNode* treePtr;

struct treeType
{
    treePtr root;
};

void loadFile(treeType&, string);
void insert(treeType&, string);
treeNode* insertHelper(treeType&, treeNode*, string);
int countNodes(treeType&);
int countNodesHelper(treeType&, treeNode*);
treeNode* find(treeType&, string);
treeNode* findHelper(treeType&, treeNode*, string);
void testFind(treeType&);
treeNode* deleteHelper(treeType&, treeNode*, string);
treeNode* deleteTargetNode(treeType&, treeNode*);
void deleteNode(treeType&, string);
void testDelete(treeType&);
void printInOrder(treeType&);
void printInOrderHelper(treeType&, treeNode*);
void printPreorder(treeType&);
void printPreorderHelper(treeType&, treeNode*);
void printPostorder(treeType&);
void printPostorderHelper(treeType&, treeNode*);
int countLeaves(treeType&);
int countLeavesHelper(treeType&, treeNode*);
int height(treeType&);
int heightHelper(treeType&, treeNode*);
int max(int, int);
int width(treeType&);
int widthHelper(treeType&, treeNode*);
void printLevel(treeType&);
void printLevelHelper(treeType&, treeNode*);
void mainMenu(treeType&);
void clearTree(treeType&);

void loadFile(treeType& tree, string fileName)
{
    ifstream reader(fileName);
    string id;

    while (reader >> id)
    {
        insert(tree, id);
    }

    reader.close();
}

void insert(treeType& tree, string id)
{
    tree.root = insertHelper(tree, tree.root, id);
}

treeNode* insertHelper(treeType& tree, treeNode* node, string id)
{
    // EMPTY TREE
    if (node == nullptr)
    {
        treeNode* newNode = new treeNode(id, nullptr, nullptr);
        return newNode;
    }

    // TO THE LEFT (LESS THAN)
    else if (id.compare(node->myId) < 0)
    {
        // INSERT NODE LESS THAN
        node->left = insertHelper(tree, node->left, id);
    }

    // TO THE RIGHT (GREATER THAN)
    else
    {
        // INSERT NODE GREATER THAN
        node->right = insertHelper(tree, node->right, id);
    }

    return node;
}




int countNodes(treeType& tree)
{
    return countNodesHelper(tree, tree.root);
}

int countNodesHelper(treeType& tree, treeNode* root)
{
    if (root == nullptr)
    {
        return 0;
    }


    return 1 + countNodesHelper(tree, root->left) + countNodesHelper(tree, root->right);
}



treeNode* find(treeType& tree, string id)
{
    return findHelper(tree, tree.root, id);
}

treeNode* findHelper(treeType& tree, treeNode* root, string id)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    else if (id.compare(root->myId) < 0)
    {
        return findHelper(tree, root->left, id);
    }

    else if (id.compare(root->myId) > 0)
    {
        return findHelper(tree, root->right, id);
    }

    else
    {
        return root;
    }
}

void testFind(treeType& tree)
{
    string idToFind;
    treeNode* location;

    cout << "Testing search algorithm\n";
    cout << "Enter Id value to search for (-1 to quit) --> ";
    cin >> idToFind;

    while (!(idToFind == "-1"))
    {
        location = find(tree, idToFind);

        if (location == nullptr)
        {
            cout << "Id = " << idToFind << " No such part in stock\n";
        }

        else
        {
            cout << "Id = " << location->myId << " found in tree.\n";
        }

        cout << "\n";
        cout << "Enter Id value to search for (-1 to quit) --> ";
        cin >> idToFind;
    }
}

void deleteNode(treeType& tree, string id)
{
    tree.root = deleteHelper(tree, tree.root, id);
}

treeNode* deleteHelper(treeType& tree, treeNode* node, string id)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    else if (id == node->myId)
    {
        return deleteTargetNode(tree, node);
    }

    else if (id.compare(node->myId) < 0)
    {
        node->left = deleteHelper(tree, node->left, id);
        return node;
    }

    else
    {
        node->right = deleteHelper(tree, node->right, id);
        return node;
    }
}

treeNode* deleteTargetNode(treeType& tree, treeNode* target)
{
    if (target->left == nullptr)
    {
        return target->right;
    }

    else if (target->right == nullptr)
    {
        return target->left;
    }

    else if (target->right->left == nullptr)
    {
        target->myId = target->right->myId;
        target->right = target->right->right;
        return target;
    }

    else
    {
        //left child has right child
        treePtr marker = target->right;

        while (marker->left->left != nullptr)
        {
            marker = marker->left;
        }

        target->myId = marker->left->myId;
        marker->left = marker->left->right;
        return target;
    }
}

void testDelete(treeType& tree)
{
    string idToDelete;

    cout << "Testing delete algorithm\n";
    cout << "Enter Id value to delete (-1 to quit) --> ";
    cin >> idToDelete;

    while (!(idToDelete == "-1"))
    {
        if (find(tree, idToDelete) == nullptr)
        {
            cout << "Id = " << idToDelete << " does not exist.\n";
        }

        else
        {
            deleteNode(tree, idToDelete);
            cout << idToDelete << " was deleted.";
        }

        cout << "\n";
        cout << "Enter Id value to delete (-1 to quit) --> ";
        cin >> idToDelete;
    }
}

void printInOrder(treeType& tree)
{
    printInOrderHelper(tree, tree.root);
}

void printInOrderHelper(treeType& tree, treeNode* temp)
{
    if (temp != nullptr)
    {
        printInOrderHelper(tree, temp->left);
        cout << temp->myId;
        printInOrderHelper(tree, temp->right);
    }
}

void printPreorder(treeType& tree)
{
    printPreorderHelper(tree, tree.root);
}

void printPreorderHelper(treeType& tree, treeNode* node)
{
    if (node != nullptr)
    {
        cout << node->myId;
        printPreorderHelper(tree, node->left);
        printPreorderHelper(tree, node->right);
    }
}

void printPostorder(treeType& tree)
{
    printPostorderHelper(tree, tree.root);
}

void printPostorderHelper(treeType& tree, treeNode* node)
{
    if (node != nullptr)
    {
        printPostorderHelper(tree, node->left);
        printPostorderHelper(tree, node->right);
        cout << node->myId;
    }
}

int countLeaves(treeType& tree)
{
    return countLeavesHelper(tree, tree.root);
}

int countLeavesHelper(treeType& tree, treeNode* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    else if (node->right == nullptr && node->left == nullptr)
    {
        return 1;
    }

    else
    {
        return countLeavesHelper(tree, node->left) + countLeavesHelper(tree, node->right);
    }
}

int height(treeType& tree)
{
    return heightHelper(tree, tree.root);
}

int heightHelper(treeType& tree, treeNode* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return 1 + max(heightHelper(tree, node->left), heightHelper(tree, node->right));
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else if (a < b)
    {
        return b;
    }

    else
    {
        return a;
    }
}

int width(treeType& tree)
{
    return widthHelper(tree, tree.root);
}

int widthHelper(treeType& tree, treeNode* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    int rootWidth = 1 + heightHelper(tree, node->left) + heightHelper(tree, node->right);
    int rightWidth;
    int leftWidth;

    rightWidth = widthHelper(tree, node->right);
    leftWidth = widthHelper(tree, node->left);

    return max(max(rightWidth, leftWidth), rootWidth);
}

void clearTree(treeType& tree)
{
    tree.root = nullptr;
}

void printLevel(treeType& tree)
{
    if (tree.root != nullptr)
    {
        printLevelHelper(tree, tree.root);
    }

    else
    {
        cout << "\n";
    }
}

void printLevelHelper(treeType& tree, treeNode* node)
{
    if (node != nullptr)
    {
        queue <treeNode*> queueTEA;
        queueTEA.push(node);

        while (!queueTEA.empty())
        {
            treeNode* temp = queueTEA.front();
            queueTEA.pop();

            if (temp->left != nullptr)
            {
                queueTEA.push(temp->left);
            }

            if (temp->right != nullptr)
            {
                queueTEA.push(temp->right);
            }

            cout << temp->myId;
        }
    }
}


void mainMenu(treeType& tree)
{
    char choice;

    do
    {
        cout << "BinarySearchTree Menu\n";
        cout << "(A) Read a file from disk\n";
        cout << "(B) Preorder output\n";
        cout << "(C) Inorder output\n";
        cout << "(D) Postorder output\n";
        cout << "(E) Count the nodes in the tree\n";
        cout << "(F) Count the leaves in the tree\n";
        cout << "(G) Find the height of the tree\n";
        cout << "(H) Find the width of the tree\n";
        cout << "(I) Clear the tree\n";
        cout << "(J) Print By Level\n";
        cout << "(Q) Quit\n";
        cout << "Choice ---> ";
        cin >> choice;

        switch (choice)
        {
        case 'A':
            loadFile(tree, "fileB.txt");
            cout << "File has been loaded\n";
            cout << "\n";
            break;
        case 'B':
            cout << "The list printed preorder\n";
            printPreorder(tree);
            cout << "\n";
            break;
        case 'C':
            cout << "The list printed inorder\n";
            printInOrder(tree);
            cout << "\n";
            break;
        case 'D':
            cout << "The list printed postorder\n";
            printPostorder(tree);
            cout << "\n";
            break;
        case 'E':
            cout << "Number of nodes: " << countNodes(tree) << "\n";
            cout << "\n";
            break;
        case 'F':
            cout << "Number of leaves: " << countLeaves(tree) << "\n";
            cout << "\n";
            break;
        case 'G':
            cout << "Height: " << height(tree) << "\n";
            cout << "\n";
            break;
        case 'H':
            cout << "Width: " << width(tree) << "\n";
            cout << "\n";
            break;
        case 'I':
            cout << "Tree cleared.\n";
            clearTree(tree);
            cout << "\n";
            break;
        case 'J':
            printLevel(tree);
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
    treeType tree;

    tree.root = nullptr;

    mainMenu(tree);
}