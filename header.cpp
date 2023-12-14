#include "header.h"
#include <iostream>
#include <queue>
using namespace std;


AVLtree::Student::Student(string& name, int& id) {
    studentName = name;
    GatorID = id;
    left = nullptr;
    right = nullptr;

}

AVLtree::AVLtree() {
    rootNode = nullptr;
    numberNodes = 0;
    
}


bool AVLtree::insertRecursive(Student*& root, Student* newstudent) {
    // this resursively goes to place new student. Also calls helper functions to self-balance

    if (root == nullptr) {
        root = newstudent;
        return true;
    }

    if (newstudent->GatorID < root->GatorID) {
        if (!insertRecursive(root->left, newstudent))
            return false;
    } else if (newstudent->GatorID > root->GatorID) {
        if (!insertRecursive(root->right, newstudent))
            return false;
    } else {
        // Duplicate GatorID, not allowed
        return false;
    }

    // Perform rotations if necessary
    int balance = heightDifference(root);

    if (balance > 1) {
        if (newstudent->GatorID < root->left->GatorID) {
            // this is used for left-left rotations
            root = rightRotation(root);
        } else {
            // This is used for left-right rotations
            root = leftRightRotation(root);
        }
    } else if (balance < -1) {
        if (newstudent->GatorID > root->right->GatorID) {
            // This is used for right-right rotations
            root = leftRotation(root);
        } else {
            // This is used for right-left rotations
            root = rightLeftRotation(root);
        }
    }

    return true;
}

void AVLtree::insert(string& name, int& id) {

    // makes new Student Node with parameter information. If insertion was successful, yay!
    Student* newStudent = new Student(name, id);
    if (insertRecursive(rootNode, newStudent)) {
        numberNodes++;
        cout << "successful" << endl;           // did have << endl; at end
    } else {
        cout << "unsuccessful" << endl;         // did have << endl; at end
    }
}

void AVLtree::remove(int& id) {
    // uses secondary functions to remove nodes using recursion.

    rootNode = removeRecursive(rootNode, id);

}

AVLtree::Student* AVLtree::removeRecursive(Student* root, int& id) {
    // base case
    if (root == nullptr) {
        cout << "unsuccessful" << endl;         // did have << endl; at end
        return nullptr;
    }

    // recursively search through the tree to find node
    if (id > root->GatorID)
        root->right = removeRecursive(root->right, id);

    else if (id < root->GatorID)
        root->left = removeRecursive(root->left, id);

    else {  // if root->gatorID == id, this statement executes

        // if left child = nullptr, replace with right child
        if (root->left == nullptr) {
            Student* tempNode = root->right;
            delete root;
            cout << "successful" << endl;               // did have << endl; at end
            numberNodes--;
            return tempNode; // this returns the new node to previous level(deleted node)

        }

        // if right child = nullptr, replace with left child
        else if (root->right == nullptr) {
            Student* tempNode = root->left;
            delete root;
            cout << "successful" << endl;               // did have << endl; at end
            numberNodes--;
            return tempNode;
        }

        else if (root->left != nullptr && root->right != nullptr) {
            // if node to-be-deleted has 2 children, use smallest node in right subtree to replace node
            
            // use this function finds inorder successor in right subtree
            Student* tempNode = searchInorderSuccessor(root->right);

            // update data of new node. 
            root->GatorID = tempNode->GatorID;
            root->studentName = tempNode->studentName;

            // remove inorder successor from original spot.
            root->right = removeRecursive(root->right, tempNode->GatorID);

        }
        
    }
    // if still have time, balance the tree here.
    
}

void AVLtree::search(int& id) {

    if (rootNode == nullptr) {
        cout << "unsuccessful" << endl;                 // did have << endl; at end
        return;
    }

    Student* copyStudent = searchRecursive(rootNode, id);

    if (copyStudent == nullptr)
        cout << "unsuccessful" << endl;                 // did have << endl; at end

    else 
        cout << copyStudent->studentName << endl;          // did have << endl; at end

}

void AVLtree::search(string& name) {
    // this is if the tree's rootnode is null. not implemented yet
    if (rootNode == nullptr) {
        cout << "unsuccessful" << endl;                 // did have << endl; at end
        return;
    }

    queue<Student*> q;        // using queue in case there are more than one student with the same name
    searchNameRecursive(rootNode, name, q);

    if (q.empty())
        cout << "unsuccessful" << endl;                 // did have << endl; at end
    else {
        while (!q.empty()) {
            cout << q.front()->GatorID << endl;           // did have << endl; at end
            q.pop();
        }
    }

}

AVLtree::Student* AVLtree::searchRecursive(Student* root, int& id) {
    // base case if no node with ID in tree
    if (root == nullptr)
        return nullptr;

    if (id == root->GatorID)
        return root;
                                        // these 2 recursively call same function to find student id
    if (id < root->GatorID) {
        return searchRecursive(root->left, id);
    }
    if (id > root->GatorID) {
        return searchRecursive(root->right, id);
    }

}

