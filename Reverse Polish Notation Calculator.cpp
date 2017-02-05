#include <iostream>
#include <stdlib.h>
using namespace std;

class node
{
public:
	float info;
	node* next;
	node(float data, node* ptr = 0)
	{ info = data; next = ptr; }
};

class RPN
{
public:
	RPN(){top = NULL;}
	void print();
	void push(float);
	float pop();
	bool isEmpty(){return top == NULL;}
	
private:
	node* top;
};

void RPN::push(float n)
{
	node *newNode;
	newNode = new node(n);
	newNode->next = top;
	top = newNode;
}

float RPN::pop()
{
	if(isEmpty())
		cout << "Error: Invalid input." << endl;
	else
	{
		node* temp = top;
		float element = temp->info;
		top = top->next;
		delete temp;
		return element;
	}
}

void RPN::print()
{
	for(node* tmp = top; tmp != 0; tmp = tmp->next)
		cout << tmp->info << " ";
}

void checkOperator(char operand, RPN *s)
{
	float a = 0, b = 0;
	switch(operand)
	{
	case '+':
		a = s->pop();
		b = s->pop();
		s->push(b + a);
		break;
	case '-':
		a = s->pop();
		b = s->pop();
		s->push(b - a);
		break;
	case '*':
		a = s->pop();
		b = s->pop();
		s->push(b * a);
		break;
	case '/':
		a = s->pop();
		b = s->pop();
		//Check if the denominator popped is a zero and
		//alert the user true.
		if(a == 0)
		{
			cout << "Error: division by zero" << endl;
			break;
		}
		else
			s->push( b / a );
		break;
	case '0':
		s->push(0);
		break;
	default:
		cout << "Input '" << operand << "' not recognized." << endl;
		break;
	}
}

void parseExp(char exp[], RPN *s)
{
	char* parse;
	int operators = 0, operands = 0;
	parse = strtok(exp," ");
	while(parse != NULL)
		if(atof(parse) != 0)
		{
			++operands;
			s->push(atof(parse));
			parse = strtok(NULL, " ");
		}
		else if(atof(parse) == 0)
		{
			//Check if parsing char is NOT '0' before incrementing operators else
			//increment '0' as an operand.
			(*parse != '0') ? ++operators: ++operands;
			checkOperator(*parse, s);
			parse = strtok(NULL, " " );
		}
}

bool getExpression(char exp[])
{
	cout << "\nEnter an expression to continue or 0 to terminate:\n\n";
	cin.getline(exp,' ');
	//Returns boolean as a sentry for user to quit in main.
	return (*exp == '0');
}


int main()
{
	bool userIsDone = false;
	char exp[50] = " ";
	cout << "* * *Reverse Polish Notation Calculator* * *" << endl;
	do {
		RPN *s = new RPN;
		userIsDone = getExpression(exp);
		parseExp(exp, s);
		s->print();
		delete s;
	} while(userIsDone != true);
	cout << "Exiting..." << endl;
	return 0;
}

/*
* * *Reverse Polish Notation Calculator* * *

Enter an expression to continue or 0 to terminate:

10 15 +
25
Enter an expression to continue or 0 to terminate:

10 15 -
-5
Enter an expression to continue or 0 to terminate:

2.5 3.5 +
6
Enter an expression to continue or 0 to terminate:

10 0 /
Error: division by zero

Enter an expression to continue or 0 to terminate:

10 20 * /
Error: Invalid input.
-1.#IND
Enter an expression to continue or 0 to terminate:

-10 -30 -
20
Enter an expression to continue or 0 to terminate:

12 20 30 /
0.666667 12
Enter an expression to continue or 0 to terminate:

100 10 50 25 / * - -2 /
-40
*/