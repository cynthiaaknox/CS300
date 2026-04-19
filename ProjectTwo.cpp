//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Cynthia Knox
// Version     : 1.0
// Copyright   : Copyright � 2026 SNHU COCE
// Description : Lab 7-2 ProjectTwo
//============================================================================

#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>


using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold course information
struct Course {
    string courseNumber; // unique identifier
    string courseName;
    vector<string> coursePreReq;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Project Two class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class ProjectTwo {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void destroyTree(Node* node);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string courseNumber);

public:
    ProjectTwo();
    virtual ~ProjectTwo();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    void Remove(string courseNumber);
    Course Search(string courseNumber);
};

/**
 * Default constructor
 */
ProjectTwo::ProjectTwo() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}

/**
* Deletes all nodes in tree recursively
*/
void ProjectTwo::destroyTree(Node* node) {
    if (node != nullptr) {
        //left side
        destroyTree(node->left);
        //right side
        destroyTree(node->right);
        delete node;
    }
}
/**
 * Destructor
 */
ProjectTwo::~ProjectTwo() {
    // recurse from root deleting every node
    destroyTree(root);
}

/**
 * Traverse the tree in order
 */
void ProjectTwo::InOrder() {
    // FixMe (3a): In order root
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void ProjectTwo::PostOrder() {
    // FixMe (4a): Post order root
    // postOrder root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void ProjectTwo::PreOrder() {
    // FixMe (5a): Pre order root
    // preOrder root
    preOrder(root);
}


/**
 * Insert a course
 */
void ProjectTwo::Insert(Course course) {
    // if root equal to null ptr
    if (root == nullptr) {
        // root is equal to new node course
        root = new Node(course);
    }
    // else
    else {
        // add Node root and course
        this->addNode(root, course);
    }
}

/**
 * Remove a course from the tree
 */
void ProjectTwo::Remove(string courseNumber) {
    // FIXME (7a) Implement removing a course from the tree
    // remove node root courseNumber
    root = this->removeNode(root, courseNumber);
}

/**
 * Search for a course
 */
Course ProjectTwo::Search(string courseNumber) {
    // set current node equal to root
    Node* cur = root;

    // keep looping downwards until bottom reached or matching courseNumber found
    while (cur != nullptr) {
        // if match found, return current course
        if (cur->course.courseNumber.compare(courseNumber) == 0) {
            return cur->course;
        }
        // if course is smaller than current node then traverse left
        else if (courseNumber.compare(cur->course.courseNumber) < 0) {
            cur = cur->left;
        }
        else {
            // else larger so traverse right
            cur = cur->right;
        }
    }
    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void ProjectTwo::addNode(Node* node, Course course) {
    // FIXME (6b) Implement inserting a course into the tree
    // if node is larger then add to left
    if (node != nullptr && node->course.courseNumber.compare(course.courseNumber) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
            return;
        }
        // else recurse down the left node
        else {
            this->addNode(node->left, course);
        }
    }
    // else
    else if (node != nullptr && node->course.courseNumber.compare(course.courseNumber) < 0) {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
            return;
        }
        //else
        else {
            // recurse down the right node
            this->addNode(node->right, course);
        }
    }
}
void ProjectTwo::inOrder(Node* node) {
    // FixMe (3b): Pre order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder not left
        inOrder(node->left);
        //output courseNumber, title, amount, fund
        cout << node->course.courseNumber << ", " << node->course.courseName << endl;
        //InOder right
        inOrder(node->right);
    }
}
void ProjectTwo::postOrder(Node* node) {
    // FixMe (4b): Pre order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output courseNumber, courseName, preReqs
        cout << node->course.courseNumber << " : " << node->course.courseName << " | " << endl;
    }
}

void ProjectTwo::preOrder(Node* node) {
    // FixMe (5b): Pre order root
    if (node != nullptr) {
        cout << node->course.courseNumber << " : " << node->course.courseName << " | " <<  endl;
        //preOrder left
        preOrder(node->left);
        //preOrder right
        preOrder(node->right);
        //output courseNumber, title, amount, fund
    }
}

/**
 * Remove a course from some node (recursive)
 */
