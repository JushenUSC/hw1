/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/

#include "split.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
  //Gonna create this in the forwards direction so that the values do not get reversed
  //Less efficient, but the linked list needs to be in increasing order
  //create the head pointer
  Node* head = nullptr;
  int values[] = {1,2,3,4,5,6,7,8,9,10,11,12};
  for (int i = 0; i<=12; i++) {
    Node* newNode = new Node(values[i], nullptr);
    if (head == nullptr) {
      head = newNode;
    }
    else {
      Node* current = head;
      while (current->next != nullptr) {
        current = current->next;
      }
      current->next = newNode;
    }
  }
  Node* odds = NULL;
  Node* evens = NULL;
  split(head, odds, evens);

}
