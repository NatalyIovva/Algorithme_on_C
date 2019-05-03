// lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <stack> 
const int M = 50;

using namespace std;

struct BOOK {
	int id;
	string title;
	string author;
	int book_year;
	string publishing_house;
	double price;
	int writting_year;

};

void printData(BOOK *books, int i)
{

	if (i == 0) {
		cout << "ID: " << "Title:             " << "Author :     " << "Book year:    " << "Publishing hous:    " << "Price:     " << "Writting year: " << endl;
	}
	cout << books[i].id << "   " << books[i].title << "   " << books[i].author << "        " << books[i].book_year << "          " << books[i].publishing_house << "       " << books[i].price << "        " << books[i].writting_year << endl;

}

//SINGLE LINKED LIST
//******************
//*******
struct Node
{
public:
	int data;
	Node *next;
};
/* Given a reference (pointer to pointer) to the head of a list and
   an int, inserts a new node on the front of the list. */
void push(struct Node** head_ref, int new_data)
{
	/* 1. allocate node */
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

	/* 2. put in the data  */
	new_node->data = new_data;

	/* 3. Make next of new node as head */
	new_node->next = (*head_ref);

	/* 4. move the head to point to the new node */
	(*head_ref) = new_node;
}

/* Given a node prev_node, insert a new node after the given
   prev_node */
void insertAfter(struct Node* prev_node, int new_data)
{
	/*1. check if the given prev_node is NULL */
	if (prev_node == NULL)
	{
		printf("the given previous node cannot be NULL");
		return;
	}

	/* 2. allocate new node */
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

	/* 3. put in the data  */
	new_node->data = new_data;

	/* 4. Make next of new node as next of prev_node */
	new_node->next = prev_node->next;

	/* 5. move the next of prev_node as new_node */
	prev_node->next = new_node;
}

/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void append(struct Node** head_ref, int new_data)
{
	/* 1. allocate node */
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

	struct Node *last = *head_ref;  /* used in step 5*/

	/* 2. put in the data  */
	new_node->data = new_data;

	/* 3. This new node is going to be the last node, so make next of
		  it as NULL*/
	new_node->next = NULL;

	/* 4. If the Linked List is empty, then make the new node as head */
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}

	/* 5. Else traverse till the last node */
	while (last->next != NULL)
		last = last->next;

	/* 6. Change the next of last node */
	last->next = new_node;
	return;
}

// This function prints contents of linked list starting from head 
void printList(struct Node *node)
{
	while (node != NULL)
	{
		printf(" %d ", node->data);
		node = node->next;
	}
}
/* Given a reference (pointer to pointer) to the head of a list
   and a key, deletes the first occurrence of key in linked list */
void deleteNode(struct Node **head_ref, int key)
{
	// Store head node 
	struct Node* temp = *head_ref, *prev=0;

	// If head node itself holds the key to be deleted 
	if (temp != NULL && temp->data == key)
	{
		*head_ref = temp->next;   // Changed head 
		free(temp);               // free old head 
		return;
	}

	// Search for the key to be deleted, keep track of the 
	// previous node as we need to change 'prev->next' 
	while (temp != NULL && temp->data != key)
	{
		prev = temp;
		temp = temp->next;
	}

	// If key was not present in linked list 
	if (temp == NULL) return;

	// Unlink the node from linked list 
	prev->next = temp->next;

	free(temp);  // Free memory 
}

/* Checks whether the value x is present in linked list */
bool search(struct Node* head, int x)
{
	// Base case 
	if (head == NULL)
		return false;

	// If key is present in current node, return true 
	if (head->data== x)
		return true;

	// Recur for remaining list 
	return search(head->next, x);
}
//DOUBLE LINKED LIST
//*******************
//*****


