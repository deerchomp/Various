/*
Program Specification:

Build a binary search tree, using links (not an array) for 15 records. The data in these records will hold names and their associated weights. Read the data from the screen.

Required functionality (Each # should be separate methods):
1.	Build the tree from the unique set of names (names are the key value) and their associated weights.
2.	Execute a preorder traversal
3.	Execute an inorder traversal
4.	Execute a postorder traversal
5.	Find and print the height of the tree using recursion, do not add a height variable to the tree structure, the algorithm stack should hold this.
6.	Determine the number of leaves and print the result (remember a leaf has no children).
7.	Implement search functionality that will search for a name and indicate the weight for that individual if they exist in the structure, otherwise stating no match exists.
8.	Determine the lowest weight contained in the tree.
9.	Find the first name in alphabetical order (this should not go through every node, unless the tree happens to be a linked list).

*/

/*
Brendon Linthurst
659223
CS41
*/

#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
	Node() { left = right = 0; }
	Node(string, float);

private:
	string name;
	float weight;
	Node* left;
	Node* right;

friend class BST;
};

class BST
{
public:
	Node* root;
	BST() { root = NULL; nodeCount = 0; }
	bool insertNode(string, float);
	void preOrderTraversal(Node*);
	void inOrderTraversal(Node*);
	void postOrderTraversal(Node*);
	void findMember(string);
	void printLargestName();
	int getHeight(Node*);
	int getLeafCount(Node*);
	float getLowestWeight(Node*);
	float returnLeast(float, float);
	int maxValue(int a, int b) { return (a > b ? a : b); }

private:
	int nodeCount;
	int leafCount;
};

int BST::getHeight(Node* temp)
{
	if(temp == NULL)
	{
		return -1;
	}
	else
		return maxValue(getHeight(temp->left), getHeight(temp->right)) + 1;
}

float BST::getLowestWeight(Node* temp)
{
	if(root == NULL)
	{
		return -1; //Switch(6) catches -1 and prints error message from main instead
	}
	
	if(temp->left == NULL && temp->right == NULL)
	{
		return temp->weight;
	}

	if(temp->left != NULL && temp->right == NULL)
	{
		return returnLeast(temp->weight, getLowestWeight(temp->left));
	}
	else if(temp->right != NULL && temp->left == NULL)
	{
		return returnLeast(temp->weight, getLowestWeight(temp->right));
	}
	else
		return returnLeast(getLowestWeight(temp->left), getLowestWeight(temp->right));
}

float BST::returnLeast(float a, float b)
{
	float lowest = 999999999; //Initialized to an impossible weight, just in case
	(a < b ? lowest = a : lowest = b);
	return lowest;
}


Node::Node(string info, float data)
{
	name = info;
	weight = data;
}

void BST::preOrderTraversal(Node* temp)
{
	if(root == NULL)
	{
		cout << "Error: Tree is empty!" << endl;
	}
	else
		if(temp != NULL)
		{
			cout << temp->name << " - " << temp->weight << " ";
			preOrderTraversal(temp->left);
			preOrderTraversal(temp->right);
		}

}

void BST::inOrderTraversal(Node* temp)
{
	if(root == NULL)
	{
		cout << "Error: Tree is empty!" << endl;
	}
	else
		if(temp != NULL)
		{
			inOrderTraversal(temp->left);
			cout << temp->name << " - " << temp->weight << " ";
			inOrderTraversal(temp->right);
		}
}

void BST::postOrderTraversal(Node* temp)
{
	if(root == NULL)
	{
		cout << "Error: Tree is empty!" << endl;
	}
	else
	{
		if(temp != NULL)
		{
			postOrderTraversal(temp->left);
			postOrderTraversal(temp->right);
			cout << temp->name << " - " << temp->weight << " ";
		}
	}
}

bool BST::insertNode(string name, float weight)
{
	Node* newNode = new Node(name, weight);
	if(root == NULL)
	{
		root = newNode;
		return true;
	}
	Node* temp = root;
	while(true)
	{
		if(name < temp->name)
			if(temp->left == NULL)
			{
				temp->left = newNode;
				break;
			}
			else
				temp = temp->left;
		else if(name > temp->name)
			if(temp->right == NULL)
			{
				temp->right = newNode;
				break;
			}
			else
				temp = temp->right;
		else if(name == temp->name)
		{
			cout << "Duplicate person!";
			return false;
		}
	}
}

void BST::findMember(string name)
{
	Node* temp = root;

	//Iterate through each node going left if given key is lesser
	//or right if given key is greater.
	while(temp != NULL && (name != temp->name))
	{
		if(name > temp->name)
			temp = temp->right;
		else
			temp = temp->left;
	}

	if(temp != NULL)
	{
		cout << endl << name << " weighs " << temp->weight << endl;
	}
	else
		cout << name << " was not found in the tree" << endl;
}

