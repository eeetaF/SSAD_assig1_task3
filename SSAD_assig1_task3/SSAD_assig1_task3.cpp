#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string reverse_string(string s) {
	string res;
	for (int i = size(s) - 1; i >= 0; i--)
		res += s[i];
	return res;
}

class LinkedList {
	struct Node {
		int data;
		Node* next;
	};
public:
	LinkedList() {
		head = NULL;
		currentsize = 0;
	}
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
	void swap_with_the_next_node(int index) { // no exception handling, make sure to pass index i iff node with index i+1 exists
		Node* currentNode = head;
		int i = currentsize - index - 2; // i steps are required to reach the node with index = (index + 1)
		Node* hNode; // additional node

		if (i == 0) { // in case if 0 steps are required, then the node with index = (index + 1) is the head and there is no
						  // need to connect the previous node to the current node
			hNode = currentNode->next;
			currentNode->next = hNode->next;
			hNode->next = currentNode;
			head = hNode;
		}
		else {
			i--; // in case if >0 steps are required, then the node with index = (index + 1) is not the head and it is
				 // necessary to link it with the previous node, so we need to reach the node with index = (index + 2)
			while (i--)
				currentNode = currentNode->next;
			hNode = currentNode->next->next;
			currentNode->next->next = hNode->next;
			hNode->next = currentNode->next;
			currentNode->next = hNode;
		}
	}
	string get_list() {
		string s;
		Node* next = head;
		while (next) {
			s += to_string(next->data) + ",";
			next = next->next;
		}
		
		s.pop_back();
		s = reverse_string(s);
		return "[" + s + "]";
	}
private:
	Node* head;
	int currentsize;
};

string solution(LinkedList* LL, int& n) {
	for (int i = 0; i < n - 1; i += 2)
		LL->swap_with_the_next_node(i);
	
	return LL->get_list();
}

int main() {
	string bins; // string for collecting useless data from input
	ifstream inp("input.txt"); // "head = [1,2,3,4,5,6,7,8]"
	ofstream out("output.txt"); // "[2,1,4,3,6,5,8,7]"
	int numberOfElements = 0; // number of elements in linked list
	LinkedList* LL = new LinkedList();

	getline(inp, bins, '['); // useless data "head = ["
	while (getline(inp, bins, ','))
		numberOfElements++; // counting number of elements using separation by comma
	inp.close();
	inp.open("input.txt"); // open file again to read elements

	string* arr = new string[numberOfElements];

	
	getline(inp, bins, '[');
	for (int i = 0; i < numberOfElements - 1; i++)
		getline(inp, arr[i], ',');
	getline(inp, arr[numberOfElements - 1], ']');

	for (int i = 0; i < numberOfElements; i++)
		LL->add(stoi(arr[i]));

	out << solution(LL, numberOfElements);
	inp.close();
	out.close();
	delete[] arr;
	return 0;
}