Node* ProjectTwo::removeNode(Node* node, string courseNumber) {
    // FIXME (7b) Implement removing a course from the tree
    // if node = nullptr return node
    if (node == nullptr) {
        return node;
    }
    else if (courseNumber.compare(node->course.courseNumber) < 0) {
        node->left = removeNode(node->left, courseNumber);
        // (otherwise recurse down the right subtree)
    }
    else if (courseNumber.compare(node->course.courseNumber) > 0) {
        node->right = removeNode(node->right, courseNumber);
    }
    else {
        // if left node = nullptr && right node = nullptr delete node 
        if (node->left == nullptr && node->right == nullptr) {
            //leaf node
            delete node;
            node = nullptr;
            // (otherwise check one child to the left)
            // if left node != nullptr && right node = nullptr delete node 
        }
        else if (node->left != nullptr && node->right == nullptr) {
            Node* tmp = node;
            node = node->left;
            delete tmp;
            tmp = nullptr;
            // (otherwise check one child to the right)
            // if left node = nullptr && right node != nullptr delete node
        }
        else if (node->right != nullptr && node->left == nullptr) {
            Node* tmp = node;
            node = node->right;
            delete tmp;
            tmp = nullptr;
        }
        // (otherwise more than one child so find the minimum)
        else {
            //find the min of the right subtree nodes for bst
            // create temp node to right
            Node* tmp = node->right;
            // while left node is not nullptr keep moving temp left
            while (tmp->left != nullptr) {
                // make node course (right) equal to temp course (left)
                tmp = tmp->left;
            }
            node->course = tmp->course;
            // remove right node using recursive call
            node->right = removeNode(node->right, tmp->course.courseNumber);
        }
    }
    return node;
}



//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    cout << course.courseNumber << ", " << course.courseName << endl;
    // print prerequisites if any
    if (!course.coursePreReq.empty()) {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.coursePreReq.size(); ++i) {
            cout << course.coursePreReq[i];
            if (i + 1 < course.coursePreReq.size()) cout << ", ";
        }
        cout << endl;
    }
    cout << endl;
    return;
}

/**
 * Load a CSV file containing courses into a binary search tree
 * container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 */
void loadCourses(string csvPath, ProjectTwo* bst) {

    cout << "Loading CSV file " << csvPath << endl;
    ifstream file;
    file.open(csvPath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << csvPath << endl;
        return;
    }

    int count;
    string row;
    string item;

    // loop to read rows of the CSV course file
    // read one line at a time
    while (getline(file, row)) {
        count = 0;
        // Create a data structure and add to the collection of courses
        Course course;
        stringstream str(row);
		//get course number and course name
        while (count <  2) {
            // read one item at a time
            getline(str, item, ',');
            if (count == 0) {
                course.courseNumber = item;
            }
            else if (count == 1) {
                course.courseName = item;
            }
            count++;
		}
        // push this course to the end
        while (getline(str, item, ',')) {
            course.coursePreReq.push_back(item);
		}
        bst->Insert(course);
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, courseNumber, fileChoice;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        courseNumber = "CSCI300";
        break;
    case 3:
        csvPath = argv[1];
        courseNumber = argv[2];
        break;
    default:
        csvPath = "CS 300 ABCU_Advising_Program_Input.csv";
        courseNumber = "CSCI300";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all courses
    ProjectTwo* bst;
    bst = new ProjectTwo();
    Course course;

    int choice = 0;
    cout << "Welcome to the course planner." << endl << endl;

    while (choice != 9) {
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl << endl;
        cout << "What would you like to do? ";
        
        string input;
        getline(cin >> ws, input);             // read full line, skip leading whitespace
        if (input.size() == 1 && isdigit((unsigned char)input[0])) {
            choice = input[0] - '0';
        } else {
            cout << "Invalid selection. Enter a single digit (e.g. 1)." << endl;
            continue; // reprompt loop
        }

        switch (choice) {

            case 1:

                // Initialize a timer variable before loading courses
                ticks = clock();
				// Prompt the user for the CSV file to load and read in the courses from that file
                cout << "Enter the filename of the CSV file to load: ";
                // use getline to allow filenames with spaces (e.g. "CS 300 ABCU_Advising_Program_Input.csv")
                getline(cin >> ws, fileChoice);
                // Complete the method call to load the courses
                loadCourses(fileChoice, bst);

                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                break;

            case 2:
				cout << "Here is a sample schedule: " << endl << endl;
                bst->InOrder();
                break;

            case 3:
                ticks = clock();
                cout << endl;
				cout << "What course do you want to know about? ";
				cin >> courseNumber;
				transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
                course = bst->Search(courseNumber);

                ticks = clock() - ticks; // current clock ticks minus starting clock ticks

                if (!course.courseNumber.empty()) {
                    displayCourse(course);
                }
                else {
                    cout << "Course Id " << courseNumber << " not found." << endl;
                }

                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                break;
            case 9:
                cout << "Thank you for using the course planner!" << endl;
				break;
            default:
		        cout << choice << " is not a valid option." << endl;
                break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
