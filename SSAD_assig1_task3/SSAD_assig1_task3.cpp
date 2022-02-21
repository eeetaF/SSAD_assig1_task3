// 21.02.2022 | Gubaidullin Marat | B21-02 | SSAD, Assignment 1, Task 3.
/*
* Return the head of a linked list after swapping every two adjacent nodes.
* You must solve the problem without changing the values in the nodes of the list (i.e., only nodes themselves may be changed.)
*
* Sample 
* Input: head = 1 2 3 4
* Output: 2 1 4 3
*
* Note:  input.txt contains array as shown in the sample above. Read and write, compute and write your result to output.txt .
*/
#include <iostream>
#include <fstream>
#include <string>

std::string reverse_string(std::string s) {
	std::string result;
	
	// from the end to beggining of s
	for (int i = size(s) - 1; i >= 0; i--)
		result += s[i];
	return result;
}

class LinkedList {
	struct Node {
		int data;
		Node* next;
	};
private:
	Node* head;
	int currentsize;
public:
	// constructor
	LinkedList() {
		head = NULL;
		currentsize = 0;
	}
	// desctructor
	~LinkedList() {
		Node* next = head;
		while (next) {
			Node* currentNode = next;
			next = next->next;
			delete currentNode;
		}
	}
	
	void add(int currentdata) {
		Node* newNode = new Node();
		newNode->data = currentdata;
		newNode->next = head;
		head = newNode;
		currentsize++;
	}

	// no exception handling, make sure to pass index i iff node with index i+1 exists
	void swap_with_the_next_node(int index) { 
		Node* currentNode = head;

		// i steps are required to reach the node with index = (index + 1)
		int i = currentsize - index - 2;

		// additional node
		Node* hNode; 

		// in case if 0 steps are required, then the node with index = (index + 1) is the head 
		// and there is no need to connect the previous node to the current node
		if (i == 0) {			  
			hNode = currentNode->next;
			currentNode->next = hNode->next;
			hNode->next = currentNode;
			head = hNode;
		}

		// in case if >0 steps are required, then the node with index = (index + 1) is not the head and it is
		// necessary to link it with the previous node, so we need to reach the node with index = (index + 2)
		else {
			i--; 
			while (i--)
				currentNode = currentNode->next;
			hNode = currentNode->next->next;
			currentNode->next->next = hNode->next;
			hNode->next = currentNode->next;
			currentNode->next = hNode;
		}
	}
	
	// get all elements of the list in the right order 
	std::string get_list() {

		// in case if list is empty
		if (currentsize == 0)
			return "";

		// additional Node for collecting data
		Node* next = head;

		// s contains elements in the wrong order
		std::string s = std::to_string(next->data);

		while (next->next) {
			next = next->next;
			s += " " + std::to_string(next->data);
		}

		// reversing string to organize it
		s = reverse_string(s);

		// returning the result
		return s;
	}

	// size getter
	int get_size() {
		return currentsize;
	}
};

std:: string solution(LinkedList* LL) {
	// for every second node (0, 2, 4...) swap it with the next one
	for (int i = 0; i < LL->get_size() - 1; i += 2)
		LL->swap_with_the_next_node(i);
	return LL->get_list();
}

int main() {
	std::string s; // string for collecting data from input
	std::ifstream inp("input.txt"); // "head = 1 2 3 4 5 6 7 8"
	std::ofstream out("output.txt"); // "2 1 4 3 6 5 8 7"
	LinkedList* LL = new LinkedList();

	// skipping useless data "head = "
	getline(inp, s, ' ');
	getline(inp, s, ' ');		

	// adding elements to a linked list (seperated by space)
	while (getline(inp, s, ' '))
		LL->add(stoi(s)); 

	// printing result to output.txt
	out << solution(LL); 

	// garbage collecting
	inp.close();
	out.close();
	delete LL;
	return 0;
}