int BST::getLeafCount(Node* temp)
{
	if(root == NULL)
	{
		return 0;
	}
	if(temp->left == NULL && temp->right == NULL)
	{
		return 1; //Single node is also a leaf
	}
	else
	{
		if(temp->left == NULL && temp->right != NULL)
		{
			return getLeafCount(temp->right);
		}
		else	if(temp->right == NULL && temp->left != NULL)
		{
				return getLeafCount(temp->left);
		}
		else
			return getLeafCount(temp->left) + getLeafCount(temp->right);
	}
}

void BST::printLargestName()
{
	Node* temp = root;
	Node* pred = root;
	if(root == NULL)
	{
		cout << "Error: Tree is empty!" << endl;
		return;
	}
	
	//The greatest value should be the left most node
	//of the tree, therefore no point in checking
	//the other nodes.
	while(temp != NULL)
	{
		pred = temp;
		temp = temp->left;
	}

	cout << "The largest name value contained within the tree is: ";
	cout << pred->name;
}


void giveOptions()
{
	cout << "\n\n1. Add members" << endl;
	cout << "2. View members using traversals" << endl;
	cout << "3. View the height of the tree" << endl;
	cout << "4. View the amount of leaves" << endl;
	cout << "5. Search for a member" << endl;
	cout << "6. Find lowest weight in the tree" << endl;
	cout << "7. View largest name value contained in tree" << endl;
	cout << "0. Exit" << endl << endl;
}

int main()
{
	int choice = 0;
	float weight = 0;
	bool exit = false;
	string name;
	BST* b = new BST;
	float lowestWeight;
	cout << "Welcome! Please select an option from below.";
	do {
		giveOptions();
		cin >> choice;
		switch(choice)
		{
		case 1:
			cout << "Enter -999 in any field to exit data entry." << endl;
			while(true)
			{
				cin.ignore();
				cout << "Name: ";
				getline(cin, name);
				if(name == "-999")
					break;
				cout << "Weight: ";
				cin >> weight;
				if(weight == -999)
					break;
				if(name >= "A" && name <= "z")
					b->insertNode(name, weight);
			}
			break;

		case 2:
			cout << "\nPreorder Traversal: " << endl;
			b->preOrderTraversal(b->root);
			cout << "\n\nIn-Order Traversal: " << endl;
			b->inOrderTraversal(b->root);
			cout << "\n\nPost Order Traversal: " << endl;
			b->postOrderTraversal(b->root);
			cout << endl << endl;
			break;

		case 3:
			cout << "Current Height: " << b->getHeight(b->root) << endl;
			break;
			
		case 4:
			cout << "Current Leaves: " << b->getLeafCount(b->root) << endl;
			break;

		case 5:
			cin.ignore();
			cout << "Enter a user to search for: ";
			getline(cin, name);
			b->findMember(name);
			break;
			
		case 6:
			lowestWeight = b->getLowestWeight(b->root);
			if(lowestWeight == -1)
			{
				cout << "Error: The tree is empty!" << endl;
			}
			else
				cout << "The lowest weight contained in the tree is: " << lowestWeight << endl;
			break;

		case 7:
			b->printLargestName();
			break;

		case 0:
			exit = true;
		}
	} while (!exit);
	return 0;
}

/*
Enter -999 in any field to exit data entry:
Name: Michael
Weight: 200
Name: Chris
Weight: 164
Name: April
Weight: 102
Name: John
Weight: 180
Name: Steve
Weight: 202
Name: Harold
Weight: 171
Name: Victoria
Weight: 105
Name: Brandon
Weight: 258
Name: Blake
Weight: 191
Name: Annie
Weight: 140
Name: Kristin
Weight: 94
Name: Bertha
Weight: 300
Name: Roy
Weight: 202
Name: -999

Preorder Traversal:
Michael - 200 Chris - 164 April - 102 Annie - 140 Brandon - 258 Blake - 191 Bert
ha - 300 John - 180 Harold - 171 Kristin - 94 Steve - 202 Roy - 202 Victoria - 1
05

In-Order Traversal:
Annie - 140 April - 102 Bertha - 300 Blake - 191 Brandon - 258 Chris - 164 Harol
d - 171 John - 180 Kristin - 94 Michael - 200 Roy - 202 Steve - 202 Victoria - 1
05

Post Order Traversal:
Annie - 140 Bertha - 300 Blake - 191 Brandon - 258 April - 102 Harold - 171 Kris
tin - 94 John - 180 Chris - 164 Roy - 202 Victoria - 105 Steve - 202 Michael - 2
00

Current Height: 5

Current Leaves: 6

Enter a user to search for: Bertha

Bertha weighs 300

The lowest weight contained in the tree is: 94

The largest name value contained within the tree is: Annie
*/