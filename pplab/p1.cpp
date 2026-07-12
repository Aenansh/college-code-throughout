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
  Node *reverseIterative(Node *node)
  {
    Node *before = nullptr;
    Node *current = node;
    Node *after = node;
    while (current)
    {
      after = after->next;
      current->next = before;
      before = current;
      current = after;
    }
    return before;
  }
  bool isPalindrome()
  {
    if (!head || !head->next)
      return true;
    Node *slow = head;
    Node *fast = head;
    while (fast->next && fast->next->next)
    {
      fast = fast->next->next;
      slow = slow->next;
    }
    Node *secondHalf = reverseIterative(slow->next);
    Node *temp1 = head;
    Node *temp2 = secondHalf;
    while (temp2)
    {
      if (temp1->value != temp2->value)
        return false;
      temp1 = temp1->next;
      temp2 = temp2->next;
    }
    return true;
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
};

int main(int argc, char const *argv[])
{
  LinkedList l1(1);
  l1.addAtTail(2);
  l1.addAtTail(2);
  l1.addAtTail(1);
  l1.printList();
  cout << l1.isPalindrome();
  return 0;
}