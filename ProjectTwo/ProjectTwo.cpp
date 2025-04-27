// Christopher M. Biele
// 04/18/2025
// Project Two

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// Creating the course class structure to store the course information
class Course {
private:
	std::string courseNumber;
	std::string courseName;
	std::vector<std::string> prerequisites;

public:
	// Default constructor
	Course() {}

	// Constructor including the course number and name
	Course(const std::string& number, const std::string& name) {
		// Limiting string lenghts for preventing overflow errors
		courseNumber = number;
		courseName = name;
	}
	
	// Adding a prerequisite course to the course
	void addPrerequisite(const std::string& prereq) {
		prerequisites.push_back(prereq);
	}

	// Course number getter
	std::string getCourseNumber() const {
		return courseNumber;
	}
	
	// Course name getter
	std::string getCourseName() const {
		return courseName;
    }

	// Prerequisite getter
	std::vector<std::string> getPrerequisites() const {
		return prerequisites;
	}	
};

// Node structure definition for the BST
struct Node {
	Course course;
	Node* left;
	Node* right;

	// Constructor for creating a new node
	Node(const Course& c) : course(c), left(nullptr), right(nullptr) {}
};

// The magnificent BST class and implementation
class BST {
private:
	Node* root;

	// Helper for destroying nodes
	void destroy(Node* node) {
		if (node) {
			destroy(node->left);
			destroy(node->right);
			delete node;
		}
	}

	// Helper for in-order traversal
	void displayInOrder(Node* root) const {
		if (root == nullptr) {
			return;
		}

		std::vector<Node*> stack;
		Node* current = root;

		while (current != nullptr || !stack.empty()) {
			// Traverse to the leftmost node
			while (current != nullptr) {
				stack.push_back(current);
				current = current->left;
			}
			// Checking if the stack is empty
			if (!stack.empty()) {
				// Process the current node and move to the right
				current = stack.back();
				stack.pop_back();

				std::cout << current->course.getCourseNumber() << ": " << current->course.getCourseName() << std::endl;

				current = current->right;
			}
		}
	}

public:
	// Constructor
	BST() : root(nullptr) {}

	// Destructor
	~BST() {
		destroy(root);
	}
	
	// Inmerting a course into the tree
	void insert(const Course& course) {
		// New node creation
		Node* newNode = new Node(course);

		// If the tree is empty, a node will be added as the root
		if (root == nullptr) {
			root = newNode;
			return;
		}

		// Otherwise, find the correct position for the new node
		Node* current = root;
		Node* parent = nullptr;

		while (true) {
			parent = current;

			// Moving left if the course number is less than the current node's course number
			if (course.getCourseNumber() < current->course.getCourseNumber()) {
				current = current->left;

				// If we reach a leaf node, we will insert the new node here
				if (current == nullptr) {
					parent->left = newNode;
					return;
				}
			}
			// Move right if the course number is greater than the current node's course number
			else if (course.getCourseNumber() > current->course.getCourseNumber()) {
				current = current->right;

				// If we reach a leaf node, we will insert the new node here
				if (current == nullptr) {
					parent->right = newNode;
					return;
				}
			}
			else {
				// Removing duplicates, if needed
				delete newNode;
				return;
			}
		}
	}

	// Printing the courses in alphanumerical order with added error checks
	void printCourseList() const {
		if (root == nullptr) {
			std::cout << "No courses available." << std::endl;
			return;
		}

		std::cout << "Here is a sample schedule:" << std::endl;
		displayInOrder(root);
	}

	// Searching for courses by their course number
	Course* search(const std::string& courseNumber) {
		Node* current = root;

		while (current != nullptr) {
			// Returns the course if located
			if (current->course.getCourseNumber() == courseNumber) {
				return &(current->course);
			}
			// Traversing left if the course number is less than the current
			else if (courseNumber < current->course.getCourseNumber()) {
				current = current->left;
			}
			// Traversing right if the course number is greater than the current
			else {
				current = current->right;
			}
		}
		// Course not found
		return nullptr;
	}
};

