/* Willem van Veldhuisen
   12/06*/
#include <iostream>
#include <cstring>
#include "Node.h"
#include <fstream>

using namespace std;

//Functions
void add(Node** head);
void print(Node* current, int dist);
Node* getParent(Node* current, int val);
Node* find(Node* current, int val);
void addValue(int a, Node** current);
void remove(Node** head);
Node* getReplacementNode(Node* current);
void search(Node* head);
void showTree(Node* head);

//Main
int main() {
  //Variables
  Node* head = NULL;
  add(&head);
  while(1) {
    cout << "enter a command(add, remove, search, show tree, quit)" << endl;
    char* input;
    input = new char[10];
    cin.getline(input, 10);
    if (strcmp(input, "add") == 0) {
      add(&head);
    }
    else if (strcmp(input, "remove") == 0) {
      remove(&head);
    }
    else if (strcmp(input, "search") == 0) {
      search(head);
    }
    else if (strcmp(input, "show tree") == 0) {
      showTree(head);
    }
    else if (strcmp(input, "quit") == 0) {
      break;
    }
    else {
      cout << endl << "invalid input" << endl << endl;
    }
  }
  
  return 0;
}
//Gather user input to create new 
void add(Node** head) {
  //Pick console or file input
  cout << endl;
  char* choice = new char[10];
  cout << "console or file input(console/file)" << endl;
  cin.getline(choice, 10);
  //File input
  if (strcmp(choice, "file") == 0) {
    cout << "enter file name" << endl;
    char fileName[30];
    cin.getline(fileName, 30);
    fstream file;
    file.open (fileName);
    while(!file.eof()) {
      int entry = 0;
      file >> entry;
      if (entry != 0) {
	addValue(entry, head);
      }
    }
  }
  //Console input
  else if (strcmp(choice, "console") == 0) {
    cout << "enter numbers from 1-999 pressing enter after each enter 0 when done" << endl;
    while(1) {
      int entry;
      cin >> entry;
      if (entry == 0) {
	break;
      }
      else {
	addValue(entry, head);
      }
    }
  }
  //Invalid input
  else {
    cout << "invalid input" << endl;
  }
  cout << endl;
}
//Add a value to the tree using binary search and recursion
void addValue(int a, Node** current) {
  Node* temp;
  //If the head is empty fill it in
  if (*current == NULL) {
    *current = new Node(a);
  }
  //If a is less than the current value it goes to the left
  else if ((*current)->getValue() > a) {
    if ((*current)->getLchild() == NULL) {
      (*current)->setLchild(new Node(a));
    }
    else {
      temp = (*current)->getLchild();
      addValue(a, &temp);
    }
  }
  //If a is greater than the current value it goes to the right
  else if ((*current)->getValue() < a) {
    if ((*current)->getRchild() == NULL) {
      (*current)->setRchild(new Node(a));
    }
    else {
      temp = (*current)->getRchild();
      addValue(a, &temp);
    }
  }
}
//Find a value from the tree
Node* find(Node* current, int val) {
  if (current == NULL) {
    return NULL;
  }
  else if (current->getValue() == val) {
    return current;
  }
  else if (current->getValue() > val) {
    return find(current->getLchild(), val);
  }
  else if (current->getValue() < val) {
    return find(current->getRchild(), val);
  }
}
//Remove a value and node from the tree
void remove(Node** head) {
  cout << endl;
  cout << "enter number you want to remove" << endl;
  int val;
  Node* temp;
  Node* temp1;
  cin >> val;
  Node* node = find(*head, val);
  temp = node;
  if (node == NULL) {
    cout << "number does not exist" << endl;
  }
  //If deleting the head node
  else if (node == *head) {
    if (node->getRchild() == NULL && node->getLchild() == NULL) {
      *head = NULL;
    }
    else if (node->getRchild() != NULL && node->getLchild() == NULL) {
      *head = (*head)->getRchild();
    }
    else if (node->getRchild() == NULL && node->getLchild() != NULL) {
      *head = (*head)->getLchild();
    }
    else {
      cout << "head with 2 children" << endl;
      node = getReplacementNode((*head)->getLchild());
      temp1 = getParent(*head, node->getValue());
      if (node->getLchild() == NULL) {
	*head = node;
	if (temp->getLchild() != node) {
	  (*head)->setLchild(temp->getLchild());
	}
	else {
	  (*head)->setLchild(NULL);
	}
	(*head)->setRchild(temp->getRchild());
      }
      else {
        cout << "Replacement node has a left child" << endl;
	temp1 = node->getLchild();
	*head = node;
	if (temp->getLchild() != node) {
	  (*head)->setLchild(temp->getLchild());
	  getParent(*head, node->getValue())->setRchild(temp1);
	}
	else {
	  cout << "a" << endl;
	  (*head)->setLchild(temp1);
	}
	(*head)->setRchild(temp->getRchild());
      }
    }
    temp->~Node();
  }
  else if (node->getRchild() == NULL || node->getLchild() == NULL) {
    if (node->getRchild() == NULL) {
      if (node->getLchild() != NULL) {
	node = node->getLchild();
	if (getParent(*head, val)->getValue() > val) {
	  getParent(*head, val)->setLchild(node);
	}
	else {
	  getParent(*head, val)->setRchild(node);
	}
      }
      else {
        if (getParent(*head, val)->getValue() > val) {
	  getParent(*head, val)->setLchild(NULL);
	}
	else {
	  getParent(*head, val)->setRchild(NULL);
	}
      }
    }
    else {
      node = node->getRchild();
      if (getParent(*head, val)->getValue() > val) {
	getParent(*head, val)->setLchild(node);
      }
      else {
	getParent(*head, val)->setRchild(node);
      }
    }
    temp->~Node();
  }
  else {
    temp1 = node->getRchild();
    node = getReplacementNode(node->getLchild());
    if (getParent(*head, val)->getValue() > val) {
      getParent(*head, val)->setLchild(node);
    }
    else {
      getParent(*head, val)->setRchild(node);
    }
    temp->~Node();
    node->setRchild(temp1);
  }
  cout << endl;
}
//Get parent of a node
Node* getParent(Node* current, int val) {
  if (current->getValue() > val) {
    if (current->getLchild()->getValue() == val) {
      return current;
    }
    else {
      return getParent(current->getLchild(), val);
    }
  }
  else if (current->getValue() < val) {
    if (current->getRchild()->getValue() == val) {
      return current;
    }
    else {
      return getParent(current->getRchild(), val);
    }
  }
}
Node* getReplacementNode(Node* current) {
  if (current->getRchild() == NULL) {
    return current;
  }
  else {
    getReplacementNode(current->getRchild());
  }
}
//Search for a value in the tree
void search(Node* head) {
  cout << endl;
  cout << "enter number you want to search" << endl;
  int val;
  cin >> val;
  Node* node = find(head, val);
  if (node == NULL) {
    cout << "number does not exist" << endl;
  }
  else {
    cout << "number exists" << endl;
  }
  cout << endl;
}
//Wrapper for printing tree
void showTree(Node* head) {
  cout << "your binary tree:";
  print(head, 0);
  cout << endl;
}
//Printing tree
void print(Node* current, int dist) {
  if (current == NULL) {
    return;
  }
  dist += 5;
  //cout << "dist: " << dist << endl;
  print(current->getRchild(), dist);
  cout << endl;
  for (int i = 2; i < dist; i++) {
    cout << ' ';
  }
  cout << current->getValue() << "\n";
  print(current->getLchild(), dist);
}