/* Node of a doubly linked list */
struct Node1 {
	int data;
	struct Node1* next; // Pointer to next node in DLL 
	struct Node1* prev; // Pointer to previous node in DLL 
};
/* Given a reference (pointer to pointer) to the head of a list
and an int, inserts a new node on the front of the list. */
void push1(struct Node1** head_ref, int new_data)
{
	/* 1. allocate node */
	struct Node1* new_node = (struct Node1*)malloc(sizeof(struct Node1));

	/* 2. put in the data */
	new_node->data = new_data;

	/* 3. Make next of new node as head and previous as NULL */
	new_node->next = (*head_ref);
	new_node->prev = NULL;

	/* 4. change prev of head node to new node */
	if ((*head_ref) != NULL)
		(*head_ref)->prev = new_node;

	/* 5. move the head to point to the new node */
	(*head_ref) = new_node;
}
// This function prints contents of linked list starting from the given node  
void printList1(Node1* node)
{
	Node1* last=0;
	cout << "\nTraversal in forward direction \n";
	while (node != NULL)
	{
		cout << " " << node->data << " ";
		last = node;
		node = node->next;
	}

	cout << "\nTraversal in reverse direction \n";
	while (last != NULL)
	{
		cout << " " << last->data << " ";
		last = last->prev;
	}
}
/* Given a node as prev_node, insert a new node after the given node */
void insertAfter(struct Node1* prev_node, int new_data)
{
	/*1. check if the given prev_node is NULL */
	if (prev_node == NULL) {
		printf("the given previous node cannot be NULL");
		return;
	}

	/* 2. allocate new node */
	struct Node1* new_node = (struct Node1*)malloc(sizeof(struct Node1));

	/* 3. put in the data */
	new_node->data = new_data;

	/* 4. Make next of new node as next of prev_node */
	new_node->next = prev_node->next;

	/* 5. Make the next of prev_node as new_node */
	prev_node->next = new_node;

	/* 6. Make prev_node as previous of new_node */
	new_node->prev = prev_node;

	/* 7. Change previous of new_node's next node */
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
}
/* Given a reference (pointer to pointer) to the head
of a DLL and an int, appends a new node at the end */
void append(struct Node1** head_ref, int new_data)
{
	/* 1. allocate node */
	struct Node1* new_node = (struct Node1*)malloc(sizeof(struct Node1));

	struct Node1* last = *head_ref; /* used in step 5*/

	/* 2. put in the data */
	new_node->data = new_data;

	/* 3. This new node is going to be the last node, so
		make next of it as NULL*/
	new_node->next = NULL;

	/* 4. If the Linked List is empty, then make the new
		node as head */
	if (*head_ref == NULL) {
		new_node->prev = NULL;
		*head_ref = new_node;
		return;
	}

	/* 5. Else traverse till the last node */
	while (last->next != NULL)
		last = last->next;

	/* 6. Change the next of last node */
	last->next = new_node;

	/* 7. Make last node as previous of new node */
	new_node->prev = last;

	return;
}
// Function to insert a node at the end  
void insertNode(struct Node1** start, int value)
{
	// If the list is empty, create a single node  
	// circular and doubly list  
	if (*start == NULL)
	{
		struct Node1* new_node = new Node1;
		new_node->data = value;
		new_node->next = new_node->prev = new_node;
		*start = new_node;
		return;
	}

	// If list is not empty  

	/* Find last node */
	Node1 *last = (*start)->prev;

	// Create Node dynamically  
	struct Node1* new_node = new Node1;
	new_node->data = value;

	// Start is going to be next of new_node  
	new_node->next = *start;

	// Make new node previous of start  
	(*start)->prev = new_node;

	// Make last preivous of new node  
	new_node->prev = last;

	// Make new node next of old last  
	last->next = new_node;
}
/* Function to delete a node in a Doubly Linked List.
head_ref --> pointer to head node pointer.
del --> pointer to node to be deleted. */
void deleteNode1(Node1** head_ref, Node1* del)
{
	/* base case */
	if (*head_ref == NULL || del == NULL)
		return;

	/* If node to be deleted is head node */
	if (*head_ref == del)
		*head_ref = del->next;

	/* Change next only if node to be
	deleted is NOT the last node */
	if (del->next != NULL)
		del->next->prev = del->prev;

	/* Change prev only if node to be
	deleted is NOT the first node */
	if (del->prev != NULL)
		del->prev->next = del->next;

	/* Finally, free the memory occupied by del*/
	free(del);
	return;
}
// Function to display the 
// circular doubly linked list 
void displayList(struct Node1* start)
{
	struct Node1 *temp = start;

	while (temp->next != start)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("%d ", temp->data);
}
// Function to search the particular element 
// from the list 
// Function to search the particular element 
// from the list 
int searchList(struct Node1* start, int search)
{
	// Declare the temp variable 
	struct Node1 *temp = start;

	// Declare other control 
	// variable for the searching 
	int count = 0, flag = 0, value;

	// If start is NULL return -1 
	if (temp == NULL)
		return -1;
	else
	{
		// Move the temp pointer until,  
		// temp->next doesn't move 
		// start address (Circular Fashion) 
		while (temp->next != start)
		{
			// Increment count for location 
			count++;
			// If it is found raise the 
			// flag and break the loop 
			if (temp->data == search)
			{
				flag = 1;
				count--;
				break;
			}
			// Increment temp pointer 
			temp = temp->next;
		}
		// Check whether last element in the 
		// list content the value if contain,  
		// raise a flag and increment count 
		if (temp->data == search)
		{
			count++;
			flag = 1;
		}

		// If flag is true, then element 
		// found, else not 
		if (flag == 1)
			cout << "\n" << search << " found at location " <<
			count << endl;
		else
			cout << "\n" << search << " not found" << endl;
	}
}

