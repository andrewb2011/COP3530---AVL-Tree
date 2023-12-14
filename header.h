#include <iostream>
#include <queue>
using namespace std;

class AVLtree {
private:

    int numberNodes;

public:

    class Student {
    public:

        int GatorID;
        string studentName;
        Student* left;
        Student* right;
        Student(string& name, int& id);

    };

    /* ==================== class functionality ==================== */  
    Student* rootNode;
    
    
    /* ==================== CONSTRUCTOR ==================== */
    AVLtree();

    /* ==================== OPERATORS ======================= */
    void insert(string& name, int& id);  //return true if successfull, false if unsuccessful
    void remove(int& id);  //return true if successfull, false if unsuccessful
    Student* removeRecursive(Student* root, int& id);
    void search(int& id);
    void search(string& name);
    Student* searchRecursive(Student* root, int& id);
    Student* searchInorderSuccessor(Student* root);
    void searchNameRecursive(Student* root, string& name, queue<Student*>& q);
    void printInorder(Student* root);           
    void printInorderRecursive(Student* root, queue<Student*>& q);
    void printPreorder(Student* root);          
    void printPreorderRecursive(Student* root, queue<Student*>&q);  // not done
    void printPostorder(Student* root);         
    void printPostorderRecursive(Student* root, queue<Student*>& q); // not done
    void printLevelCount(Student* root);        
    void removeInorder(int n);
    bool insertRecursive(Student*& root, Student* newstudent);
    int getNumberNodes();
    void printStudents(queue<Student*>& q);

    int height(Student* root);                  

    int heightDifference(Student* root);

    /* ==================== ROTATIONS ==================== */

    // these implementations are same as stepik questions
    Student* leftRotation(Student* student);
    Student* rightRotation(Student* student);
    Student* leftRightRotation(Student* student);
    Student* rightLeftRotation(Student* student);

        

        // maybe change paramaters to a root node or something like that and change return type
        // use Depth first search to balance tree

        // Maybe use another insert function for recursion in first insert function
        

};

