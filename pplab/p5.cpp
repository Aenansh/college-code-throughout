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
  Node *get(int index)
  {
    if (index < 0 || index >= length)
      return nullptr;
    Node *temp = head;
    for (int i = 0; i < index; i++) // Assumes index starts from 0
    {
      temp = temp->next;
    }

    if (temp != nullptr)
      return temp;
    return nullptr;
  }

  void addAtHead(int val)
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
      newNode->next = head;
      head = newNode;
    }
    length++;
    return;
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

  void addAtIndex(int index, int val)
  {
    if (index < 0 || index > length)
      return;
    Node *newNode = new Node(val);
    if (!newNode)
      return;
    if (index == 0) // Assumes index starts from 0 and goes to length - 1
      return addAtHead(val);
    if (index == length)
      return addAtTail(val);
    Node *temp = get(index - 1);
    newNode->next = temp->next;
    temp->next = newNode;
    length++;
    return;
  }

  void deleteAtIndex(int index)
  {
    if (index < 0 || index >= length)
      return;
    Node *target = head;
    if (index == 0)
    {
      target = head;
      head = head->next;
      target->next = nullptr;
    }
    else
    {
      Node *temp = get(index - 1);
      if (temp->next == tail)
        tail = temp;
      target = temp->next;
      temp->next = target->next;
      target->next = nullptr;
    }
    length--;
    if (length == 0)
    {
      head = nullptr;
      tail = nullptr;
    }
    delete target;
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
  }
};

int main(int argc, char const *argv[])
{
  LinkedList l1(2);
  l1.addAtHead(1);
  l1.addAtTail(6);
  l1.addAtTail(5);
  l1.addAtHead(3);
  l1.addAtIndex(2, 4);
  l1.addAtIndex(6, 7);
  l1.deleteAtIndex(6);
  l1.printList();
  return 0;
}