//STACK
//**********
//********
void showstack(stack <int> s)
{
	while (!s.empty())
	{
		cout << '\t' << s.top();
		s.pop();
	}
	cout << '\n';
}
//QUEUE
//***********
//******
// A structure to represent a queue  
struct Queue
{
public:
	int front, rear, size;
	unsigned capacity;
	int* array;
};

// function to create a queue of given capacity.  
// It initializes size of queue as 0  
Queue* createQueue(unsigned capacity)
{
	Queue* queue = new Queue();
	queue->capacity = capacity;
	queue->front = queue->size = 0;
	queue->rear = capacity - 1; // This is important, see the enqueue  
	queue->array = new int[(queue->capacity * sizeof(int))];
	return queue;
}

// Queue is full when size  
// becomes equal to the capacity  
int isFull(Queue* queue)
{
	return (queue->size == queue->capacity);
}

// Queue is empty when size is 0  
int isEmpty(Queue* queue)
{
	return (queue->size == 0);
}

// Function to add an item to the queue.  
// It changes rear and size  
void enqueue(Queue* queue, int item)
{
	if (isFull(queue))
		return;
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1;
	cout << item << " enqueued to queue\n";
}

// Function to remove an item from queue.  
// It changes front and size  
int dequeue(Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	int item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;
	return item;
}

// Function to get front of queue  
int front(Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->front];
}

// Function to get rear of queue  
int rear(Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->rear];
}
//BINARY TREE
//************
//*********
struct node
{
	int key;
	struct node *left, *right;
};

// A utility function to create a new BST node 
struct node *newNode(int item)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

// A utility function to do inorder traversal of BST 
void inorder(struct node *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d ", root->key);
		inorder(root->right);
	}
}

