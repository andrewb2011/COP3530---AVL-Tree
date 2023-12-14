
#include <iostream>
#include <string>
#include "header.h"
using namespace std;

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

bool isNameCorrect(string& name);
bool isIDCorrect(string& number);


int main(){

	int numberOfCommands;
	//cout << "Please enter the number of commands you would like to do." << endl;
	cin >> numberOfCommands;
	cin.ignore();

	AVLtree avlTree;

	for (int i = 0; i < numberOfCommands; i++) {
		//cout << endl;
		//cout << "Please enter a command." << endl;
		string command;
		cin >> command;
		cin.ignore();
		string studentName;			// input for student name
		string gatorID;				// input for gatorID
		int gatorIDCorrect;			// used to change about string to int if correct parsing

		if (command == "insert") {
					
			// Get input of Students name and see if input is valid.
			//cout << "Insert name of student." << endl;
			
			cin >> studentName;
            //getline(cin, studentName);
            cin.ignore();
            //cout << "You typed in " << studentName << endl;
			bool goodName = isNameCorrect(studentName);
			
			// if student name is not valid, return to beginning of loop
			if (goodName == false) {
				cout << "unsuccessful" << endl;		// did have << endl; at end
				continue;
			}
			
			// takes off quotations of input to use in tree
			studentName = studentName.substr(1, studentName.length() - 2);
			
			
			// input for student's GatorID
			//cout << "Insert the student's GatorID." << endl;
			cin >> gatorID;

			// Checks to see if inputed number is valid
			bool goodNumber = isIDCorrect(gatorID);

			// if number is not valid, return to beginning of loop
			if (goodNumber == false) {
				cout << "unsuccessful" << endl;		// did have << endl; at end
				continue;
			}
			
			// changes inputed gatorID into an integer for tree insertion
			
			gatorIDCorrect = stoi(gatorID);

			
			// if both inputs are correct, insert new student into tree
			// MAYBE REFRACTOR THIS USING BOOL COMPARISION AND INSERT IF BOTH ARE TRUE
			// OTHERWISE SKIP TO BEGINNING OF LOOP
			avlTree.insert(studentName, gatorIDCorrect);

		}

		else if (command == "remove") {
			// needs to implement, if input type is string, remove(string)
			// if input type is integer, remove(int);
			// maybe use previously used functions

			//cout << "Name or GatorId of student you want to remove" << endl;
			
			string studentID;
			cin >> studentID;

			bool goodNumber = isIDCorrect(studentID);

			if (!goodNumber) {
				cout << "unsuccessful" << endl;
				continue;
			}

			gatorIDCorrect = stoi(studentID);

			avlTree.remove(gatorIDCorrect);

		}

		else if (command == "search") {
			// implement to type() of imput to see if name or GatorID
			
			//cout << "Insert name or ID or student." << endl;

			// take user input for search parameter
			string userInput;
			getline(cin, userInput);

			// checks to see in inputed is either a correct integer or string
			bool goodNumber = isIDCorrect(userInput);
			bool goodName = isNameCorrect(userInput);

			if (goodNumber) {
				gatorIDCorrect = stoi(userInput);
				avlTree.search(gatorIDCorrect);
			}

			else if (goodName){
				userInput = userInput.substr(1, userInput.length() - 2);
				avlTree.search(userInput);
			}

		}

		else if (command == "printInorder") {
			
			avlTree.printInorder(avlTree.rootNode);
			//cout << endl;
		}
		
		else if (command == "printPreorder") {
			
			avlTree.printPreorder(avlTree.rootNode);
			//cout << endl;
		}

		else if (command == "printPostorder") {
			
			avlTree.printPostorder(avlTree.rootNode);
			//cout << endl;
		}

		else if (command == "printLevelCount") {
			
			avlTree.printLevelCount(avlTree.rootNode);

		}

		else if (command == "removeInorder") {
			
			//cout << "Enter the index of the Inorder traversed list to remove" << endl;
			int index;
			cin >> index;

			avlTree.removeInorder(index);

		}

		else {
			cout << "unsuccessful" << endl;
		}

		


	}
	cout << endl;
	return 0;
}

// 
bool isNameCorrect(string& name) {
    //checks if input is surrounded by quotations
    
    if (name.front() == '"' && name.back() == '"') {

        // checks each character to see if its a letter or a space
        for (int i = 1; i < name.length() - 1; i++) {

            // if not then return false. invalid string
            if (!isalpha(name[i]) && name[i] != ' ') {			// https://cplusplus.com/reference/cctype/isalpha/
                return false;
            }
        }
        return true;

    }
    return false;
    
}

bool isIDCorrect(string& number) {
    if (number.length() == 8) {
        for (int i = 0; i < number.length(); i++) {
            if (!isdigit(number[i])) {				// https://cplusplus.com/reference/cctype/isdigit/
                return false;
            }
        }
        return true;
    }

    return false;
}
