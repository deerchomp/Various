//Homework 2

/*
Program Specification:
1. Read data for names and weights for 15 people.
2. Your program will build a list for the data maintained in ascending order based on both name and weight via a doubly linked list. 
3. This dll will use one pointer to keep weights in sorted order, and use the other link to keep names on sorted order. 
4. You need to build the list as you go maintaining this ordering, so at any time a print method was called it would print the 
related field in order. (This means nodes are added to the list in sorted order, elements are not added to the list followed by a 
sort called on the list.)
*/

/*
Brendon Linthurst 659223
CS41
*/

#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
	Node(float data, string userName, Node *pNext = NULL, Node *pPrev = NULL)
	{
		weight = data;
		name = userName;
		next = pNext;
		prev = pPrev;
	}

private:
	float weight;
	string name;
	Node *next; //Name link
	Node *prev; //Weight link 

friend class List;
};

class List
{
public:
	List(){head = tail = 0;}
	void sortedInsert(float, string);
	void printAscendingName();
	void printAscendingWeight();

private:
	Node* head;
	Node* tail;
};

void List::printAscendingName()
{
	cout << "=======Name Ascending=======" << endl;
	//Iterate from the head to ascend names using next ptr.
	for(Node *tmp = head; tmp != NULL; tmp = tmp->next)
		cout << tmp->name << " - " << tmp->weight << endl;
	cout << endl;
}

void List::printAscendingWeight()
{
	cout << "=======Weight Ascending=======" << endl;
	//Iterate backwards from the tail to ascend weights using prev ptr.
	for(Node *tmp = tail; tmp != NULL; tmp = tmp->prev)
		cout << tmp->name << " - " << tmp->weight << endl;
	cout << endl;
}
void List::sortedInsert(float data, string name)
{
	Node* newNode = new Node(data, name);
	Node* tmp = head;
	Node* pred = NULL; //Predecessor/second temp node
	
	if(head == NULL)
	{
		head = tail = newNode;
		return;
	}

	while(tmp->next != NULL && tmp->name < name)
	{
		pred = tmp;
		tmp = tmp->next;
	}

	if(head == tmp)
	{
		if(tmp->name > name)
		{
			newNode->next = head;
			head = newNode;
		}
		else
		{
			head->next = newNode;
		}
	}
	else
		if(tmp->name < name)
		{
			tmp->next = newNode;
		}

		else
		{
			newNode->next = tmp;
			pred->next = newNode;
		}

	//Work the algorithm backwards using prev ptr to link weights
	//beginning at the tail of the list.

	tmp = tail;
	
	while(tmp->prev != NULL && tmp->weight <= data)
	{
		pred = tmp;
		tmp = tmp->prev;
	}
	
	if(tail == tmp)
	{
		if(tmp->weight > data)
		{
			newNode->prev = tail;
			tail = newNode;
		}
		else
		{
			tail->prev = newNode;
		}
	}
	else
		if(tmp->weight < data)
		{
			tmp->prev = newNode;
		}
		else
		{
			newNode->prev = tmp;
			pred->prev = newNode;
		}
}

void printOptions()
{
	cout << "\nPlease enter a choice below: " << endl
		<< "1. Add members\n2. Print sorted by name" << endl
		<< "3. Print sorted by weight\n4. Exit" << endl << endl;
}

int main()
{
	List *L = new List;
	int choice = 0;
	float weight = 0;
	string name;
	bool falseToExit = true;
	cout << "* * * Fitness Database * * *" << endl << endl;
	printOptions();
	cin >> choice;
	do {
		switch(choice)
		{
		case 1:
			cout << "\nEnter -999 in any field to exit data entry." << endl;

			while(true)
			{
				cin.ignore();
				cout << endl << "Name: ";
				getline(cin, name);
				if(name == "-999")
					break;
				cout << "Weight: ";
				cin >> weight;
				if(weight == -999)
					break;
				L->sortedInsert(weight, name);
			}

			printOptions();
			cin >> choice;
			break;

		case 2:
			L->printAscendingName();
			printOptions();
			cin >> choice;
			break;

		case 3:
			L->printAscendingWeight();
			printOptions();
			cin >> choice;
			break;

		case 4:
			cout << "Goodbye!" << endl;
			falseToExit = false;
			break;

		default:
			cout << "Unrecognized input! Try again: ";
			cin >> choice;
		}
	} while(falseToExit);

	cout << endl;
	return 0;
}

/*

OUTPUT
=======Name Ascending=======
Abe - 175
Dexter - 155
Finn the Human - 120
Jake the Dog - 68
Michael - 170
Steve - 200
Tom - 150
Walter - 191.5

=======Weight Ascending=======
Jake the Dog - 68
Finn the Human - 120
Tom - 150
Dexter - 155
Michael - 170
Abe - 175
Walter - 191.5
Steve - 200

*/