/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key)
{
	/* If the tree is empty, return a new node */
	if (node == NULL) return newNode(key);

	/* Otherwise, recur down the tree */
	if (key < node->key)
		node->left = insert(node->left, key);
	else
		node->right = insert(node->right, key);

	/* return the (unchanged) node pointer */
	return node;
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
struct node * minValueNode(struct node* node)
{
	struct node* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}

/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
struct node* deleteNode(struct node* root, int key)
{
	// base case 
	if (root == NULL) return root;

	// If the key to be deleted is smaller than the root's key, 
	// then it lies in left subtree 
	if (key < root->key)
		root->left = deleteNode(root->left, key);

	// If the key to be deleted is greater than the root's key, 
	// then it lies in right subtree 
	else if (key > root->key)
		root->right = deleteNode(root->right, key);

	// if key is same as root's key, then This is the node 
	// to be deleted 
	else
	{
		// node with only one child or no child 
		if (root->left == NULL)
		{
			struct node *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			struct node *temp = root->left;
			free(root);
			return temp;
		}

		// node with two children: Get the inorder successor (smallest 
		// in the right subtree) 
		struct node* temp = minValueNode(root->right);

		// Copy the inorder successor's content to this node 
		root->key = temp->key;

		// Delete the inorder successor 
		root->right = deleteNode(root->right, temp->key);
	}
	return root;
}
/* Given a binary tree, print its nodes according to the
"bottom-up" postorder traversal. */
void printPostorder(struct node* node)
{
	if (node == NULL)
		return;

	// first recur on left subtree 
	printPostorder(node->left);

	// then recur on right subtree 
	printPostorder(node->right);

	// now deal with the node 
	cout << node->key << " ";
}

/* Given a binary tree, print its nodes in inorder*/
void printInorder(struct node* node)
{
	if (node == NULL)
		return;

	/* first recur on left child */
	printInorder(node->left);

	/* then print the data of node */
	cout << node->key << " ";

	/* now recur on right child */
	printInorder(node->right);
}

/* Given a binary tree, print its nodes in preorder*/
void printPreorder(struct node* node)
{
	if (node == NULL)
		return;

	/* first print data of node */
	cout << node->key << " ";

	/* then recur on left sutree */
	printPreorder(node->left);

	/* now recur on right subtree */
	printPreorder(node->right);
}
int main()
{
	BOOK books[M];
	ifstream file("input.txt");
	if (file.is_open())
	{
		string line;

		for (int i = 0; getline(file, line); i++)
		{
			istringstream iss(line);
			iss >> books[i].id >> books[i].title >> books[i].author >> books[i].book_year >> books[i].publishing_house >> books[i].price >> books[i].writting_year;
			printData(books, i);

		}

	}
	else {
		cout << "The file doesn't open" << endl;

	}
	int c,element;
	struct Node* head = NULL;
	struct Node1* head1 = NULL;
	struct node *root = NULL;
	stack <int> s;
	Queue* queue = createQueue(1000);
	do {
		cout << "Menu:\n" << "1)SINGLE LINKED LIST \n" << "2)DOUBLE LINKED LIST\n" << "3)STACK\n" << "4)QUEUE\n" <<"5)BINARY TREE\n" <<"0)Exit" << endl;
		cin >> c;
	} while (c > 5 || c < 0);
	switch (c)
	{case 1:
		for (int i = 0; i < M; i++) {
			append(&head, books[i].id);
		}
		printf("\n Created Linked list is: ");
		printList(head);
		cout << "\n insert an element at the start:";
		cin >> element;
		push(&head, element);
		puts("\nCreated Linked List: ");
		printList(head);
		cout << "\n Which elemnt do you want to found:";
		cin >> element;
		puts("\nCreated Linked List: ");
		printList(head);
		search(head, element) ? cout << "Yes, exist" : cout << "No, doesn't exist";
		cout << "\n Which elemnt do you want to found:";
		cin >> element; 
		deleteNode(&head, element);
		puts("\nLinked List after Deletion: ");
		printList(head);
		break;
	case 2:
		for (int i = 0; i < M; i++) {
			push1(&head1, books[i].id);
		}
		printf("\n Created Linked list is: ");
		printList1(head1);
		cout << "\n insert an element at the end:";
		cin >> element;
		append(&head1, element);
		printf("\n Created Linked list is: ");
		printList1(head1);
		cout << "\n Which elemnt do you want to delete:";
		cin >> element;
		deleteNode1(&head1,head1->next);
		printf("\n Created Linked list is: ");
		printList1(head1);
		cout << "\n Which elemnt do you want to found:";
		cin >> element;
		searchList(head1, element);
		break;
	case 3:
		for (int i = 0; i < M; i++) {
			s.push(books[i].id);
		}
		cout << "The stack is : ";
		showstack(s);
		cout << "\ns.size() : " << s.size();
		cout << "\ns.top() : " << s.top();
		break;
	case 4:
		for (int i = 0; i < M; i++) {
			enqueue(queue, books[i].id);
		}
		cout << dequeue(queue) << " dequeued from queue\n";

		cout << "Front item is " << front(queue) << endl;
		cout << "Rear item is " << rear(queue) << endl;
		break;
	case 5:
		for (int i = 0; i < M; i++) {
			root = insert(root, books[i].id);
		}
		inorder(root);
		cout << "\n Which elemnt do you want to delete:";
		cin >> element;
		root = deleteNode(root, element);
		inorder(root);
		cout << "\nPreorder traversal of binary tree is \n";
		printPreorder(root);

		cout << "\nInorder traversal of binary tree is \n";
		printInorder(root);

		cout << "\nPostorder traversal of binary tree is \n";
		printPostorder(root);
		break;
	case 0:
		break;
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