AVLtree::Student* AVLtree::searchInorderSuccessor(Student* root) {
    // the inorder successor of a node is the leftmost node in the nodes right subtree.
    // the parameter is the node to be deleted's right child.

    while (root->left != nullptr) 
        root = root->left;
    
    return root;

}

void AVLtree::searchNameRecursive(Student* root, string& name, queue<Student*>& q) {

    // base case. If there is no student with given name in tree
    if (root == nullptr) {
        return;
    }

    // if student's name is given name, add name to q. there can be more than one
    if (root->studentName == name) 
        q.push(root);

    // this uses this function recursively using pre-order traversal
    searchNameRecursive(root->left, name, q);
    searchNameRecursive(root->right, name, q);
}

void AVLtree::printInorder(Student* root) {
    
    queue<Student*> studentq;
    printInorderRecursive(root, studentq);

    printStudents(studentq);

}

void AVLtree::printInorderRecursive(Student* root, queue<Student*>& q) {

    if (root == nullptr) 
        return;;

    printInorderRecursive(root->left, q);       // left child
    q.push(root);                               // root
    printInorderRecursive(root->right, q);      // right child
}

void AVLtree::printPreorder(Student* root) {
    // recursive calls to print student names using Preorder traversal (Node, Left, Right)

    queue<Student*> studentq;
    printPreorderRecursive(root, studentq);

    printStudents(studentq);

}

void AVLtree::printPreorderRecursive(Student* root, queue<Student*>& q) {

    if (root == nullptr) 
        return;

    q.push(root);                               // root
    printPreorderRecursive(root->left, q);      // left child
    printPreorderRecursive(root->right, q);     // right child

}

void AVLtree::printPostorder(Student* root) {
    // recursive calls to print student names using Postorder traversal (Left, Right, Node)

    queue<Student*> studentq;
    printPostorderRecursive(root, studentq);

    printStudents(studentq);
}

void AVLtree::printPostorderRecursive(Student* root, queue<Student*>& q) {

    if (root == nullptr)
        return;

    printPostorderRecursive(root->left, q);     // left child
    printPostorderRecursive(root->right, q);    // right child
    q.push(root);                               // root

}

void AVLtree::printStudents(queue<Student*>& q) {

    while (!q.empty()) {
        cout << q.front()->studentName;
        q.pop();

        if (!q.empty())     // prints names in queue seperated by comma, except last
            cout << ", ";
    }
    cout << endl;
} 

void AVLtree::printLevelCount(Student* root) {
    
    if (root == nullptr) {
        cout << "0";
        return;
    }

    int treeLevel = height(root);    // finds farthest route in tree
    cout << treeLevel << endl;                      // did have << endl; at end
        

}

void AVLtree::removeInorder(int n) {
    // removes the Nth GatorID from the inorder traversal of the tree (N = 0 for the first item)
    queue<Student*> q;

    // this doesnt print, rather gathers the nodes into the queue
    printInorderRecursive(rootNode, q);

    int size = q.size();

    // if the parameter is greater than the size of the queue, then unsuccessful
    if (n >= size) {
        cout << "unsuccessful" << endl;                     // did have << endl; at end
        return;
    }

    // removes front on queue to get to the nth inorder traversed node
    while (n > 0) {
        q.pop();
        n--;
    }

    // Nth node is at the front of queue
    Student* tempNode = q.front();

    // remove the selected node in the queue from the tree. Makes adjustments also
    rootNode = removeRecursive(rootNode, tempNode->GatorID);

    numberNodes--;

}

int AVLtree::getNumberNodes() {

    // this return the number of successfully inserted nodes. For testing purposes
    return numberNodes;
}

int AVLtree::height(Student* root) {
    // implemented from stepik questions
    
    if (root == nullptr)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

int AVLtree::heightDifference(Student* root) {
    // implemented from stepik questions

    if (root == nullptr)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return leftHeight - rightHeight;

}

AVLtree::Student* AVLtree::leftRotation(Student* student) {
    // implemented from stepik questions 

    Student* grandchild = student->right->left;    // This is node x. gets moved to left side under node A
    Student* newParent = student->right;          // This saved reference to node B
    newParent->left = student;                 // root node is moved to left of new root, which is newParent
    student->right = grandchild;               // node X is now right child of node
    return newParent;
}

AVLtree::Student* AVLtree::rightRotation(Student* student) {
    // implemented from stepik questions 

    Student* grandchild = student->left->right;       // this is mirror image of rotateLeft()
    Student* newParent = student->left;
    newParent->right = student;
    student->left = grandchild;
    return newParent;
}

AVLtree::Student* AVLtree::leftRightRotation(Student* student) {
    // implemented from stepik questions 

    student->left = leftRotation(student->left);
    return rightRotation(student);
}

AVLtree::Student* AVLtree::rightLeftRotation(Student* student) {
    // implemented from stepik questions 

    student->right = rightRotation(student->right);
    return leftRotation(student);
}