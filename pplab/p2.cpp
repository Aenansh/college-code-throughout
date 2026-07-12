#include <iostream>
using namespace std;

class Node
{
public:
  int value;
  Node *next;
  Node()
  {
    next = nullptr;
  }
  Node(int val)
  {
    value = val;
    next = nullptr;
  }
};

class LinkedList
{
private:
  Node *head;
  Node *tail;
  int length;

public:
  LinkedList()
  {
    head = nullptr;
    tail = nullptr;
    length = 0;
  }
  LinkedList(int val)
  {
    Node *newNode = new Node(val);
    head = newNode;
    tail = newNode;
    length = 1;
  }
  void addAtTail(int val)
  {
    Node *newNode = new Node(val);
    if (!newNode)
      return;
    if (length == 0)
    {
      head = newNode;
      tail = newNode;
    }
    else
    {
      tail->next = newNode;
      tail = newNode;
    }
    length++;
    return;
  }

  void reverseIterative()
  {
    Node *before = nullptr;
    Node *current = head;
    Node *after = head;

    while (current)
    {
      after = after->next;
      current->next = before;
      before = current;
      current = after;
    }
    Node *temp = head;
    head = tail;
    tail = temp;
    return;
  }

  void printList()
  {
    Node *temp = head;
    while (temp != nullptr)
    {
      cout << temp->value << " ";
      temp = temp->next;
    }
    cout << endl;
  }
  Node *func(Node *node)
  {
    if (!node || !node->next)
      return node;
    Node *newNode = func(node->next);
    node->next->next = node;
    node->next = nullptr;
    return newNode;
  }
  void reverseRecursive()
  {
    if (length <= 1)
      return;
    tail = head;
    head = func(head);
  }
};

int main(int argc, char const *argv[])
{
  LinkedList l1(1);
  l1.addAtTail(2);
  l1.addAtTail(3);
  l1.addAtTail(4);
  l1.addAtTail(5);
  cout << "Original: " << endl;
  l1.printList();
  cout << "Iteratively: " << endl;
  l1.reverseIterative();
  l1.printList();
  l1.reverseIterative(); // Re-reverse for next type
  cout << "Recursively: " << endl;
  l1.reverseRecursive();
  l1.printList();
  return 0;
}