// Function for loading file data into the tree with verification checks for debug
static void loadCourses(BST& bst, const std::string& filename) {
	std::ifstream file(filename);

	// Check if the file was opened successfully
	if (!file.is_open()) {
		std::cout << "Error opening file: " << filename << std::endl;
		return;
	}

	std::string line;

	// Reading the file line by line
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string token;
		std::vector<std::string> tokens;

		// Parsing comma-separated values
		while (std::getline(ss, token, ',')) {
			// Removing leading and trailing whitespace
			token.erase(0, token.find_first_not_of(" \t"));
			token.erase(token.find_last_not_of(" \t") + 1);
			tokens.push_back(token);
		}

		// Creating a course if a number and name is obtained
		if (tokens.size() >= 2) {
			Course course(tokens[0], tokens[1]);

			// Adding prerequisites if they exist
			for (size_t i = 2; i < tokens.size(); i++) {
				if (!tokens[i].empty()) {
					course.addPrerequisite(tokens[i]);
				}
			}

			// Inserting the course into the BST
			bst.insert(course);

			// Output for debugging
			std::cout << "Loaded course: " << tokens[0] << " - " << tokens[1] << std::endl;
		}
	}


	std::cout << "Data loaded successfully." << std::endl;
}

// Function to display the course information
static void printCourseInfo(BST& bst, const std::string& courseNumber) {
	Course* course = bst.search(courseNumber);

	if (course != nullptr) {
		std::cout << course->getCourseNumber() << ", " << course->getCourseName() << std::endl;
		std::cout << "Prerequisites: ";

		std::vector<std::string> prerequisites = course->getPrerequisites();
		if (prerequisites.empty()) {
			std::cout << "None" << std::endl;
		}
		else {
			for (size_t i = 0; i < prerequisites.size(); i++) {
				Course* prerequisite = bst.search(prerequisites[i]);
				if (prerequisite != nullptr) {
					std::cout << prerequisites[i] << ", " << prerequisite->getCourseName();
					if (i < prerequisites.size() - 1) {
						std::cout << std::endl << "                ";
					}
				}
				else {
					std::cout << prerequisites[i] << " (Course not found)";
					if (i < prerequisites.size() - 1) {
						std::cout << std::endl << "                ";
					}
				}
			}
			std::cout << std::endl;
		}
	}
	else {
		std::cout << "Course not found" << std::endl;
	}
}

// Main function
int main() {
	BST bst;
	bool dataLoaded = false;

	std::cout << "Welcome to the course planner." << std::endl;

	int choice = 0;
	while (choice != 9) {
		std::cout << std::endl;
		std::cout << "1. Load Data Structure" << std::endl;
		std::cout << "2. Print Course List" << std::endl;
		std::cout << "3. Print Course" << std::endl;
		std::cout << "9. Exit" << std::endl;
		std::cout << std::endl;
		std::cout << "What would you like to do? ";

		// Fetch user input
		std::string input;
		std::getline(std::cin, input);

		// Validating the input is a number
		try {
			choice = std::stoi(input);
		}
		catch (...) {
			std::cout << input << " is not a valid option." << std::endl;
			continue;
		}

		// Processing the choice
		switch (choice) {
			case 1: {
				std::cout << "Enter the file name containing the course data: ";
				std::string filename;
				std::getline(std::cin, filename);

				loadCourses(bst, filename);
				dataLoaded = true;
				break;
			}
			case 2: {
				// If the file did not load or has not been loaded yet, we will not be able to print the course list
				if (!dataLoaded) {
					std::cout << "Please load data first (option 1)." << std::endl;
					break;
				}
				
				// Printing the course list
				bst.printCourseList();
				break;
			}
			case 3: {
				// If the file did not load or has not been loaded yet, we will not be able to print the course list
				if (!dataLoaded) {
					std::cout << "Please load data first (option 1)." << std::endl;
					break;
				}
				std::cout << "What course do you want to know about? ";
				std::string courseNumber;
				std::getline(std::cin, courseNumber);

				// Converting to uppercase for consistent formatting
				std::transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

				printCourseInfo(bst, courseNumber);
				break;
			}
			case 9:
				// Exiting the program
				std::cout << "Thank you for using the course planner!" << std::endl;
				break;
			default:
				std::cout << choice << " is not a valid option." << std::endl;
				break;
			}
		}

	return 0;
}
// End of the program